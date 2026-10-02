/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * Serial (USB CDC / usbser) channel
 *
 * The WeAct Studio Logic Analyzer V2 USB-to-UART application (APP slot 1)
 * enumerates as a CDC composite device (VID 0x1A86 / PID 0x5540) with three
 * COM ports. It carries no vendor requests the tool could send; the only
 * channel that is always forwarded by usbser.sys is SET_LINE_CODING, and the
 * firmware reacts on its baud rate field: opening a port at 2048 baud makes
 * the board reboot into the IAP bootloader (HID, 1A86:FE17).
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SERIALDEV_H
#define SERIALDEV_H

#include <QList>
#include <QString>
#include <QtGlobal>

#include "ch375dev.h"

/* USB IDs (CH32H417_U2U_VID / CH32H417_U2U_PID) and the IAP trigger baud rate
 * (CH32H417_U2U_IAP_BAUD) are defined in ch375dev.h. */

/**
 * Enumerate the COM ports of the USB-to-UART application.
 *
 * The firmware exposes three CDC channels per board; all of them can trigger
 * the IAP entry, so only one entry per board is reported (the lowest numbered
 * interface), which keeps the device list at one line per board.
 *
 * @param errorMessage Set when the COM port enumeration itself fails
 */
QList<Ch375DeviceInfo> serialdev_enum_devices(QString &errorMessage);

/**
 * Reboot a board into IAP mode by opening comPort at the magic baud rate
 * (CH32H417_U2U_IAP_BAUD). The port is closed again right away; the board
 * then re-enumerates as the HID IAP device.
 *
 * @param comPort  COM port name, e.g. "COM5"
 * @param errorMessage Set on failure (port missing or held by another program)
 */
bool serialdev_enter_iap(const QString &comPort, QString &errorMessage);

#endif /* SERIALDEV_H */
