/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * 固件镜像解析实现
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

/* 单条 HEX 数据记录 */
struct HexChunk
{
    quint32 address;
    QByteArray bytes;
};

/* 单文件允许的最大镜像体积，防止异常 HEX 撑爆内存 */
const qint64 MAX_IMAGE_SIZE = 4 * 1024 * 1024;

/* 将一行 HEX 文本转成字节序列；返回 false 表示格式非法 */
bool hex_line_to_bytes(const QString &line, QByteArray &bytes)
{
    const QString body = line.trimmed();

    if (body.length() < 11)          /* ':' + 至少 5 字节 = 11 字符 */
        return false;
    if (!body.startsWith(':'))
        return false;
    if (body.length() % 2 == 0)      /* ':' 之后必须是偶数个字符 */
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

/* 解析 Intel HEX 文本 */
bool parse_hex(const QByteArray &raw, FirmwareImage &image, QString &errorMessage)
{
    QList<HexChunk> chunks;
    quint32 upperAddress = 0;      /* 扩展线性地址 (类型 04) */
    quint32 segmentAddress = 0;    /* 扩展段地址   (类型 02) */
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
            /* 允许文件首尾存在非 HEX 内容（例如空行、注释） */
            continue;
        }

        QByteArray record;
        if (!hex_line_to_bytes(line, record)) {
            errorMessage = QString("HEX 格式错误：第 %1 行无法解析").arg(lineNumber);
            return false;
        }

        if (record.size() < 5) {
            errorMessage = QString("HEX 格式错误：第 %1 行长度不足").arg(lineNumber);
            return false;
        }

        /* 校验和：整行（含校验字节）累加应为 0x00 */
        quint8 sum = 0;
        for (int i = 0; i < record.size(); ++i)
            sum = static_cast<quint8>(sum + static_cast<quint8>(record[i]));
        if (sum != 0) {
            errorMessage = QCoreApplication::translate("FirmwareImage", "HEX 校验和错误：第 %1 行 (0x%2)")
                               .arg(lineNumber)
                               .arg(static_cast<unsigned>(sum), 2, 16, QChar('0'));
            return false;
        }

        const int byteCount = static_cast<quint8>(record[0]);
        if (record.size() < byteCount + 5) {
            errorMessage = QString("HEX 格式错误：第 %1 行数据长度不符").arg(lineNumber);
            return false;
        }

        const quint32 offset = (static_cast<quint8>(record[1]) << 8) |
                               (static_cast<quint8>(record[2]));
        const int type = static_cast<quint8>(record[3]);
        const char *payload = record.constData() + 4;

        switch (type) {
        case 0x00: {   /* 数据记录 */
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
        case 0x01:     /* 文件结束 */
            endRecordSeen = true;
            break;
        case 0x02:     /* 扩展段地址 */
            segmentAddress = ((static_cast<quint8>(record[4]) << 8) |
                              static_cast<quint8>(record[5])) << 4;
            break;
        case 0x03:     /* 起始段地址 (CS:IP) */
            image.entryAddress = (static_cast<quint8>(record[4]) << 8) |
                                 static_cast<quint8>(record[5]);
            break;
        case 0x04:     /* 扩展线性地址 */
            upperAddress = (static_cast<quint8>(record[4]) << 24) |
                           (static_cast<quint8>(record[5]) << 16);
            break;
        case 0x05:     /* 起始线性地址 (EIP) */
            image.entryAddress = (static_cast<quint8>(record[4]) << 24) |
                                 (static_cast<quint8>(record[5]) << 16) |
                                 (static_cast<quint8>(record[6]) << 8) |
                                 static_cast<quint8>(record[7]);
            break;
        default:       /* 未知类型，忽略 */
            break;
        }

        if (endRecordSeen)
            break;
    }

    if (chunks.isEmpty()) {
        errorMessage = "HEX 文件中没有有效的数据记录";
        return false;
    }

    const qint64 size = static_cast<qint64>(maxAddress) -
                        static_cast<qint64>(minAddress) + 1;
    if (size <= 0 || size > MAX_IMAGE_SIZE) {
        errorMessage = QCoreApplication::translate("FirmwareImage", "HEX 地址范围异常：0x%1 - 0x%2")
                           .arg(minAddress, 8, 16, QChar('0'))
                           .arg(maxAddress, 8, 16, QChar('0'));
        return false;
    }

    /* 空洞填充 0xFF，生成连续镜像 */
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

/* 计算 32 位累加和 */
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
        errorMessage = QString("无法打开固件文件：%1").arg(path);
        return false;
    }

    const QByteArray raw = file.readAll();
    file.close();

    if (raw.isEmpty()) {
        errorMessage = "固件文件为空";
        return false;
    }

    const QString lower = path.toLower();
    bool ok = false;

    if (lower.endsWith(".hex") || lower.endsWith(".ihex") || lower.endsWith(".h86")) {
        ok = parse_hex(raw, image, errorMessage);
        if (!ok)
            return false;
    } else {
        /* 嗅探：以 ':' 开头且第二行也以 ':' 开头则按 HEX 处理 */
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
        return QString("%1 B").arg(bytes);
    if (bytes < 1024 * 1024)
        return QCoreApplication::translate("FirmwareImage", "%1 KB (%2 bytes)")
            .arg(static_cast<double>(bytes) / 1024.0, 0, 'f', 2)
            .arg(bytes);
    return QCoreApplication::translate("FirmwareImage", "%1 MB (%2 bytes)")
        .arg(static_cast<double>(bytes) / (1024.0 * 1024.0), 0, 'f', 2)
        .arg(bytes);
}
