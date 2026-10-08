/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * IAP control commands: reboot and slot switch
 *
 * The IAP firmware understands two host commands besides the upgrade flow
 * (CH32H417_Logic_Analyzer_IAP/Common/iap.h):
 *
 *   0x85 CMD_IAP_REBOOT  - answer, then soft-reset the chip; the boot walks the
 *                          power-on path again and runs the active slot
 *   0x86 CMD_IAP_SETSLOT - data[0] = slot: store it in the config area and boot
 *                          it right away (same path as CMD_IAP_END, but this one
 *                          does answer first)
 *
 * Both are single instant commands, so they live here instead of in the
 * upgrade worker - no progress, no thread, no firmware file involved. They only
 * exist while the board sits in the bootloader (HID), which is exactly when the
 * upgrade tool detects it as an IAP device.
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef IAPCTL_H
#define IAPCTL_H

#include <QString>
#include <QtGlobal>

/* Command bytes, kept in sync with the firmware iap.h */
#define CMD_IAP_REBOOT        0x85
#define CMD_IAP_SETSLOT       0x86

/* Number of APP slots the bootloader knows (slot 0 .. 2) */
#define IAP_APP_SLOT_NUM      3

/**
 * Flash base address of an APP slot.
 *
 * Single source of truth for the three slots: the bootloader only accepts
 * exactly these bases (IAP_SlotOfBase), and the UI shows them both in the BIN
 * base address dropdown and in the slot switch menu.
 *
 * @param slot Slot index (0 .. 2)
 * @return Base address, 0 for an out of range slot
 */
quint32 iapctl_slot_base_address(int slot);

/**
 * Reboot the board into the currently active slot.
 *
 * The firmware answers first and resets afterwards, so the acknowledgement is
 * read normally; only then does the board disappear from the bus.
 *
 * @param vid IAP mode VID (0x1A86)
 * @param pid IAP mode PID (0xFE17)
 * @param errorMessage Set on failure
 * @return true when the board acknowledged the request
 */
bool iapctl_reboot(quint16 vid, quint16 pid, QString &errorMessage);

/**
 * Make another slot the active one and boot it immediately.
 *
 * The firmware refuses slots that are out of range or empty, and answers with
 * an error code in that case.
 *
 * @param slot Slot index (0 .. 2)
 * @param errorMessage Set on failure
 * @return true when the board accepted the switch
 */
bool iapctl_set_slot(quint16 vid, quint16 pid, int slot, QString &errorMessage);

#endif /* IAPCTL_H */