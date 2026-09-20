/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * 固件镜像解析：支持 Intel HEX (.hex) 与原始二进制 (.bin)
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
 * 解析后的固件镜像
 */
struct FirmwareImage
{
    QByteArray data;            /* 连续二进制数据（空洞填 0xFF） */
    quint32 startAddress = 0;   /* 起始地址（烧录基地址） */
    quint32 endAddress = 0;     /* 结束地址（含） */
    quint32 checksum = 0;       /* 32 位累加和，用于界面展示 */
    quint32 entryAddress = 0;   /* HEX 中的入口地址记录，可能为 0 */
    bool fromHex = false;
};

/**
 * 加载固件文件（自动识别 .hex / .bin）
 *
 * @param path           固件文件路径
 * @param binBaseAddress .bin 文件使用的烧录基地址
 * @param image          输出镜像
 * @param errorMessage   失败时的错误描述
 * @return 成功返回 true
 */
bool firmware_load(const QString &path, quint32 binBaseAddress,
                   FirmwareImage &image, QString &errorMessage);

/**
 * 人性化显示文件大小，如 "120.5 KB"
 */
QString firmware_format_size(qint64 bytes);

#endif /* FIRMWAREIMAGE_H */
