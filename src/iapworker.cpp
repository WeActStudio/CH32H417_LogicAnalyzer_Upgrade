/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * IAP upgrade worker implementation
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "iapworker.h"
#include <QCoreApplication>
#include "firmwareimage.h"
#include "ch375dev.h"
#include "libusbdev.h"
#include "serialdev.h"

#include <hidapi.h>

#include <QThread>
#include <QFileInfo>
#include <QDateTime>

#include <cstring>

namespace {

/* On Windows hid_error() returns a wchar_t* */
QString hid_error_string(hid_device *dev)
{
    const wchar_t *msg = ::hid_error(dev);
    if (!msg)
        return QCoreApplication::translate("IapWorker", "Unknown error");
    return QString::fromWCharArray(msg);
}

} // namespace

IapWorker::IapWorker(const Config &config, QObject *parent)
    : QObject(parent)
    , config_(config)
    , hidHandle_(nullptr)
    , cancelled_(false)
{
}

IapWorker::~IapWorker()
{
    closeHid();
}

void IapWorker::cancel()
{
    QMutexLocker locker(&mutex_);
    cancelled_ = true;
}

bool IapWorker::isCancelled()
{
    QMutexLocker locker(&mutex_);
    return cancelled_;
}

void IapWorker::log(const QString &message)
{
    Q_EMIT logMessage(message);
}

void IapWorker::updateProgress(int percent, const QString &status)
{
    Q_EMIT progressUpdated(percent, status);
}

/* ==========================================================================
 * HID device handling
 * ========================================================================== */

bool IapWorker::openHid(int waitSeconds)
{
    static bool hidInitialized = false;
    if (!hidInitialized) {
        if (::hid_init() != 0) {
            log(tr("Failed to initialize hidapi"));
            return false;
        }
        hidInitialized = true;
    }

    const int maxTries = qMax(1, waitSeconds) * 2;   /* one attempt every 500 ms */

    for (int i = 0; i < maxTries; ++i) {
        if (isCancelled()) {
            log(tr("Cancelled while waiting for the IAP device"));
            return false;
        }

        hidHandle_ = ::hid_open(config_.iapVid, config_.iapPid, nullptr);
        if (hidHandle_) {
            ::hid_set_nonblocking(static_cast<hid_device *>(hidHandle_), 1);
            log(tr("Connected to IAP device (VID:0x%1 PID:0x%2)")
                    .arg(config_.iapVid, 4, 16, QChar('0'))
                    .arg(config_.iapPid, 4, 16, QChar('0')));
            return true;
        }

        if (i == 0)
            log(tr("Waiting for the IAP device (VID:0x%1 PID:0x%2) ...")
                    .arg(config_.iapVid, 4, 16, QChar('0'))
                    .arg(config_.iapPid, 4, 16, QChar('0')));

        QThread::msleep(500);
    }

    log(tr("IAP device not found after waiting %1 seconds").arg(waitSeconds));
    return false;
}

void IapWorker::closeHid()
{
    if (hidHandle_) {
        ::hid_close(static_cast<hid_device *>(hidHandle_));
        hidHandle_ = nullptr;
    }
}

bool IapWorker::hidWrite(const quint8 *data, int len)
{
    if (!hidHandle_)
        return false;

    quint8 sendBuf[HID_PACKET_LEN];
    std::memset(sendBuf, 0, sizeof(sendBuf));
    sendBuf[0] = HID_REPORT_ID;

    const int copyLen = qMin(len, HID_PACKET_LEN - 1);
    if (copyLen > 0)
        std::memcpy(sendBuf + 1, data, static_cast<size_t>(copyLen));

    int elapsed = 0;
    while (elapsed < HID_TIMEOUT_MS) {
        if (isCancelled()) {
            log(tr("Write cancelled"));
            return false;
        }

        const int result = ::hid_write(static_cast<hid_device *>(hidHandle_),
                                       sendBuf, HID_PACKET_LEN);
        if (result > 0)
            return true;
        if (result == 0) {
            QThread::msleep(20);
            elapsed += 20;
            continue;
        }

        log(tr("HID write failed: %1")
                .arg(hid_error_string(static_cast<hid_device *>(hidHandle_))));
        return false;
    }

    log(tr("HID write timed out (%1 ms)").arg(HID_TIMEOUT_MS));
    return false;
}

bool IapWorker::hidRead(quint8 *data, int len, int timeoutMs, bool reportFailure)
{
    if (!hidHandle_)
        return false;

    quint8 recvBuf[HID_PACKET_LEN];
    std::memset(recvBuf, 0, sizeof(recvBuf));

    int elapsed = 0;
    while (elapsed < timeoutMs) {
        if (isCancelled()) {
            log(tr("Read cancelled"));
            return false;
        }

        const int slice = qMin(100, timeoutMs - elapsed);
        const int result = ::hid_read_timeout(static_cast<hid_device *>(hidHandle_),
                                              recvBuf, HID_PACKET_LEN, slice);
        if (result > 0) {
            const int outLen = qMin(len, HID_PACKET_LEN - 1);
            std::memcpy(data, recvBuf + 1, static_cast<size_t>(outLen));
            return true;
        }
        if (result == 0) {
            elapsed += slice;
            continue;
        }

        /* hidapi says "Success" when the device just vanished, which reads like
         * a contradiction - the finish step expects that and stays quiet */
        if (reportFailure) {
            log(tr("HID read failed: %1")
                    .arg(hid_error_string(static_cast<hid_device *>(hidHandle_))));
        }
        return false;
    }

    return false;   /* The caller decides how to report a timeout */
}

/* ==========================================================================
 * IAP sequence
 * ========================================================================== */

bool IapWorker::enterIapMode()
{
    if (isCancelled()) {
        log(tr("Upgrade cancelled"));
        return false;
    }

    if (config_.deviceBusy) {
        log(tr("The device is in use by another program.\n"
               "Close the program that currently uses the board "
               "(for example the logic analyzer software) and refresh."));
        return false;
    }

    if (config_.alreadyInIap) {
        log(tr("Device is already in IAP mode, skipping the mode switch"));
        return true;
    }

    /*
     * A CH375 index is only required for the CH375 channel; a libusb upgrade
     * addresses the board by bus/address and a serial upgrade by its COM port
     * (ch375Index is -1 on all other channels).
     */
    if (!config_.viaLibusb && !config_.viaSerial && config_.ch375Index < 0) {
        log(tr("No usable CH375 device index, cannot send the switch command"));
        return false;
    }

    /*
     * The board sits in application mode on one of three channels: the CH375
     * driver, a generic USB driver (WinUSB) reached through libusb, or a COM
     * port when the USB-to-UART application is running. All of them carry the
     * same request, only the transport differs - on the serial channel the
     * request *is* the baud rate.
     */
    QString error;
    bool sent = false;
    if (config_.viaSerial) {
        log(tr("Opening %1 at the IAP baud rate %2 ...")
                .arg(config_.serialPort).arg(CH32H417_U2U_IAP_BAUD));
        sent = serialdev_enter_iap(config_.serialPort, error);
    } else if (config_.viaLibusb) {
        log(tr("Sending enter-IAP-mode command over libusb (bus %1, address %2) ...")
                .arg(config_.libusbBus).arg(config_.libusbAddress));
        sent = libusbdev_enter_iap(config_.libusbBus, config_.libusbAddress, error);
    } else {
        log(tr("Sending enter-IAP-mode command to device (CH375 index %1) ...").arg(config_.ch375Index));
        sent = ch375dev_enter_iap(config_.ch375Index, error);
    }
    if (!sent) {
        log(tr("Failed to enter IAP mode: %1").arg(error));
        return false;
    }

    log(tr("Command sent, waiting for the device to reset into a HID IAP device ..."));

    for (int i = 0; i < 10; ++i) {
        if (isCancelled()) {
            log(tr("Upgrade cancelled"));
            return false;
        }
        QThread::msleep(100);
    }

    return true;
}

bool IapWorker::eraseFlash(quint32 startAddr)
{
    if (isCancelled())
        return false;

    log(tr("Erasing FLASH, start address 0x%1").arg(startAddr, 8, 16, QChar('0')));
    updateProgress(20, tr("Erasing FLASH ..."));

    quint8 cmd[IAP_DATA_LEN];
    std::memset(cmd, 0, sizeof(cmd));
    cmd[0] = CMD_IAP_ERASE;
    cmd[1] = 0;
    cmd[2] = static_cast<quint8>(startAddr & 0xFF);
    cmd[3] = static_cast<quint8>((startAddr >> 8) & 0xFF);
    cmd[4] = static_cast<quint8>((startAddr >> 16) & 0xFF);
    cmd[5] = static_cast<quint8>((startAddr >> 24) & 0xFF);

    if (!hidWrite(cmd, 6)) {
        log(tr("Failed to send the erase command"));
        return false;
    }

    quint8 resp[IAP_DATA_LEN];
    std::memset(resp, 0, sizeof(resp));
    if (!hidRead(resp, 2, 10000)) {
        log(tr("Erase response timed out"));
        return false;
    }

    if (resp[0] != 0x00 || resp[1] != 0x00) {
        log(tr("Erase failed, error code: %1").arg(resp[1]));
        return false;
    }

    log(tr("Erase complete"));
    return true;
}

bool IapWorker::programFlash(const quint8 *data, int len)
{
    log(tr("Programming FLASH, %1 bytes in total").arg(len));
    updateProgress(25, tr("Programming FLASH ... %1%").arg(0));

    int offset = 0;
    int retryCount = 0;

    while (offset < len) {
        if (isCancelled()) {
            log(tr("Upgrade cancelled"));
            return false;
        }

        const int chunkSize = qMin(IAP_PROGRAM_MAX, len - offset);

        quint8 cmd[IAP_DATA_LEN];
        std::memset(cmd, 0, sizeof(cmd));
        cmd[0] = CMD_IAP_PROM;
        cmd[1] = static_cast<quint8>(chunkSize);
        std::memcpy(cmd + 2, data + offset, static_cast<size_t>(chunkSize));

        if (!hidWrite(cmd, 2 + chunkSize)) {
            log(tr("Failed to write data, offset %1").arg(offset));
            if (++retryCount > 3)
                return false;
            QThread::msleep(100);
            continue;
        }

        quint8 resp[IAP_DATA_LEN];
        std::memset(resp, 0, sizeof(resp));
        if (!hidRead(resp, 2, HID_TIMEOUT_MS)) {
            log(tr("Programming response timed out, offset %1").arg(offset));
            if (++retryCount > 3)
                return false;
            QThread::msleep(100);
            continue;
        }

        if (resp[0] != 0x00 || resp[1] != 0x00) {
            log(tr("Programming failed, error code %1, offset %2").arg(resp[1]).arg(offset));
            if (++retryCount > 3)
                return false;
            QThread::msleep(100);
            continue;
        }

        retryCount = 0;
        offset += chunkSize;

        const int percent = 25 + static_cast<int>(45LL * offset / len);

        /*
         * The text is rounded down to a multiple of 10% so that a block of a
         * few dozen bytes does not produce a new line (or a new label) on its
         * own; the progress bar still uses the exact value above.
         */
        updateProgress(percent, tr("Programming FLASH ... %1%").arg(offset * 10 / len * 10));
    }

    /* A zero length packet tells the firmware that all data has been sent */
    quint8 cmd[IAP_DATA_LEN];
    std::memset(cmd, 0, sizeof(cmd));
    cmd[0] = CMD_IAP_PROM;
    cmd[1] = 0;
    hidWrite(cmd, 2);

    log(tr("Programming complete"));
    return true;
}

bool IapWorker::verifyFlash(quint32 startAddr, const quint8 *data, int len)
{
    log(tr("Verifying FLASH ..."));
    updateProgress(70, tr("Verifying FLASH ... %1%").arg(0));

    int offset = 0;
    quint32 verifyAddr = startAddr;
    int retryCount = 0;

    while (offset < len) {
        if (isCancelled()) {
            log(tr("Upgrade cancelled"));
            return false;
        }

        const int chunkSize = qMin(IAP_VERIFY_MAX, len - offset);

        quint8 cmd[IAP_DATA_LEN];
        std::memset(cmd, 0, sizeof(cmd));
        cmd[0] = CMD_IAP_VERIFY;
        cmd[1] = static_cast<quint8>(chunkSize);
        cmd[2] = static_cast<quint8>(verifyAddr & 0xFF);
        cmd[3] = static_cast<quint8>((verifyAddr >> 8) & 0xFF);
        cmd[4] = static_cast<quint8>((verifyAddr >> 16) & 0xFF);
        cmd[5] = static_cast<quint8>((verifyAddr >> 24) & 0xFF);
        std::memcpy(cmd + 6, data + offset, static_cast<size_t>(chunkSize));

        if (!hidWrite(cmd, 6 + chunkSize)) {
            log(tr("Failed to send the verify command, offset %1").arg(offset));
            if (++retryCount > 3)
                return false;
            QThread::msleep(100);
            continue;
        }

        quint8 resp[IAP_DATA_LEN];
        std::memset(resp, 0, sizeof(resp));
        if (!hidRead(resp, 2, HID_TIMEOUT_MS)) {
            log(tr("Verify response timed out, offset %1").arg(offset));
            if (++retryCount > 3)
                return false;
            QThread::msleep(100);
            continue;
        }

        if (resp[0] != 0x00 || resp[1] != 0x00) {
            log(tr("Verification failed, error code %1, address 0x%2")
                    .arg(resp[1])
                    .arg(verifyAddr, 8, 16, QChar('0')));
            if (++retryCount > 3)
                return false;
            QThread::msleep(100);
            continue;
        }

        retryCount = 0;
        offset += chunkSize;
        verifyAddr += static_cast<quint32>(chunkSize);

        const int percent = 70 + static_cast<int>(25LL * offset / len);

        /* Rounded down to a multiple of 10%, see programFlash() */
        updateProgress(percent, tr("Verifying FLASH ... %1%").arg(offset * 10 / len * 10));
    }

    log(tr("Verification succeeded"));
    return true;
}

bool IapWorker::endUpgrade()
{
    log(tr("Sending the upgrade-finish command ..."));
    updateProgress(96, tr("Finishing upgrade ..."));

    quint8 cmd[IAP_DATA_LEN];
    std::memset(cmd, 0, sizeof(cmd));
    cmd[0] = CMD_IAP_END;
    cmd[1] = 0;

    if (!hidWrite(cmd, 2)) {
        log(tr("Failed to send the finish command"));
        return false;
    }

    /* The firmware resets and jumps immediately after END, so a reply is unusual */
    quint8 resp[IAP_DATA_LEN];
    std::memset(resp, 0, sizeof(resp));
    if (hidRead(resp, 2, 2000, false)) {
        if (resp[0] == CMD_JUMP_IAP)
            log(tr("Device confirmed the upgrade"));
    } else {
        log(tr("Device has reset (no response is normal)"));
    }

    return true;
}

/* ==========================================================================
 * Firmware loading and main sequence
 * ========================================================================== */

bool IapWorker::loadFirmware(QByteArray &outData, quint32 &startAddr)
{
    QString error;
    FirmwareImage image;

    updateProgress(3, tr("Reading firmware file ..."));

    if (!firmware_load(config_.firmwarePath, config_.binBaseAddress, image, error)) {
        log(tr("Failed to load firmware: %1").arg(error));
        return false;
    }

    log(tr("Firmware loaded: %1").arg(QFileInfo(config_.firmwarePath).fileName()));
    log(tr("  Format: %1, size: %2 bytes")
            .arg(image.fromHex ? tr("Intel HEX") : tr("BIN"))
            .arg(image.data.size()));
    log(tr("  Address range: 0x%1 - 0x%2")
            .arg(image.startAddress, 8, 16, QChar('0'))
            .arg(image.endAddress, 8, 16, QChar('0')));
    log(tr("  Checksum: 0x%1").arg(image.checksum, 8, 16, QChar('0')));

    if (image.data.isEmpty()) {
        log(tr("Firmware data is empty"));
        return false;
    }

    outData = image.data;
    startAddr = image.startAddress;

    /* See Config::alignTo: the tail buffer of the firmware is only flushed on
       the first VERIFY after a reset, so align to the flash page instead. */
    if (config_.alignTo > 1 && (outData.size() % static_cast<int>(config_.alignTo)) != 0) {
        const int pad = static_cast<int>(config_.alignTo)
                        - (outData.size() % static_cast<int>(config_.alignTo));
        outData.append(QByteArray(pad, static_cast<char>(0xFF)));
        log(tr("Padded the image with %1 bytes of 0xFF (flash page alignment)")
                .arg(pad));
    }

    return true;
}

void IapWorker::run()
{
    QString errorHint;

    updateProgress(1, tr("Starting upgrade ..."));
    log(tr("========== Firmware upgrade started %1 ==========")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));

    QByteArray firmwareData;
    quint32 startAddr = 0;

    /* Switching to the bootloader alone needs no firmware file at all, so it
       must not be loaded here - a missing file would abort the request before
       the board is even asked to reboot */
    if (!config_.onlyEnterIap && !loadFirmware(firmwareData, startAddr)) {
        Q_EMIT finished(false, tr("Failed to load the firmware file"));
        return;
    }

    /* 1. Enter IAP mode */
    updateProgress(10, tr("Entering IAP mode ..."));
    if (!enterIapMode()) {
        Q_EMIT finished(false, tr("Unable to enter IAP mode"));
        return;
    }

    /* The board is in its bootloader now - that was the whole request */
    if (config_.onlyEnterIap) {
        updateProgress(100, tr("Device is now in IAP mode"));
        Q_EMIT finished(true, tr("The device rebooted into IAP mode"));
        return;
    }

    /* 2. Connect to the HID IAP device */
    updateProgress(15, tr("Looking for the IAP device ..."));
    if (!openHid(config_.hidWaitSeconds)) {
        Q_EMIT finished(false, tr("No device in IAP mode found"));
        return;
    }
    updateProgress(18, tr("Connected to the IAP device"));

    /* 3. Erase */
    if (!eraseFlash(startAddr)) {
        closeHid();
        Q_EMIT finished(false, tr("Failed to erase FLASH"));
        return;
    }

    /* 4. Program */
    if (!programFlash(reinterpret_cast<const quint8 *>(firmwareData.constData()),
                      firmwareData.size())) {
        closeHid();
        Q_EMIT finished(false, tr("Failed to program FLASH"));
        return;
    }

    /* 5. Verify */
    if (!verifyFlash(startAddr,
                     reinterpret_cast<const quint8 *>(firmwareData.constData()),
                     firmwareData.size())) {
        closeHid();
        Q_EMIT finished(false, tr("Failed to verify FLASH"));
        return;
    }

    /* 6. Finish */
    if (config_.skipEnd) {
        /* Batch mode: the caller programs the next slot over the same
           connection and finishes with SETSLOT / REBOOT itself */
        closeHid();
        updateProgress(100, tr("Slot programmed"));
        log(tr("Slot programmed, the board stays in the bootloader"));
        Q_EMIT finished(true, tr("Slot programmed"));
        return;
    }

    if (!endUpgrade()) {
        closeHid();
        Q_EMIT finished(false, tr("Failed to finish the upgrade"));
        return;
    }

    closeHid();

    updateProgress(100, tr("Upgrade complete"));
    log(tr("========== Firmware upgrade succeeded =========="));
    Q_EMIT finished(true, tr("Firmware upgrade succeeded, the device will restart"));
}
