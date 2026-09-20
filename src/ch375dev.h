/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * CH375 设备访问层：设备枚举 / 版本查询 / 进入 IAP 模式
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef CH375DEV_H
#define CH375DEV_H

#include <QList>
#include <QString>
#include <QtGlobal>

/* CH32H417 运行模式下的 USB ID（CH375 通道） */
#define CH32H417_APP_VID    0x1A86
#define CH32H417_APP_PID    0x5537

/* CH32H417 IAP (BootLoader) 模式下的 USB ID（HID 通道） */
#define CH32H417_IAP_VID    0x1A86
#define CH32H417_IAP_PID    0xFE17

/* 命令通道管道号 */
#define CH32H417_PIPE_CMD   1

/*
 * USB 序列号前缀 -> 产品名
 * 与 libsigrok 的 wch-ch32h417 驱动保持一致：
 *   序列号以 b5 开头 -> WeAct Studio Logic Analyzer V2
 *   序列号以 01 开头 -> CH32H417 Logic Analyzer
 */
#define CH32H417_SN_PREFIX_V2   "b5"
#define CH32H417_SN_PREFIX_V1   "01"

/**
 * 一个 CH375 通道上的设备
 */
struct Ch375DeviceInfo
{
    int index = -1;         /* CH375 设备索引 0..15；HID(IAP) 设备为 -1 */
    quint16 vid = 0;
    quint16 pid = 0;
    QString name;           /* 驱动返回的设备路径/名称，可能为空 */
    QString serial;         /* USB 序列号（小写），从设备路径解析，可能为空 */
    bool isIap = false;     /* true = IAP 升级模式（HID 通道），false = 运行模式（CH375 通道） */

    QString idString() const
    {
        return QString("VID:%1 PID:%2")
            .arg(vid, 4, 16, QChar('0'))
            .arg(pid, 4, 16, QChar('0'));
    }

    /** 按序列号前缀识别产品名；无法识别时回退到 CH32H417 */
    QString modelName() const
    {
        if (serial.startsWith(QLatin1String(CH32H417_SN_PREFIX_V2)))
            return QStringLiteral("WeAct Studio Logic Analyzer V2");
        if (serial.startsWith(QLatin1String(CH32H417_SN_PREFIX_V1)))
            return QStringLiteral("CH32H417 Logic Analyzer");
        return QStringLiteral("CH32H417");
    }

    /** 设备列表里的完整描述（下拉框显示不下时放进 tooltip） */
    QString description() const
    {
        /* 运行模式显示 CH375 索引；IAP 模式没有 CH375 索引，改用通道标记 */
        const QString tag = isIap ? QStringLiteral("IAP")
                                  : QStringLiteral("#%1").arg(index);
        QString text = QString("%1  %2  %3").arg(tag).arg(idString()).arg(modelName());
        if (!serial.isEmpty())
            text += QStringLiteral("  SN:%1").arg(serial);
        return text;
    }
};

/**
 * 设备当前所处模式
 */
enum class DeviceMode
{
    NotFound,       /* 未发现设备 */
    AppRunning,     /* 运行 APP（CH375 通道可见） */
    IapBootloader   /* 已处于 IAP/HID 模式 */
};

/**
 * 加载 CH375DLL。失败时 errorMessage 给出说明。
 */
bool ch375dev_init(QString &errorMessage);

/**
 * 枚举 CH375 上的设备
 * @param matchVid 过滤的 VID，0 表示不过滤
 * @param matchPid 过滤的 PID，0 表示不过滤
 */
QList<Ch375DeviceInfo> ch375dev_enum_devices(quint16 matchVid, quint16 matchPid,
                                             QString &errorMessage);

/**
 * 枚举处于 IAP 升级模式的 HID 设备
 * @param matchVid 过滤的 VID，0 表示不过滤
 * @param matchPid 过滤的 PID，0 表示不过滤
 */
QList<Ch375DeviceInfo> ch375dev_enum_hid_devices(quint16 matchVid, quint16 matchPid);

/**
 * 读取固件版本（CMD_GET_VERSION）
 * @param swVer 软件版本
 * @param hwVer 硬件版本
 */
bool ch375dev_get_version(int index, quint8 &swVer, quint8 &hwVer,
                          QString &errorMessage);

/**
 * 发送进入 IAP 模式命令（CMD_SET_IAP = 0xAE）
 * 成功发送后设备会复位并切换为 HID IAP 设备
 */
bool ch375dev_enter_iap(int index, QString &errorMessage);

/**
 * 判断指定的 HID 设备是否在线
 */
bool ch375dev_hid_present(quint16 vid, quint16 pid);

/**
 * 综合判断设备当前模式
 * @param appIndex   输出：APP 模式下的 CH375 设备索引，未找到为 -1
 * @param deviceList 输出：枚举到的 CH32H417 设备
 */
DeviceMode ch375dev_detect(quint16 appVid, quint16 appPid,
                           quint16 iapVid, quint16 iapPid,
                           int &appIndex,
                           QList<Ch375DeviceInfo> &deviceList,
                           QString &errorMessage);

#endif /* CH375DEV_H */
