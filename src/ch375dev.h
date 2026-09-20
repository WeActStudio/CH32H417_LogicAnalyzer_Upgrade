/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * CH375 device access layer: enumeration / version query / entering IAP mode
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef CH375DEV_H
#define CH375DEV_H

#include <QList>
#include <QString>
#include <QtGlobal>

/* USB IDs of the CH32H417 seen on the CH375 channel (application / run mode).
 * The PID is fixed at 0x5537 for every board revision; the serial number prefix
 * tells the boards apart (see below). */
#define CH32H417_APP_VID    0x1A86
#define CH32H417_APP_PID    0x5537

/* USB IDs of the CH32H417 in IAP (bootloader) mode (HID channel) */
#define CH32H417_IAP_VID    0x1A86
#define CH32H417_IAP_PID    0xFE17

/* Pipe number of the command channel */
#define CH32H417_PIPE_CMD   1

/*
 * USB serial number prefix -> product name.
 *
 * Kept in sync with the firmware / device naming:
 *   serial starting with b5 -> WeAct Studio Logic Analyzer V2
 *   serial starting with 01 -> CH32H417 Logic Analyzer
 */
#define CH32H417_SN_PREFIX_V2   "b5"
#define CH32H417_SN_PREFIX_V1   "01"

/**
 * A single device reachable over the CH375 / HID channel.
 */
struct Ch375DeviceInfo
{
    int index = -1;         /* CH375 device index 0..15; -1 for HID (IAP) devices */
    quint16 vid = 0;
    quint16 pid = 0;
    QString name;           /* Device path/name reported by the driver, may be empty */
    QString serial;         /* USB serial number (lower case), parsed from the device path */
    bool isIap = false;     /* true = IAP upgrade mode (HID), false = application mode (CH375) */

    QString idString() const
    {
        return QString("VID:%1 PID:%2")
            .arg(vid, 4, 16, QChar('0'))
            .arg(pid, 4, 16, QChar('0'));
    }

    /** Product name derived from the serial number prefix; falls back to CH32H417 */
    QString modelName() const
    {
        if (serial.startsWith(QLatin1String(CH32H417_SN_PREFIX_V2)))
            return QStringLiteral("WeAct Studio Logic Analyzer V2");
        if (serial.startsWith(QLatin1String(CH32H417_SN_PREFIX_V1)))
            return QStringLiteral("CH32H417 Logic Analyzer");
        return QStringLiteral("CH32H417");
    }

    /** Full description used in the device list (moved into a tooltip when clipped) */
    QString description() const
    {
        /* Application mode shows the CH375 index; IAP mode has none, use a channel tag */
        const QString tag = isIap ? QStringLiteral("IAP")
                                  : QStringLiteral("#%1").arg(index);
        QString text = QString("%1  %2  %3").arg(tag).arg(idString()).arg(modelName());
        if (!serial.isEmpty())
            text += QStringLiteral("  SN:%1").arg(serial);
        return text;
    }
};

/**
 * Current mode of the attached device.
 */
enum class DeviceMode
{
    NotFound,       /* No device found */
    AppRunning,     /* Application running (visible on the CH375 channel) */
    IapBootloader   /* Already in IAP / HID mode */
};

/**
 * Load CH375DLL. On failure errorMessage carries the reason.
 */
bool ch375dev_init(QString &errorMessage);

/**
 * Check whether a VID/PID pair is a CH32H417 in application (run) mode on the
 * CH375 channel: 1A86:5537.
 */
bool ch375dev_is_app_id(quint16 vid, quint16 pid);

/**
 * Check whether a VID/PID pair is an IAP (bootloader) device: 1A86:FE17, the
 * HID device the board enumerates as after the enter-IAP command.
 */
bool ch375dev_is_iap_id(quint16 vid, quint16 pid);

/**
 * Enumerate the devices on the CH375 channel.
 * @param matchVid VID filter, 0 means no filtering
 * @param matchPid PID filter, 0 means no filtering
 */
QList<Ch375DeviceInfo> ch375dev_enum_devices(quint16 matchVid, quint16 matchPid,
                                             QString &errorMessage);

/**
 * Enumerate the HID devices that are already in IAP upgrade mode.
 * @param matchVid VID filter, 0 means no filtering
 * @param matchPid PID filter, 0 means no filtering
 */
QList<Ch375DeviceInfo> ch375dev_enum_hid_devices(quint16 matchVid, quint16 matchPid);

/**
 * Read the firmware version (CMD_GET_VERSION).
 * @param swVer Software version
 * @param hwVer Hardware version
 */
bool ch375dev_get_version(int index, quint8 &swVer, quint8 &hwVer,
                          QString &errorMessage);

/**
 * Send the "enter IAP mode" command (CMD_SET_IAP = 0xAE).
 * On success the device resets and reappears as a HID IAP device.
 */
bool ch375dev_enter_iap(int index, QString &errorMessage);

/**
 * Check whether the given HID device is present.
 */
bool ch375dev_hid_present(quint16 vid, quint16 pid);

/**
 * Determine the current mode of the device.
 * @param appIndex   Output: CH375 device index in application mode, -1 if not found
 * @param deviceList Output: all enumerated CH32H417 devices
 */
DeviceMode ch375dev_detect(quint16 appVid, quint16 appPid,
                           quint16 iapVid, quint16 iapPid,
                           int &appIndex,
                           QList<Ch375DeviceInfo> &deviceList,
                           QString &errorMessage);

#endif /* CH375DEV_H */
