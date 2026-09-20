/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * IAP 升级工作线程：在后台完成 进入IAP -> 擦除 -> 编程 -> 校验 -> 结束
 *
 * 协议与固件 CH32H417_Logic_Analyzer_IAP/Common/iap.c 一致：
 *   命令包 64 字节： [0]=命令  [1]=长度  [2..]=参数/数据
 *   响应包 64 字节： [0]=0x00  [1]=错误码(0=成功)
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef IAPWORKER_H
#define IAPWORKER_H

#include <QObject>
#include <QString>
#include <QMutex>
#include <QByteArray>
#include <QtGlobal>

/* IAP 命令字 */
#define CMD_IAP_PROM    0x80    /* 编程 */
#define CMD_IAP_ERASE   0x81    /* 擦除 */
#define CMD_IAP_VERIFY  0x82    /* 校验 */
#define CMD_IAP_END     0x83    /* 结束 */
#define CMD_JUMP_IAP    0x84    /* 跳转/成功标志 */

/* 数据包长度 */
#define IAP_DATA_LEN        64  /* IAP 数据包长度 */
#define HID_PACKET_LEN      65  /* HID 报文长度（含 Report ID） */
#define HID_REPORT_ID       0   /* HID Report ID */
#define HID_TIMEOUT_MS      500 /* 默认超时 */

/* 单次编程/校验的最大有效数据长度 */
#define IAP_PROGRAM_MAX     62  /* 2 字节命令头 + 62 字节数据 = 64 */
#define IAP_VERIFY_MAX      56  /* 2 字节命令头 + 4 字节地址 + 56 字节数据 = 62 */

/**
 * IAP 升级工作线程
 */
class IapWorker : public QObject
{
    Q_OBJECT

public:
    /**
     * 升级参数
     */
    struct Config
    {
        QString firmwarePath;                   /* 固件文件 (.bin/.hex) */
        quint32 binBaseAddress = 0x08006000;    /* .bin 烧录基地址 */
        quint16 iapVid = 0x1A86;                /* IAP 模式 VID */
        quint16 iapPid = 0xFE17;                /* IAP 模式 PID */
        int ch375Index = -1;                    /* APP 模式下的 CH375 索引，-1 表示直接走 HID */
        bool alreadyInIap = false;              /* 设备是否已经在 IAP/HID 模式 */
        int hidWaitSeconds = 10;                /* 等待 HID 设备出现的秒数 */
    };

    explicit IapWorker(const Config &config, QObject *parent = nullptr);
    ~IapWorker();

    const Config &config() const { return config_; }

Q_SIGNALS:
    void progressUpdated(int percent, const QString &status);
    void logMessage(const QString &message);
    void finished(bool success, const QString &message);

public Q_SLOTS:
    void run();
    void cancel();

private:
    /* HID 设备操作 */
    bool openHid(int waitSeconds);
    void closeHid();
    bool hidWrite(const quint8 *data, int len);
    bool hidRead(quint8 *data, int len, int timeoutMs);

    /* IAP 流程 */
    bool enterIapMode();
    bool eraseFlash(quint32 startAddr);
    bool programFlash(const quint8 *data, int len);
    bool verifyFlash(quint32 startAddr, const quint8 *data, int len);
    bool endUpgrade();

    /* 固件文件 */
    bool loadFirmware(QByteArray &outData, quint32 &startAddr);

    bool isCancelled();
    void log(const QString &message);
    void updateProgress(int percent, const QString &status);

private:
    Config config_;
    void *hidHandle_;
    bool cancelled_;
    QMutex mutex_;
};

#endif /* IAPWORKER_H */
