/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * libusb device access layer: enumeration of the boards that are bound to a
 * generic USB driver (WinUSB on Windows) and sending the "enter IAP mode"
 * command over that channel.
 *
 * This is the counterpart of ch375dev.cpp. Both channels speak exactly the
 * same USB protocol — the endpoints and the command packets are unchanged —
 * they only differ in which driver owns the device:
 *
 *   CH375 channel : CH375DLL.DLL / CH375WDM.sys   (ch375dev.cpp)
 *   libusb channel: WinUSB / libusb               (this file)
 *
 * A device instance can only be claimed by one driver at a time, so a board
 * shows up on one channel or on the other, never on both. Enumerating both
 * and using whichever answers is therefore enough; no configuration is needed.
 *
 * Endpoint layout (from the firmware's USB descriptors):
 *   EP 0x01 / 0x81   command channel, 64 bytes out / 32 bytes in per packet
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef LIBUSBDEV_H
#define LIBUSBDEV_H

#include "ch375dev.h"

#include <QList>
#include <QString>
#include <QtGlobal>

/* Maximum number of libusb devices handled by one enumeration pass */
#define LIBUSBDEV_MAX_NUMBER    16

/**
 * Initialise libusb. Safe to call more than once; on failure errorMessage
 * carries the reason (the most common one is that no device is bound to a
 * driver libusb can use).
 */
bool libusbdev_init(QString &errorMessage);

/** True once libusb has been initialised successfully */
bool libusbdev_ready();

/** Release libusb; called on shutdown */
void libusbdev_cleanup();

/**
 * Enumerate the CH32H417 boards reachable through libusb.
 *
 * @param matchVid VID filter, 0 means no filtering
 * @param matchPid PID filter, 0 means the application PID 1A86:5537 is used
 *
 * Boards that are bound to another driver (the CH375 driver, for example)
 * cannot be opened and are skipped: they are handled on the CH375 channel.
 * Boards that match the USB IDs but are in use by another program are still
 * listed, with the busy flag set, so the UI can explain why they are unusable.
 */
QList<Ch375DeviceInfo> libusbdev_enum_devices(quint16 matchVid, quint16 matchPid,
                                              QString &errorMessage);

/**
 * Send the "enter IAP mode" command (CMD_SET_IAP = 0xAE) to the board at the
 * given USB bus/address. On success the device resets and reappears as the
 * HID IAP device (1A86:FE17).
 */
bool libusbdev_enter_iap(int bus, int address, QString &errorMessage);

/**
 * Read the firmware version (CMD_GET_VERSION = 0xAC) from the board at the
 * given USB bus/address.
 */
bool libusbdev_get_version(int bus, int address, quint8 &swVer, quint8 &hwVer,
                           QString &errorMessage);

#endif /* LIBUSBDEV_H */
