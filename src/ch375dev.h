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

/* USB IDs of the USB-to-UART application (CDC composite device, serial
 * channel). USB 2.0 (USBHS) and USB 3.0 (USBSS) share the same PID on
 * purpose, so the host keeps the same COM port numbers at both speeds. */
#define CH32H417_U2U_VID    0x1A86
#define CH32H417_U2U_PID    0x5540

/* The baud rate that makes the USB-to-UART firmware reboot into IAP mode.
 * Kept in sync with DEF_U2U_IAP_BAUD in the firmware usb2uart.h. */
#define CH32H417_U2U_IAP_BAUD   2048u

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
 * Channel a device was found on. A board instance is claimed by a single
 * driver at a time, so it is reachable on exactly one of these:
 *
 *   Ch375  - CH375DLL.DLL / CH375WDM.sys (application mode)
 *   Libusb - generic USB driver (WinUSB on Windows), application mode
 *   Serial - the USB-to-UART application, a CDC device owned by usbser.sys
 *   Hid    - the IAP bootloader, seen by hidapi after the mode switch
 *
 * The USB protocol is identical on all of them, only the transport differs.
 */
enum class DeviceChannel
{
    Ch375,
    Libusb,
    Serial,
    Hid
};

/**
 * A single device reachable over the CH375 / libusb / HID channel.
 */
struct Ch375DeviceInfo
{
    int index = -1;         /* Index inside its own channel; -1 for HID (IAP) devices */
    DeviceChannel channel = DeviceChannel::Ch375;
    int bus = 0;            /* USB bus number (libusb channel), 0 when unknown */
    int address = 0;        /* USB device address (libusb channel), 0 when unknown */
    quint16 vid = 0;
    quint16 pid = 0;
    QString name;           /* Device path/name reported by the driver, may be empty */
    QString serial;         /* USB serial number (lower case), parsed from the device path */
    QString comPort;        /* COM port name (serial channel), e.g. "COM5" */
    bool isIap = false;     /* true = IAP upgrade mode (HID), false = application mode */
    bool busy = false;      /* true = the board matches the USB IDs but is held by
                             * another program / driver, so it cannot be opened */

    QString idString() const
    {
        return QString("VID:%1 PID:%2")
            .arg(vid, 4, 16, QChar('0'))
            .arg(pid, 4, 16, QChar('0'));
    }

    /** Product name derived from the serial number prefix; falls back to CH32H417 */
    QString modelName() const
    {
        /* The USB-to-UART PID belongs to the V2 USB-UART firmware alone */
        if (viaSerial() && pid == CH32H417_U2U_PID)
            return QStringLiteral("WeAct Studio Logic Analyzer V2");
        if (serial.startsWith(QLatin1String(CH32H417_SN_PREFIX_V2)))
            return QStringLiteral("WeAct Studio Logic Analyzer V2");
        if (serial.startsWith(QLatin1String(CH32H417_SN_PREFIX_V1)))
            return QStringLiteral("CH32H417 Logic Analyzer");
        return QStringLiteral("CH32H417");
    }

    /** True when the device is reached through libusb / WinUSB */
    bool viaLibusb() const { return channel == DeviceChannel::Libusb; }

    /** True when the device is reached through a CDC COM port (USB-to-UART app) */
    bool viaSerial() const { return channel == DeviceChannel::Serial; }

    /** Channel name shown in the logs and in the device list */
    QString channelName() const
    {
        switch (channel) {
        case DeviceChannel::Libusb:
            return QStringLiteral("libusb");
        case DeviceChannel::Serial:
            return QStringLiteral("serial");
        case DeviceChannel::Hid:
            return QStringLiteral("HID");
        case DeviceChannel::Ch375:
        default:
            return QStringLiteral("CH375");
        }
    }

    /** Full description used in the device list (moved into a tooltip when clipped) */
    QString description() const
    {
        /*
         * Application mode shows the index inside its channel; the serial
         * channel names the COM port instead, and IAP mode has neither, so it
         * gets a channel tag.
         */
        QString tag;
        if (isIap)
            tag = QStringLiteral("IAP");
        else if (viaSerial())
            tag = comPort;
        else if (viaLibusb())
            tag = QStringLiteral("USB#%1").arg(index);
        else
            tag = QStringLiteral("#%1").arg(index);
        QString text = QString("%1  %2  %3").arg(tag).arg(idString()).arg(modelName());
        if (!serial.isEmpty())
            text += QStringLiteral("  SN:%1").arg(serial);
        if (!isIap)
            text += QStringLiteral("  (%1)").arg(channelName());
        if (busy)
            text += QStringLiteral("  [in use]");
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
    IapBootloader,  /* Already in IAP / HID mode */
    DeviceBusy      /* Board visible on the bus but held by another program */
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
 * Read the firmware version of a device, whichever channel it was found on.
 * Wrapper around ch375dev_get_version() / libusbdev_get_version().
 */
bool ch375dev_get_version_for(const Ch375DeviceInfo &device, quint8 &swVer,
                              quint8 &hwVer, QString &errorMessage);

/**
 * Send the "enter IAP mode" command to a device, whichever channel it was
 * found on. Wrapper around ch375dev_enter_iap() / libusbdev_enter_iap().
 */
bool ch375dev_enter_iap_for(const Ch375DeviceInfo &device, QString &errorMessage);

/**
 * Determine the current mode of the device.
 *
 * All channels are scanned: the CH375 channel, the HID channel (boards that
 * already sit in the bootloader), the libusb channel (boards bound to a
 * generic USB driver such as WinUSB) and the serial channel (boards running
 * the USB-to-UART application, seen as COM ports). A missing CH375 driver is
 * not an error any more as long as another channel can see the board.
 *
 * @param appIndex   Output: CH375 index in application mode, -1 if not found
 *                   or if the board was found on another channel
 * @param appDevice  Output: the first application mode device found, on
 *                   whichever channel; invalid when nothing was found
 * @param deviceList Output: all enumerated CH32H417 devices
 */
DeviceMode ch375dev_detect(quint16 appVid, quint16 appPid,
                           quint16 iapVid, quint16 iapPid,
                           int &appIndex,
                           Ch375DeviceInfo &appDevice,
                           QList<Ch375DeviceInfo> &deviceList,
                           QString &errorMessage);

#endif /* CH375DEV_H */
