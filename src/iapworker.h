/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * IAP upgrade worker: runs enter IAP -> erase -> program -> verify -> finish
 * in a background thread.
 *
 * Protocol matching the firmware CH32H417_Logic_Analyzer_IAP/Common/iap.c:
 *   command packet, 64 bytes: [0]=command  [1]=length  [2..]=parameters/data
 *   response packet, 64 bytes: [0]=0x00    [1]=error code (0 = success)
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

/* IAP command bytes */
#define CMD_IAP_PROM    0x80    /* Program */
#define CMD_IAP_ERASE   0x81    /* Erase */
#define CMD_IAP_VERIFY  0x82    /* Verify */
#define CMD_IAP_END     0x83    /* Finish */
#define CMD_JUMP_IAP    0x84    /* Jump / success flag */

/* Packet lengths */
#define IAP_DATA_LEN        64  /* IAP data packet length */
#define HID_PACKET_LEN      65  /* HID report length, including the report ID */
#define HID_REPORT_ID       0   /* HID report ID */
#define HID_TIMEOUT_MS      500 /* Default timeout */

/* Maximum payload of a single program / verify transfer */
#define IAP_PROGRAM_MAX     62  /* 2 bytes header + 62 bytes data = 64 */
#define IAP_VERIFY_MAX      56  /* 2 bytes header + 4 bytes address + 56 bytes data = 62 */

/**
 * Background worker performing the IAP upgrade.
 */
class IapWorker : public QObject
{
    Q_OBJECT

public:
    /**
     * Upgrade parameters.
     */
    struct Config
    {
        QString firmwarePath;                   /* Firmware file (.bin/.hex) */
        quint32 binBaseAddress = 0x08006000;    /* Programming base address for .bin */
        quint16 iapVid = 0x1A86;                /* VID in IAP mode */
        quint16 iapPid = 0xFE17;                /* PID in IAP mode */
        int ch375Index = -1;                    /* CH375 index in application mode, -1 goes straight to HID */
        bool viaLibusb = false;                 /* Application mode device reached through libusb / WinUSB */
        int libusbBus = 0;                      /* USB bus of the libusb device */
        int libusbAddress = 0;                  /* USB address of the libusb device */
        bool viaSerial = false;                 /* Application mode device reached through a CDC COM port */
        QString serialPort;                     /* COM port of the serial device, e.g. "COM5" */
        bool deviceBusy = false;                /* Device is held by another program, refuse to upgrade */
        bool alreadyInIap = false;              /* Device is already in IAP/HID mode */
        int hidWaitSeconds = 10;                /* Seconds to wait for the HID device to appear */
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
    /* HID device handling */
    bool openHid(int waitSeconds);
    void closeHid();
    bool hidWrite(const quint8 *data, int len);
    bool hidRead(quint8 *data, int len, int timeoutMs);

    /* IAP sequence */
    bool enterIapMode();
    bool eraseFlash(quint32 startAddr);
    bool programFlash(const quint8 *data, int len);
    bool verifyFlash(quint32 startAddr, const quint8 *data, int len);
    bool endUpgrade();

    /* Firmware file */
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
