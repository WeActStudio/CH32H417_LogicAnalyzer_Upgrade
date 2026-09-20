/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * IAP 升级工作线程实现
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "iapworker.h"
#include <QCoreApplication>
#include "firmwareimage.h"
#include "ch375dev.h"

#include <hidapi.h>

#include <QThread>
#include <QFileInfo>
#include <QDateTime>

#include <cstring>

namespace {

/* hid_error() 在 Windows 上返回 wchar_t* */
QString hid_error_string(hid_device *dev)
{
    const wchar_t *msg = ::hid_error(dev);
    if (!msg)
        return QCoreApplication::translate("IapWorker", "未知错误");
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
 * HID 设备操作
 * ========================================================================== */

bool IapWorker::openHid(int waitSeconds)
{
    static bool hidInitialized = false;
    if (!hidInitialized) {
        if (::hid_init() != 0) {
            log(tr("hidapi 初始化失败"));
            return false;
        }
        hidInitialized = true;
    }

    const int maxTries = qMax(1, waitSeconds) * 2;   /* 每 500ms 尝试一次 */

    for (int i = 0; i < maxTries; ++i) {
        if (isCancelled()) {
            log(tr("已取消：等待 IAP 设备"));
            return false;
        }

        hidHandle_ = ::hid_open(config_.iapVid, config_.iapPid, nullptr);
        if (hidHandle_) {
            ::hid_set_nonblocking(static_cast<hid_device *>(hidHandle_), 1);
            log(tr("已连接 IAP 设备 (VID:0x%1 PID:0x%2)")
                    .arg(config_.iapVid, 4, 16, QChar('0'))
                    .arg(config_.iapPid, 4, 16, QChar('0')));
            return true;
        }

        if (i == 0)
            log(tr("等待 IAP 设备出现 (VID:0x%1 PID:0x%2) ...")
                    .arg(config_.iapVid, 4, 16, QChar('0'))
                    .arg(config_.iapPid, 4, 16, QChar('0')));

        QThread::msleep(500);
    }

    log(tr("未找到 IAP 设备，已等待 %1 秒").arg(waitSeconds));
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
            log(tr("写入被取消"));
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

        log(tr("HID 写入失败：%1")
                .arg(hid_error_string(static_cast<hid_device *>(hidHandle_))));
        return false;
    }

    log(tr("HID 写入超时 (%1 ms)").arg(HID_TIMEOUT_MS));
    return false;
}

bool IapWorker::hidRead(quint8 *data, int len, int timeoutMs)
{
    if (!hidHandle_)
        return false;

    quint8 recvBuf[HID_PACKET_LEN];
    std::memset(recvBuf, 0, sizeof(recvBuf));

    int elapsed = 0;
    while (elapsed < timeoutMs) {
        if (isCancelled()) {
            log(tr("读取被取消"));
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

        log(tr("HID 读取失败：%1")
                .arg(hid_error_string(static_cast<hid_device *>(hidHandle_))));
        return false;
    }

    return false;   /* 超时由调用方决定如何提示 */
}

/* ==========================================================================
 * IAP 流程
 * ========================================================================== */

bool IapWorker::enterIapMode()
{
    if (isCancelled()) {
        log(tr("已取消升级"));
        return false;
    }

    if (config_.alreadyInIap) {
        log(tr("设备已处于 IAP 模式，跳过模式切换"));
        return true;
    }

    if (config_.ch375Index < 0) {
        log(tr("没有可用的 CH375 设备索引，无法发送切换命令"));
        return false;
    }

    log(tr("向设备 (CH375 索引 %1) 发送进入 IAP 模式命令 ...").arg(config_.ch375Index));

    QString error;
    if (!ch375dev_enter_iap(config_.ch375Index, error)) {
        log(tr("进入 IAP 模式失败：%1").arg(error));
        return false;
    }

    log(tr("命令已发送，等待设备复位并切换为 HID IAP 设备 ..."));

    for (int i = 0; i < 10; ++i) {
        if (isCancelled()) {
            log(tr("已取消升级"));
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

    log(tr("擦除 FLASH，起始地址 0x%1").arg(startAddr, 8, 16, QChar('0')));
    updateProgress(20, tr("擦除 FLASH ..."));

    quint8 cmd[IAP_DATA_LEN];
    std::memset(cmd, 0, sizeof(cmd));
    cmd[0] = CMD_IAP_ERASE;
    cmd[1] = 0;
    cmd[2] = static_cast<quint8>(startAddr & 0xFF);
    cmd[3] = static_cast<quint8>((startAddr >> 8) & 0xFF);
    cmd[4] = static_cast<quint8>((startAddr >> 16) & 0xFF);
    cmd[5] = static_cast<quint8>((startAddr >> 24) & 0xFF);

    if (!hidWrite(cmd, 6)) {
        log(tr("发送擦除命令失败"));
        return false;
    }

    quint8 resp[IAP_DATA_LEN];
    std::memset(resp, 0, sizeof(resp));
    if (!hidRead(resp, 2, 10000)) {
        log(tr("擦除响应超时"));
        return false;
    }

    if (resp[0] != 0x00 || resp[1] != 0x00) {
        log(tr("擦除失败，错误码：%1").arg(resp[1]));
        return false;
    }

    log(tr("擦除完成"));
    return true;
}

bool IapWorker::programFlash(const quint8 *data, int len)
{
    log(tr("编程 FLASH，共 %1 字节").arg(len));
    updateProgress(25, tr("编程 FLASH ..."));

    int offset = 0;
    int retryCount = 0;

    while (offset < len) {
        if (isCancelled()) {
            log(tr("已取消升级"));
            return false;
        }

        const int chunkSize = qMin(IAP_PROGRAM_MAX, len - offset);

        quint8 cmd[IAP_DATA_LEN];
        std::memset(cmd, 0, sizeof(cmd));
        cmd[0] = CMD_IAP_PROM;
        cmd[1] = static_cast<quint8>(chunkSize);
        std::memcpy(cmd + 2, data + offset, static_cast<size_t>(chunkSize));

        if (!hidWrite(cmd, 2 + chunkSize)) {
            log(tr("写入数据失败，偏移 %1").arg(offset));
            if (++retryCount > 3)
                return false;
            QThread::msleep(100);
            continue;
        }

        quint8 resp[IAP_DATA_LEN];
        std::memset(resp, 0, sizeof(resp));
        if (!hidRead(resp, 2, HID_TIMEOUT_MS)) {
            log(tr("编程响应超时，偏移 %1").arg(offset));
            if (++retryCount > 3)
                return false;
            QThread::msleep(100);
            continue;
        }

        if (resp[0] != 0x00 || resp[1] != 0x00) {
            log(tr("编程失败，错误码 %1，偏移 %2").arg(resp[1]).arg(offset));
            if (++retryCount > 3)
                return false;
            QThread::msleep(100);
            continue;
        }

        retryCount = 0;
        offset += chunkSize;

        const int percent = 25 + static_cast<int>(45LL * offset / len);
        updateProgress(percent, tr("编程 FLASH ... %1%").arg(offset * 100 / len));
    }

    /* 长度为 0 的包：通知固件数据发送完毕 */
    quint8 cmd[IAP_DATA_LEN];
    std::memset(cmd, 0, sizeof(cmd));
    cmd[0] = CMD_IAP_PROM;
    cmd[1] = 0;
    hidWrite(cmd, 2);

    log(tr("编程完成"));
    return true;
}

bool IapWorker::verifyFlash(quint32 startAddr, const quint8 *data, int len)
{
    log(tr("校验 FLASH ..."));
    updateProgress(70, tr("校验 FLASH ..."));

    int offset = 0;
    quint32 verifyAddr = startAddr;
    int retryCount = 0;

    while (offset < len) {
        if (isCancelled()) {
            log(tr("已取消升级"));
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
            log(tr("发送校验命令失败，偏移 %1").arg(offset));
            if (++retryCount > 3)
                return false;
            QThread::msleep(100);
            continue;
        }

        quint8 resp[IAP_DATA_LEN];
        std::memset(resp, 0, sizeof(resp));
        if (!hidRead(resp, 2, HID_TIMEOUT_MS)) {
            log(tr("校验响应超时，偏移 %1").arg(offset));
            if (++retryCount > 3)
                return false;
            QThread::msleep(100);
            continue;
        }

        if (resp[0] != 0x00 || resp[1] != 0x00) {
            log(tr("校验失败，错误码 %1，地址 0x%2")
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
        updateProgress(percent, tr("校验 FLASH ... %1%").arg(offset * 100 / len));
    }

    log(tr("校验成功"));
    return true;
}

bool IapWorker::endUpgrade()
{
    log(tr("发送升级结束命令 ..."));
    updateProgress(96, tr("结束升级 ..."));

    quint8 cmd[IAP_DATA_LEN];
    std::memset(cmd, 0, sizeof(cmd));
    cmd[0] = CMD_IAP_END;
    cmd[1] = 0;

    if (!hidWrite(cmd, 2)) {
        log(tr("发送结束命令失败"));
        return false;
    }

    /* 固件收到 END 后会直接复位跳转，通常不会有应答 */
    quint8 resp[IAP_DATA_LEN];
    std::memset(resp, 0, sizeof(resp));
    if (hidRead(resp, 2, 2000)) {
        if (resp[0] == CMD_JUMP_IAP)
            log(tr("设备确认升级完成"));
    } else {
        log(tr("设备已复位（无应答属正常现象）"));
    }

    return true;
}

/* ==========================================================================
 * 固件加载与主流程
 * ========================================================================== */

bool IapWorker::loadFirmware(QByteArray &outData, quint32 &startAddr)
{
    QString error;
    FirmwareImage image;

    updateProgress(3, tr("读取固件文件 ..."));

    if (!firmware_load(config_.firmwarePath, config_.binBaseAddress, image, error)) {
        log(tr("固件加载失败：%1").arg(error));
        return false;
    }

    log(tr("已加载固件：%1").arg(QFileInfo(config_.firmwarePath).fileName()));
    log(tr("  格式：%1，大小：%2 字节")
            .arg(image.fromHex ? tr("Intel HEX") : tr("BIN"))
            .arg(image.data.size()));
    log(tr("  地址范围：0x%1 - 0x%2")
            .arg(image.startAddress, 8, 16, QChar('0'))
            .arg(image.endAddress, 8, 16, QChar('0')));
    log(tr("  校验和：0x%1").arg(image.checksum, 8, 16, QChar('0')));

    if (image.data.isEmpty()) {
        log(tr("固件数据为空"));
        return false;
    }

    outData = image.data;
    startAddr = image.startAddress;
    return true;
}

void IapWorker::run()
{
    QString errorHint;

    updateProgress(1, tr("开始升级 ..."));
    log(tr("========== 开始固件升级 %1 ==========")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));

    QByteArray firmwareData;
    quint32 startAddr = 0;

    if (!loadFirmware(firmwareData, startAddr)) {
        Q_EMIT finished(false, tr("固件文件加载失败"));
        return;
    }

    /* 1. 进入 IAP 模式 */
    updateProgress(10, tr("进入 IAP 模式 ..."));
    if (!enterIapMode()) {
        Q_EMIT finished(false, tr("无法进入 IAP 模式"));
        return;
    }

    /* 2. 连接 HID IAP 设备 */
    updateProgress(15, tr("查找 IAP 设备 ..."));
    if (!openHid(config_.hidWaitSeconds)) {
        Q_EMIT finished(false, tr("未找到 IAP 模式的设备"));
        return;
    }
    updateProgress(18, tr("已连接 IAP 设备"));

    /* 3. 擦除 */
    if (!eraseFlash(startAddr)) {
        closeHid();
        Q_EMIT finished(false, tr("擦除 FLASH 失败"));
        return;
    }

    /* 4. 编程 */
    if (!programFlash(reinterpret_cast<const quint8 *>(firmwareData.constData()),
                      firmwareData.size())) {
        closeHid();
        Q_EMIT finished(false, tr("编程 FLASH 失败"));
        return;
    }

    /* 5. 校验 */
    if (!verifyFlash(startAddr,
                     reinterpret_cast<const quint8 *>(firmwareData.constData()),
                     firmwareData.size())) {
        closeHid();
        Q_EMIT finished(false, tr("校验 FLASH 失败"));
        return;
    }

    /* 6. 结束 */
    if (!endUpgrade()) {
        closeHid();
        Q_EMIT finished(false, tr("结束升级失败"));
        return;
    }

    closeHid();

    updateProgress(100, tr("升级完成"));
    log(tr("========== 固件升级成功 =========="));
    Q_EMIT finished(true, tr("固件升级成功，设备将重新启动"));
}
