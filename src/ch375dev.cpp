/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * CH375 设备访问层实现
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "ch375dev.h"
#include <QCoreApplication>

#include "ch375_wrapper.h"
#include <hidapi.h>

#include <cstring>

/* 应用层命令（与固件 ch32h417_logic.h 保持一致） */
#define CMD_GET_VERSION     0xAC    /* 读取版本 */
#define CMD_SET_IAP         0xAE    /* 切换到 IAP 下载模式 */
#define CMD_RETURN_PARA     0x10    /* 命令响应标志 */

/* 命令通道包长度 */
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
 * 从 CH375 返回的设备路径里解析 USB 序列号（小写）。
 * 设备路径形如：
 *   \\?\usb#vid_1a86&pid_5537#b5e339e33906e19c7f6416064c#{5e7f6bdf-...}
 * 第 2 个 '#' 与第 3 个 '#' 之间即实例序列号。
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

bool ch375dev_init(QString &errorMessage)
{
    if (ch375_init() != 0) {
        errorMessage = QCoreApplication::translate(
                           "Ch375Dev",
                           "无法加载 CH375DLL64.DLL / CH375DLL.DLL。\n"
                           "请确认已安装 CH375 驱动，且驱动 DLL 位于本程序目录或系统可搜索路径中。");
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

        if ((matchVid == 0 || vid == matchVid) && (matchPid == 0 || pid == matchPid)) {
            Ch375DeviceInfo info;
            info.index = static_cast<int>(i);
            info.vid = vid;
            info.pid = pid;

            /* 设备路径里带 USB 序列号，用于识别具体产品（b5 开头 = Logic Analyzer V2） */
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
 * 枚举处于 IAP 升级模式的 HID 设备。
 *
 * 设备进入 IAP 后会复位成 HID 设备（1A86:FE17），此时 CH375 通道上已经看不到它，
 * 只有 hidapi 能枚举到，因此单独列出来，保证设备列表里始终能看到设备。
 */
QList<Ch375DeviceInfo> ch375dev_enum_hid_devices(quint16 matchVid, quint16 matchPid)
{
    QList<Ch375DeviceInfo> list;

    if (!hid_ready())
        return list;

    hid_device_info *devs = ::hid_enumerate(matchVid, matchPid);
    for (hid_device_info *cur = devs; cur; cur = cur->next) {
        Ch375DeviceInfo info;
        info.index = -1;            /* HID 设备没有 CH375 索引 */
        info.isIap = true;
        info.vid = cur->vendor_id;
        info.pid = cur->product_id;

        if (cur->path)
            info.name = QString::fromLocal8Bit(cur->path);
        if (cur->serial_number) {
            info.serial = QString::fromWCharArray(cur->serial_number).toLower();
            /*
             * 部分固件把实例序列号放在 serial_number 里；也有固件给出的是
             * 形如 "b5e339e33906e19c7f6416064c" 的字符串，两种都能用于识别产品。
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
        errorMessage = QCoreApplication::translate("Ch375Dev", "设备索引无效");
        return false;
    }

    if (!ch375_is_loaded()) {
        if (!ch375dev_init(errorMessage))
            return false;
    }

    void *handle = ch375_open_device(static_cast<unsigned long>(index));
    if (handle == CH375_INVALID_HANDLE) {
        errorMessage = QCoreApplication::translate("Ch375Dev", "无法打开 CH375 设备 (索引 %1)").arg(index);
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
        errorMessage = QCoreApplication::translate("Ch375Dev", "读取固件版本失败（设备无响应）");
        return false;
    }

    ch375_close_device(static_cast<unsigned long>(index));

    if (resp[0] != (CMD_GET_VERSION | CMD_RETURN_PARA)) {
        errorMessage = QCoreApplication::translate("Ch375Dev", "版本响应异常：0x%1")
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
        errorMessage = QCoreApplication::translate("Ch375Dev", "设备索引无效");
        return false;
    }

    if (!ch375_is_loaded()) {
        if (!ch375dev_init(errorMessage))
            return false;
    }

    void *handle = ch375_open_device(static_cast<unsigned long>(index));
    if (handle == CH375_INVALID_HANDLE) {
        errorMessage = QCoreApplication::translate("Ch375Dev", "无法打开 CH375 设备 (索引 %1)").arg(index);
        return false;
    }

    unsigned char cmd[CMD_PACKET_LEN];
    std::memset(cmd, 0, sizeof(cmd));
    cmd[0] = CMD_SET_IAP;   /* 通知 APP 写入 IAP 标志并复位 */
    cmd[1] = 0;

    ch375_set_timeout_ex(static_cast<unsigned long>(index), 1000, 1000, 1000, 1000);

    unsigned long length = CMD_PACKET_LEN;
    const bool ok = ch375_write_endpoint(static_cast<unsigned long>(index),
                                         CH32H417_PIPE_CMD, cmd, &length) != 0;

    ch375_close_device(static_cast<unsigned long>(index));

    if (!ok) {
        errorMessage = QCoreApplication::translate("Ch375Dev", "发送进入 IAP 模式命令失败");
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

DeviceMode ch375dev_detect(quint16 appVid, quint16 appPid,
                           quint16 iapVid, quint16 iapPid,
                           int &appIndex,
                           QList<Ch375DeviceInfo> &deviceList,
                           QString &errorMessage)
{
    appIndex = -1;
    deviceList.clear();

    if (!ch375dev_init(errorMessage))
        return DeviceMode::NotFound;

    deviceList = ch375dev_enum_devices(appVid, appPid, errorMessage);

    /* IAP 模式的设备通过 HID 通道枚举，同样放进设备列表，方便用户确认设备在线 */
    deviceList += ch375dev_enum_hid_devices(iapVid, iapPid);

    if (!deviceList.isEmpty()) {
        /* 优先使用运行模式（CH375）的设备进行版本查询 / 切换 IAP */
        for (const Ch375DeviceInfo &info : deviceList) {
            if (!info.isIap) {
                appIndex = info.index;
                return DeviceMode::AppRunning;
            }
        }
        return DeviceMode::IapBootloader;
    }

    return DeviceMode::NotFound;
}
