/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * IAP control commands implementation: reboot and slot switch
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "iapctl.h"

#include <QCoreApplication>

#include <hidapi.h>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include <cstring>

namespace {

/* Same report layout as the upgrade worker uses */
const int kReportLen = 65;             /* HID report, including the report id */
const unsigned char kReportId = 0;

/* The firmware answers before it acts, so a second is plenty */
const int kAckTimeoutMs = 2000;
const int kAckPollMs = 20;

QString trText(const char *text)
{
    return QCoreApplication::translate("IapCtl", text);
}

bool hid_ready()
{
    static bool initialized = false;
    if (!initialized) {
        if (::hid_init() != 0)
            return false;
        initialized = true;
    }
    return true;
}

/* Read the 2 byte answer: [0] = 0x00, [1] = error code */
bool readAck(hid_device *device, quint8 *errorCode, QString &errorMessage)
{
    for (int elapsed = 0; elapsed < kAckTimeoutMs; elapsed += kAckPollMs) {
        quint8 resp[kReportLen];
        std::memset(resp, 0, sizeof(resp));

        const int result = ::hid_read(device, resp, sizeof(resp));
        if (result >= 2) {
            if (resp[0] != 0x00) {
                errorMessage = trText("Unexpected answer from the bootloader: 0x%1")
                                   .arg(static_cast<unsigned>(resp[0]), 2, 16, QChar('0'));
                return false;
            }
            *errorCode = resp[1];
            return true;
        }

        Sleep(kAckPollMs);
    }

    errorMessage = trText("The bootloader did not answer (timeout)");
    return false;
}

/*
 * Open the bootloader, send one command and read its answer. cmd[0] is the
 * command byte, cmd[1] the payload length, cmd[2..] the payload.
 */
bool sendCommand(quint16 vid, quint16 pid, quint8 command,
                 const quint8 *payload, int payloadLen, QString &errorMessage)
{
    errorMessage.clear();

    if (!hid_ready()) {
        errorMessage = trText("Failed to initialize hidapi");
        return false;
    }

    hid_device *device = ::hid_open(vid, pid, nullptr);
    if (!device) {
        errorMessage = trText(
            "No IAP device found (VID:0x%1 PID:0x%2).\n"
            "These commands only work while the board sits in the bootloader.")
                           .arg(vid, 4, 16, QChar('0'))
                           .arg(pid, 4, 16, QChar('0'));
        return false;
    }

    /* Non-blocking plus a polling loop, the same approach the worker uses */
    ::hid_set_nonblocking(device, 1);

    quint8 cmd[64];
    std::memset(cmd, 0, sizeof(cmd));
    cmd[0] = command;
    cmd[1] = static_cast<quint8>(payloadLen);
    if (payloadLen > 0 && payload)
        std::memcpy(cmd + 2, payload, static_cast<size_t>(payloadLen));

    quint8 report[kReportLen];
    std::memset(report, 0, sizeof(report));
    report[0] = kReportId;
    std::memcpy(report + 1, cmd, sizeof(cmd));

    bool written = false;
    for (int attempt = 0; attempt < 5 && !written; ++attempt) {
        written = ::hid_write(device, report, kReportLen) > 0;
        if (!written)
            Sleep(kAckPollMs);
    }

    if (!written) {
        errorMessage = trText("Failed to send command 0x%1 to the bootloader")
                           .arg(static_cast<unsigned>(command), 2, 16, QChar('0'));
        ::hid_close(device);
        return false;
    }

    quint8 errorCode = 0;
    const bool answered = readAck(device, &errorCode, errorMessage);
    ::hid_close(device);

    if (!answered)
        return false;

    if (errorCode != 0) {
        errorMessage = trText("The bootloader refused the request (error code %1)")
                           .arg(errorCode);
        return false;
    }

    return true;
}

} // namespace

quint32 iapctl_slot_base_address(int slot)
{
    /* Kept in sync with the firmware APP_SLOT_ADDR() */
    switch (slot) {
    case 0:
        return 0x08006000u;
    case 1:
        return 0x08052000u;
    case 2:
        return 0x0809E000u;
    default:
        return 0;
    }
}

bool iapctl_reboot(quint16 vid, quint16 pid, QString &errorMessage)
{
    /* No payload: the firmware just resets into the active slot */
    return sendCommand(vid, pid, CMD_IAP_REBOOT, nullptr, 0, errorMessage);
}

bool iapctl_set_slot(quint16 vid, quint16 pid, int slot, QString &errorMessage)
{
    if (slot < 0 || slot >= IAP_APP_SLOT_NUM) {
        errorMessage = trText("Slot number out of range (0..%1)").arg(IAP_APP_SLOT_NUM - 1);
        return false;
    }

    const quint8 payload = static_cast<quint8>(slot);
    return sendCommand(vid, pid, CMD_IAP_SETSLOT, &payload, 1, errorMessage);
}