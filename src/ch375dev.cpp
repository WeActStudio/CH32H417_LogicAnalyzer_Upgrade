/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * CH375 device access layer implementation
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "ch375dev.h"
#include <QCoreApplication>

#include "ch375_wrapper.h"
#include "libusbdev.h"
#include <hidapi.h>

#include <cstring>

/* Application level commands (kept in sync with firmware ch32h417_logic.h) */
#define CMD_GET_VERSION     0xAC    /* Read version */
#define CMD_SET_IAP         0xAE    /* Switch to IAP download mode */
#define CMD_RETURN_PARA     0x10    /* Command response flag */

/* Command channel packet length */
#define CMD_PACKET_LEN      64

namespace {

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

/*
 * Extract the USB serial number (lower case) from the device path returned by
 * CH375. The path looks like:
 *   \\?\usb#vid_1a86&pid_5537#b5e339e33906e19c7f6416064c#{5e7f6bdf-...}
 * The instance serial number sits between the 2nd and the 3rd '#'.
 */
QString extractUsbSerial(const char *devicePath)
{
    if (!devicePath || !*devicePath)
        return QString();

    const QString path = QString::fromLocal8Bit(devicePath);

    int first = path.indexOf(QLatin1Char('#'));
    if (first < 0)
        return QString();

    int second = path.indexOf(QLatin1Char('#'), first + 1);
    if (second < 0)
        return QString();

    int third = path.indexOf(QLatin1Char('#'), second + 1);
    if (third < 0)
        return QString();

    return path.mid(second + 1, third - second - 1).toLower();
}

} // namespace

namespace {

/*
 * Message shown when a board that is visible on the bus is held by another
 * program (the logic analyzer software, for example), so the upgrade tool
 * cannot open it.
 */
QString busyDeviceError()
{
    return QCoreApplication::translate(
        "Ch375Dev",
        "The device is in use by another program.\n"
        "Close the program that currently uses the board "
        "(for example the logic analyzer software) and refresh.");
}

} // namespace

bool ch375dev_is_iap_id(quint16 vid, quint16 pid)
{
    return vid == CH32H417_IAP_VID && pid == CH32H417_IAP_PID;
}

bool ch375dev_is_app_id(quint16 vid, quint16 pid)
{
    return vid == CH32H417_APP_VID && pid == CH32H417_APP_PID;
}

bool ch375dev_init(QString &errorMessage)
{
    if (ch375_init() != 0) {
        errorMessage = QCoreApplication::translate(
                           "Ch375Dev",
                           "Unable to load CH375DLL64.DLL / CH375DLL.DLL.\n"
                           "Make sure the CH375 driver is installed and that the "
                           "driver DLL is placed next to this program or in a "
                           "directory on the system search path.");
        return false;
    }
    return true;
}

QList<Ch375DeviceInfo> ch375dev_enum_devices(quint16 matchVid, quint16 matchPid,
                                             QString &errorMessage)
{
    QList<Ch375DeviceInfo> list;

    if (!ch375_is_loaded()) {
        if (!ch375dev_init(errorMessage))
            return list;
    }

    for (unsigned long i = 0; i < CH375_MAX_NUMBER; ++i) {
        void *handle = ch375_open_device(i);
        if (handle == CH375_INVALID_HANDLE)
            continue;

        const unsigned long usbId = ch375_get_usb_id(i);
        const quint16 vid = static_cast<quint16>(usbId & 0xFFFF);
        const quint16 pid = static_cast<quint16>(usbId >> 16);

        /* Accept the run mode ID on the CH375 channel: 1A86:5537 */
        const bool vidOk = (matchVid == 0) || (vid == matchVid);
        const bool pidOk = (matchPid == 0) || (pid == matchPid) || ch375dev_is_app_id(vid, pid);

        if (vidOk && pidOk) {
            Ch375DeviceInfo info;
            info.index = static_cast<int>(i);
            info.channel = DeviceChannel::Ch375;
            info.vid = vid;
            info.pid = pid;
            info.isIap = ch375dev_is_iap_id(vid, pid);

            /* The device path carries the USB serial number, used to identify the
             * exact product (a "b5" prefix means Logic Analyzer V2). */
            const char *devicePath = ch375_get_device_name(i);
            if (devicePath)
                info.name = QString::fromLocal8Bit(devicePath);
            info.serial = extractUsbSerial(devicePath);

            list.append(info);
        }

        ch375_close_device(i);
    }

    return list;
}

/*
 * Enumerate the HID devices that are already in IAP upgrade mode.
 *
 * After entering IAP the device resets into a HID device (1A86:FE17). It is no
 * longer visible on the CH375 channel and only hidapi can see it, so it is
 * enumerated separately to keep the device list complete.
 */
QList<Ch375DeviceInfo> ch375dev_enum_hid_devices(quint16 matchVid, quint16 matchPid)
{
    QList<Ch375DeviceInfo> list;

    if (!hid_ready())
        return list;

    hid_device_info *devs = ::hid_enumerate(matchVid, matchPid);
    for (hid_device_info *cur = devs; cur; cur = cur->next) {
        Ch375DeviceInfo info;
        info.index = -1;            /* HID devices have no CH375 index */
        info.channel = DeviceChannel::Hid;
        info.isIap = true;
        info.vid = cur->vendor_id;
        info.pid = cur->product_id;

        if (cur->path)
            info.name = QString::fromLocal8Bit(cur->path);
        if (cur->serial_number) {
            info.serial = QString::fromWCharArray(cur->serial_number).toLower();
            /*
             * Some firmware builds expose the instance serial number directly in
             * serial_number; others report a string such as
             * "b5e339e33906e19c7f6416064c". Both can be used to identify the
             * product.
             */
        }
        if (info.serial.isEmpty() && cur->path)
            info.serial = extractUsbSerial(cur->path);

        list.append(info);
    }
    ::hid_free_enumeration(devs);

    return list;
}

bool ch375dev_get_version(int index, quint8 &swVer, quint8 &hwVer,
                          QString &errorMessage)
{
    swVer = 0;
    hwVer = 0;

    if (index < 0) {
        errorMessage = QCoreApplication::translate("Ch375Dev", "Invalid device index");
        return false;
    }

    if (!ch375_is_loaded()) {
        if (!ch375dev_init(errorMessage))
            return false;
    }

    void *handle = ch375_open_device(static_cast<unsigned long>(index));
    if (handle == CH375_INVALID_HANDLE) {
        errorMessage = QCoreApplication::translate("Ch375Dev", "Cannot open CH375 device (index %1)").arg(index);
        return false;
    }

    unsigned char cmd[CMD_PACKET_LEN];
    std::memset(cmd, 0, sizeof(cmd));
    cmd[0] = CMD_GET_VERSION;
    cmd[1] = 0;

    ch375_set_timeout_ex(static_cast<unsigned long>(index), 1000, 1000, 1000, 1000);

    unsigned long length = CMD_PACKET_LEN;
    bool ok = ch375_write_endpoint(static_cast<unsigned long>(index),
                                   CH32H417_PIPE_CMD, cmd, &length) != 0;

    unsigned char resp[CMD_PACKET_LEN];
    std::memset(resp, 0, sizeof(resp));

    if (ok) {
        length = CMD_PACKET_LEN;
        ok = ch375_read_endpoint(static_cast<unsigned long>(index),
                                 CH32H417_PIPE_CMD, resp, &length) != 0;
    }

    if (!ok) {
        ch375_close_device(static_cast<unsigned long>(index));
        errorMessage = QCoreApplication::translate("Ch375Dev", "Failed to read firmware version (device did not respond)");
        return false;
    }

    ch375_close_device(static_cast<unsigned long>(index));

    if (resp[0] != (CMD_GET_VERSION | CMD_RETURN_PARA)) {
        errorMessage = QCoreApplication::translate("Ch375Dev", "Unexpected version response: 0x%1")
                           .arg(static_cast<unsigned>(resp[0]), 2, 16, QChar('0'));
        return false;
    }

    swVer = resp[3];
    hwVer = resp[4];
    return true;
}

bool ch375dev_enter_iap(int index, QString &errorMessage)
{
    if (index < 0) {
        errorMessage = QCoreApplication::translate("Ch375Dev", "Invalid device index");
        return false;
    }

    if (!ch375_is_loaded()) {
        if (!ch375dev_init(errorMessage))
            return false;
    }

    void *handle = ch375_open_device(static_cast<unsigned long>(index));
    if (handle == CH375_INVALID_HANDLE) {
        errorMessage = QCoreApplication::translate("Ch375Dev", "Cannot open CH375 device (index %1)").arg(index);
        return false;
    }

    unsigned char cmd[CMD_PACKET_LEN];
    std::memset(cmd, 0, sizeof(cmd));
    cmd[0] = CMD_SET_IAP;   /* Tell the application to set the IAP flag and reset */
    cmd[1] = 0;

    ch375_set_timeout_ex(static_cast<unsigned long>(index), 1000, 1000, 1000, 1000);

    unsigned long length = CMD_PACKET_LEN;
    const bool ok = ch375_write_endpoint(static_cast<unsigned long>(index),
                                         CH32H417_PIPE_CMD, cmd, &length) != 0;

    ch375_close_device(static_cast<unsigned long>(index));

    if (!ok) {
        errorMessage = QCoreApplication::translate("Ch375Dev", "Failed to send the enter-IAP-mode command");
        return false;
    }

    return true;
}

bool ch375dev_hid_present(quint16 vid, quint16 pid)
{
    if (!hid_ready())
        return false;

    hid_device_info *devs = ::hid_enumerate(vid, pid);
    if (!devs)
        return false;

    ::hid_free_enumeration(devs);
    return true;
}

bool ch375dev_get_version_for(const Ch375DeviceInfo &device, quint8 &swVer,
                              quint8 &hwVer, QString &errorMessage)
{
    if (device.busy) {
        swVer = 0;
        hwVer = 0;
        errorMessage = busyDeviceError();
        return false;
    }

    if (device.viaLibusb())
        return libusbdev_get_version(device.bus, device.address, swVer, hwVer, errorMessage);

    return ch375dev_get_version(device.index, swVer, hwVer, errorMessage);
}

bool ch375dev_enter_iap_for(const Ch375DeviceInfo &device, QString &errorMessage)
{
    if (device.busy) {
        errorMessage = busyDeviceError();
        return false;
    }

    if (device.viaLibusb())
        return libusbdev_enter_iap(device.bus, device.address, errorMessage);

    return ch375dev_enter_iap(device.index, errorMessage);
}

DeviceMode ch375dev_detect(quint16 appVid, quint16 appPid,
                           quint16 iapVid, quint16 iapPid,
                           int &appIndex,
                           Ch375DeviceInfo &appDevice,
                           QList<Ch375DeviceInfo> &deviceList,
                           QString &errorMessage)
{
    appIndex = -1;
    appDevice = Ch375DeviceInfo();
    deviceList.clear();

    /*
     * Every channel is scanned. A board is claimed by a single driver at a
     * time, so at most one channel reports it, and a missing CH375 driver must
     * not hide a board that libusb can reach.
     */
    QString ch375Error;
    if (ch375dev_init(ch375Error))
        deviceList += ch375dev_enum_devices(appVid, appPid, ch375Error);

    /* Devices already in IAP mode are enumerated over HID and added to the same
     * list, so the user can always see that the device is online. */
    deviceList += ch375dev_enum_hid_devices(iapVid, iapPid);

    /* Boards bound to a generic USB driver (WinUSB) are reached through libusb */
    QString libusbError;
    deviceList += libusbdev_enum_devices(appVid, appPid, libusbError);

    /* Prefer an application mode device for the version query / IAP switch.
     * Busy devices (held by another program) are listed but never selected. */
    for (const Ch375DeviceInfo &info : deviceList) {
        if (!info.isIap && !info.busy) {
            appDevice = info;
            appIndex = (info.channel == DeviceChannel::Ch375) ? info.index : -1;
            return DeviceMode::AppRunning;
        }
    }

    if (!deviceList.isEmpty()) {
        /* IAP (HID) devices are never busy; busy devices only appear on the
         * libusb channel, so "everything busy" means no usable device. */
        for (const Ch375DeviceInfo &info : deviceList) {
            if (!info.busy)
                return DeviceMode::IapBootloader;
        }
        return DeviceMode::DeviceBusy;
    }

    errorMessage = ch375Error;
    if (errorMessage.isEmpty())
        errorMessage = libusbError;

    return DeviceMode::NotFound;
}
