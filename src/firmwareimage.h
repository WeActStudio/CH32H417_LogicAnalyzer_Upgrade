/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * Firmware image parsing: Intel HEX (.hex) and raw binary (.bin)
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef FIRMWAREIMAGE_H
#define FIRMWAREIMAGE_H

#include <QByteArray>
#include <QString>
#include <QtGlobal>

/**
 * A parsed firmware image.
 */
struct FirmwareImage
{
    QByteArray data;            /* Contiguous binary data (gaps filled with 0xFF) */
    quint32 startAddress = 0;   /* Start address (programming base address) */
    quint32 endAddress = 0;     /* End address, inclusive */
    quint32 checksum = 0;       /* 32-bit additive checksum, shown in the UI */
    quint32 entryAddress = 0;   /* Entry point from the HEX file, may be 0 */
    bool fromHex = false;
};

/**
 * Load a firmware file (the .hex / .bin format is detected automatically).
 *
 * @param path           Firmware file path
 * @param binBaseAddress Programming base address used for .bin files
 * @param image          Output image
 * @param errorMessage   Failure description, only set when the call fails
 * @return true on success
 */
bool firmware_load(const QString &path, quint32 binBaseAddress,
                   FirmwareImage &image, QString &errorMessage);

/**
 * Format a file size for display, e.g. "120.5 KB".
 */
QString firmware_format_size(qint64 bytes);

#endif /* FIRMWAREIMAGE_H */
