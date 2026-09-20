/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * Firmware image parsing implementation
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "firmwareimage.h"

#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QByteArray>
#include <QCoreApplication>
#include <QStringList>

namespace {

/* One HEX data record */
struct HexChunk
{
    quint32 address;
    QByteArray bytes;
};

/* Maximum accepted image size, guards against a malformed HEX exhausting memory */
const qint64 MAX_IMAGE_SIZE = 4 * 1024 * 1024;

/* Translate helper: every message below is user visible */
QString trText(const char *text)
{
    return QCoreApplication::translate("FirmwareImage", text);
}

/* Convert one HEX text line into a byte sequence; false means malformed */
bool hex_line_to_bytes(const QString &line, QByteArray &bytes)
{
    const QString body = line.trimmed();

    if (body.length() < 11)          /* ':' plus at least 5 bytes = 11 characters */
        return false;
    if (!body.startsWith(':'))
        return false;
    if (body.length() % 2 == 0)      /* an even number of characters must follow ':' */
        return false;

    bytes.clear();
    bytes.reserve((body.length() - 1) / 2);

    bool ok = false;
    for (int i = 1; i < body.length(); i += 2) {
        const unsigned value = body.mid(i, 2).toUInt(&ok, 16);
        if (!ok)
            return false;
        bytes.append(static_cast<char>(value));
    }

    return true;
}

/* Parse Intel HEX text */
bool parse_hex(const QByteArray &raw, FirmwareImage &image, QString &errorMessage)
{
    QList<HexChunk> chunks;
    quint32 upperAddress = 0;      /* Extended linear address (type 04) */
    quint32 segmentAddress = 0;    /* Extended segment address (type 02) */
    quint32 minAddress = 0xFFFFFFFFu;
    quint32 maxAddress = 0;
    bool endRecordSeen = false;
    int lineNumber = 0;

    const QString text = QString::fromLatin1(raw);
    const QStringList lines = text.split('\n');

    for (const QString &rawLine : lines) {
        ++lineNumber;

        const QString line = rawLine.trimmed();
        if (line.isEmpty())
            continue;
        if (!line.startsWith(':')) {
            /* Non HEX content (blank lines, comments) around the records is tolerated */
            continue;
        }

        QByteArray record;
        if (!hex_line_to_bytes(line, record)) {
            errorMessage = trText("Invalid HEX file: cannot parse line %1").arg(lineNumber);
            return false;
        }

        if (record.size() < 5) {
            errorMessage = trText("Invalid HEX file: line %1 is too short").arg(lineNumber);
            return false;
        }

        /* Checksum: the sum of the whole record, including the checksum byte, is 0x00 */
        quint8 sum = 0;
        for (int i = 0; i < record.size(); ++i)
            sum = static_cast<quint8>(sum + static_cast<quint8>(record[i]));
        if (sum != 0) {
            errorMessage = trText("HEX checksum error on line %1 (0x%2)")
                               .arg(lineNumber)
                               .arg(static_cast<unsigned>(sum), 2, 16, QChar('0'));
            return false;
        }

        const int byteCount = static_cast<quint8>(record[0]);
        if (record.size() < byteCount + 5) {
            errorMessage = trText("Invalid HEX file: data length mismatch on line %1").arg(lineNumber);
            return false;
        }

        const quint32 offset = (static_cast<quint8>(record[1]) << 8) |
                               (static_cast<quint8>(record[2]));
        const int type = static_cast<quint8>(record[3]);
        const char *payload = record.constData() + 4;

        switch (type) {
        case 0x00: {   /* Data record */
            const quint32 address = upperAddress + segmentAddress + offset;
            HexChunk chunk;
            chunk.address = address;
            chunk.bytes = QByteArray(payload, byteCount);
            chunks.append(chunk);

            if (address < minAddress)
                minAddress = address;
            const quint32 last = address + static_cast<quint32>(byteCount) - 1;
            if (last > maxAddress)
                maxAddress = last;
            break;
        }
        case 0x01:     /* End of file */
            endRecordSeen = true;
            break;
        case 0x02:     /* Extended segment address */
            segmentAddress = ((static_cast<quint8>(record[4]) << 8) |
                              static_cast<quint8>(record[5])) << 4;
            break;
        case 0x03:     /* Start segment address (CS:IP) */
            image.entryAddress = (static_cast<quint8>(record[4]) << 8) |
                                 static_cast<quint8>(record[5]);
            break;
        case 0x04:     /* Extended linear address */
            upperAddress = (static_cast<quint8>(record[4]) << 24) |
                           (static_cast<quint8>(record[5]) << 16);
            break;
        case 0x05:     /* Start linear address (EIP) */
            image.entryAddress = (static_cast<quint8>(record[4]) << 24) |
                                 (static_cast<quint8>(record[5]) << 16) |
                                 (static_cast<quint8>(record[6]) << 8) |
                                 static_cast<quint8>(record[7]);
            break;
        default:       /* Unknown record type, ignored */
            break;
        }

        if (endRecordSeen)
            break;
    }

    if (chunks.isEmpty()) {
        errorMessage = trText("HEX file contains no valid data record");
        return false;
    }

    const qint64 size = static_cast<qint64>(maxAddress) -
                        static_cast<qint64>(minAddress) + 1;
    if (size <= 0 || size > MAX_IMAGE_SIZE) {
        errorMessage = trText("HEX address range out of bounds: 0x%1 - 0x%2")
                           .arg(minAddress, 8, 16, QChar('0'))
                           .arg(maxAddress, 8, 16, QChar('0'));
        return false;
    }

    /* Fill the gaps with 0xFF to build one contiguous image */
    QByteArray buffer(static_cast<int>(size), static_cast<char>(0xFF));
    for (const HexChunk &chunk : chunks) {
        const int offset = static_cast<int>(chunk.address - minAddress);
        for (int i = 0; i < chunk.bytes.size(); ++i)
            buffer[offset + i] = chunk.bytes[i];
    }

    image.data = buffer;
    image.startAddress = minAddress;
    image.endAddress = maxAddress;
    image.fromHex = true;
    return true;
}

/* 32-bit additive checksum */
quint32 sum_bytes(const QByteArray &data)
{
    quint32 sum = 0;
    for (int i = 0; i < data.size(); ++i)
        sum += static_cast<quint8>(data[i]);
    return sum;
}

} // namespace

bool firmware_load(const QString &path, quint32 binBaseAddress,
                   FirmwareImage &image, QString &errorMessage)
{
    errorMessage.clear();

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        errorMessage = trText("Cannot open firmware file: %1").arg(path);
        return false;
    }

    const QByteArray raw = file.readAll();
    file.close();

    if (raw.isEmpty()) {
        errorMessage = trText("Firmware file is empty");
        return false;
    }

    const QString lower = path.toLower();
    bool ok = false;

    if (lower.endsWith(".hex") || lower.endsWith(".ihex") || lower.endsWith(".h86")) {
        ok = parse_hex(raw, image, errorMessage);
        if (!ok)
            return false;
    } else {
        /* Sniffing: a leading ':' plus a second ':' on another line means HEX */
        const QString head = QString::fromLatin1(raw.left(200));
        if (head.startsWith(':') && head.indexOf(':') >= 0 &&
            head.contains('\n')) {
            ok = parse_hex(raw, image, errorMessage);
            if (!ok)
                return false;
        } else {
            image.data = raw;
            image.startAddress = binBaseAddress;
            image.endAddress = binBaseAddress +
                               static_cast<quint32>(qMax<qint64>(raw.size() - 1, 0));
            image.fromHex = false;
        }
    }

    image.checksum = sum_bytes(image.data);
    return true;
}

QString firmware_format_size(qint64 bytes)
{
    if (bytes < 1024)
        return trText("%1 B").arg(bytes);
    if (bytes < 1024 * 1024)
        return trText("%1 KB (%2 bytes)")
            .arg(static_cast<double>(bytes) / 1024.0, 0, 'f', 2)
            .arg(bytes);
    return trText("%1 MB (%2 bytes)")
        .arg(static_cast<double>(bytes) / (1024.0 * 1024.0), 0, 'f', 2)
        .arg(bytes);
}
