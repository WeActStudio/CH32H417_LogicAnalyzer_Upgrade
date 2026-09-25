/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * libusb device access layer implementation
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "libusbdev.h"
#include "ch375dev.h"

#include <QCoreApplication>

#include <libusb-1.0/libusb.h>

#include <cstring>

/* Application level commands (kept in sync with firmware ch32h417_logic.h) */
#define CMD_GET_VERSION     0xAC    /* Read version */
#define CMD_SET_IAP         0xAE    /* Switch to IAP download mode */
#define CMD_RETURN_PARA     0x10    /* Command response flag */

/* Command channel packet lengths: 64 bytes out (EP 0x01), 32 bytes in (EP 0x81) */
#define CMD_PACKET_LEN      64
#define RESP_PACKET_LEN     32

#define USB_INTERFACE       0       /* The device exposes a single interface */
#define USB_TIMEOUT_MS      1000

namespace {

libusb_context *context_ = nullptr;
bool initFailed_ = false;

/** Human readable libusb error text */
QString libusbError(int code)
{
    return QString::fromLatin1(libusb_error_name(code));
}

QString trText(const char *text)
{
    return QCoreApplication::translate("LibusbDev", text);
}

/**
 * Look up an openable device by bus/address.
 *
 * Only the enumeration of the current instant is valid, so the device list is
 * walked again for every command: a board that has just re-enumerated (or that
 * was unplugged meanwhile) must not be addressed through a stale pointer.
 */
libusb_device *findDevice(int bus, int address)
{
    libusb_device **list = nullptr;
    const ssize_t count = libusb_get_device_list(context_, &list);
    libusb_device *found = nullptr;

    if (count < 0)
        return nullptr;

    for (ssize_t i = 0; i < count; ++i) {
        if (libusb_get_bus_number(list[i]) == bus
            && libusb_get_device_address(list[i]) == address) {
            found = list[i];
            libusb_ref_device(found);
            break;
        }
    }

    libusb_free_device_list(list, 1);
    return found;
}

/*
 * Open a device and claim its single interface.
 *
 * On Windows the interface is owned by WinUSB already, so the detach step is a
 * no-op; it is kept for the platforms where a kernel driver is still bound.
 */
bool openAndClaim(libusb_device *device, libusb_device_handle *&handle,
                  QString &errorMessage)
{
    const int openResult = libusb_open(device, &handle);
    if (openResult != LIBUSB_SUCCESS) {
        handle = nullptr;
        errorMessage = trText("Cannot open the USB device (libusb error %1). "
                          "The board must be bound to a generic USB driver "
                          "(WinUSB on Windows) and must not be in use by "
                          "another program.")
                           .arg(libusbError(openResult));
        return false;
    }

    if (libusb_has_capability(LIBUSB_CAP_SUPPORTS_DETACH_KERNEL_DRIVER)) {
        if (libusb_kernel_driver_active(handle, USB_INTERFACE) == 1)
            libusb_detach_kernel_driver(handle, USB_INTERFACE);
    }

    const int claimResult = libusb_claim_interface(handle, USB_INTERFACE);
    if (claimResult != LIBUSB_SUCCESS) {
        errorMessage = trText("Cannot claim the USB interface (libusb error %1). "
                          "Close other programs that use the device and try "
                          "again.")
                           .arg(libusbError(claimResult));
        libusb_close(handle);
        handle = nullptr;
        return false;
    }

    return true;
}

/** Run one command/response exchange on the command channel */
bool transfer(libusb_device_handle *handle, quint8 command,
              quint8 *response, QString &errorMessage)
{
    unsigned char packet[CMD_PACKET_LEN];
    std::memset(packet, 0, sizeof(packet));
    packet[0] = command;
    packet[1] = 0;

    int transferred = 0;
    int result = libusb_bulk_transfer(handle, LIBUSB_ENDPOINT_OUT | 1,
                                      packet, static_cast<int>(sizeof(packet)),
                                      &transferred, USB_TIMEOUT_MS);
    if (result != LIBUSB_SUCCESS) {
        errorMessage = trText("Failed to send command 0x%1 (libusb error %2)")
                           .arg(static_cast<unsigned>(command), 2, 16, QChar('0'))
                           .arg(libusbError(result));
        return false;
    }

    if (!response)
        return true;

    unsigned char resp[RESP_PACKET_LEN];
    std::memset(resp, 0, sizeof(resp));
    transferred = 0;
    result = libusb_bulk_transfer(handle, LIBUSB_ENDPOINT_IN | 1,
                                  resp, static_cast<int>(sizeof(resp)),
                                  &transferred, USB_TIMEOUT_MS);
    if (result != LIBUSB_SUCCESS) {
        errorMessage = trText("The device did not answer command 0x%1 (libusb error %2)")
                           .arg(static_cast<unsigned>(command), 2, 16, QChar('0'))
                           .arg(libusbError(result));
        return false;
    }

    std::memcpy(response, resp, RESP_PACKET_LEN);
    return true;
}

} // namespace

bool libusbdev_init(QString &errorMessage)
{
    if (context_)
        return true;

    if (initFailed_) {
        errorMessage = trText("libusb is not available");
        return false;
    }

    const int result = libusb_init(&context_);
    if (result != LIBUSB_SUCCESS) {
        context_ = nullptr;
        initFailed_ = true;
        errorMessage = trText("Unable to initialise libusb (error %1)").arg(libusbError(result));
        return false;
    }

    return true;
}

bool libusbdev_ready()
{
    return context_ != nullptr;
}

void libusbdev_cleanup()
{
    if (!context_)
        return;

    libusb_exit(context_);
    context_ = nullptr;
}

QList<Ch375DeviceInfo> libusbdev_enum_devices(quint16 matchVid, quint16 matchPid,
                                              QString &errorMessage)
{
    QList<Ch375DeviceInfo> list;

    if (!libusbdev_init(errorMessage))
        return list;

    libusb_device **devices = nullptr;
    const ssize_t count = libusb_get_device_list(context_, &devices);
    if (count < 0) {
        errorMessage = trText("Failed to enumerate the USB devices (libusb error %1)")
                           .arg(libusbError(static_cast<int>(count)));
        return list;
    }

    int found = 0;
    for (ssize_t i = 0; i < count && found < LIBUSBDEV_MAX_NUMBER; ++i) {
        libusb_device_descriptor descriptor;
        if (libusb_get_device_descriptor(devices[i], &descriptor) != LIBUSB_SUCCESS)
            continue;

        const quint16 vid = descriptor.idVendor;
        const quint16 pid = descriptor.idProduct;
        const bool vidOk = (matchVid == 0) || (vid == matchVid);
        const bool pidOk = (matchPid == 0) || (pid == matchPid)
                           || ch375dev_is_app_id(vid, pid);
        if (!vidOk || !pidOk)
            continue;

        /*
         * The serial number needs an open handle. How an open failure is
         * treated depends on the reason:
         *
         *   - LIBUSB_ERROR_NOT_SUPPORTED (the board is owned by another
         *     driver such as CH375WDM.sys): it belongs to the other channel
         *     and is skipped here on purpose.
         *   - LIBUSB_ERROR_ACCESS / LIBUSB_ERROR_BUSY: the board matches the
         *     USB IDs but another program is using it. It is still listed,
         *     flagged as busy, so the user sees why no upgrade is possible
         *     instead of a bare "no device found".
         */
        libusb_device_handle *handle = nullptr;
        const int openResult = libusb_open(devices[i], &handle);
        if (openResult != LIBUSB_SUCCESS) {
            if (openResult == LIBUSB_ERROR_ACCESS || openResult == LIBUSB_ERROR_BUSY) {
                Ch375DeviceInfo info;
                info.index = found;
                info.channel = DeviceChannel::Libusb;
                info.bus = libusb_get_bus_number(devices[i]);
                info.address = libusb_get_device_address(devices[i]);
                info.vid = vid;
                info.pid = pid;
                info.isIap = ch375dev_is_iap_id(vid, pid);
                info.busy = true;   /* serial number unknown, no open handle */
                list.append(info);
                ++found;
            }
            continue;
        }

        char serial[128] = {0};
        if (descriptor.iSerialNumber != 0) {
            libusb_get_string_descriptor_ascii(handle, descriptor.iSerialNumber,
                                               reinterpret_cast<unsigned char *>(serial),
                                               static_cast<int>(sizeof(serial)) - 1);
        }
        libusb_close(handle);

        Ch375DeviceInfo info;
        info.index = found;
        info.channel = DeviceChannel::Libusb;
        info.bus = libusb_get_bus_number(devices[i]);
        info.address = libusb_get_device_address(devices[i]);
        info.vid = vid;
        info.pid = pid;
        info.isIap = ch375dev_is_iap_id(vid, pid);
        info.serial = QString::fromLatin1(serial).toLower();
        list.append(info);

        ++found;
    }

    libusb_free_device_list(devices, 1);
    return list;
}

bool libusbdev_enter_iap(int bus, int address, QString &errorMessage)
{
    if (!libusbdev_init(errorMessage))
        return false;

    libusb_device *device = findDevice(bus, address);
    if (!device) {
        errorMessage = trText("The device is no longer present (bus %1, address %2)")
                           .arg(bus).arg(address);
        return false;
    }

    libusb_device_handle *handle = nullptr;
    if (!openAndClaim(device, handle, errorMessage)) {
        libusb_unref_device(device);
        return false;
    }

    const bool sent = transfer(handle, CMD_SET_IAP, nullptr, errorMessage);

    /*
     * The board resets immediately after the command, so releasing the
     * interface and closing the handle usually fails; that is expected and not
     * an error worth reporting.
     */
    libusb_release_interface(handle, USB_INTERFACE);
    libusb_close(handle);
    libusb_unref_device(device);

    if (!sent) {
        if (errorMessage.isEmpty())
            errorMessage = trText("Failed to send the enter-IAP-mode command");
        return false;
    }

    return true;
}

bool libusbdev_get_version(int bus, int address, quint8 &swVer, quint8 &hwVer,
                           QString &errorMessage)
{
    swVer = 0;
    hwVer = 0;

    if (!libusbdev_init(errorMessage))
        return false;

    libusb_device *device = findDevice(bus, address);
    if (!device) {
        errorMessage = trText("The device is no longer present (bus %1, address %2)")
                           .arg(bus).arg(address);
        return false;
    }

    libusb_device_handle *handle = nullptr;
    if (!openAndClaim(device, handle, errorMessage)) {
        libusb_unref_device(device);
        return false;
    }

    unsigned char response[RESP_PACKET_LEN];
    std::memset(response, 0, sizeof(response));
    const bool ok = transfer(handle, CMD_GET_VERSION, response, errorMessage);

    libusb_release_interface(handle, USB_INTERFACE);
    libusb_close(handle);
    libusb_unref_device(device);

    if (!ok)
        return false;

    if (response[0] != (CMD_GET_VERSION | CMD_RETURN_PARA)) {
        errorMessage = trText("Unexpected version response: 0x%1")
                           .arg(static_cast<unsigned>(response[0]), 2, 16, QChar('0'));
        return false;
    }

    swVer = response[3];
    hwVer = response[4];
    return true;
}
