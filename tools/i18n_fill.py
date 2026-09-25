# -*- coding: utf-8 -*-
"""
Fill the Qt translation file with the Simplified Chinese translations.

English is the source language of every tr() string in the source code, so only
translations/app_zh_CN.ts needs a translation; switching the UI to English just
removes the installed translator (see LanguageManager).

Usage:
    python tools/i18n_fill.py <project directory>
"""
import sys
import os
import xml.etree.ElementTree as ET

# English source text -> Simplified Chinese translation
ZH = {
    # ---------------- Ch375Dev ----------------
    "Unable to load CH375DLL64.DLL / CH375DLL.DLL.\n"
    "Make sure the CH375 driver is installed and that the driver DLL is placed "
    "next to this program or in a directory on the system search path.":
        "无法加载 CH375DLL64.DLL / CH375DLL.DLL。\n"
        "请确认已安装 CH375 驱动，且驱动 DLL 位于本程序目录或系统可搜索路径中。",
    "Invalid device index": "设备索引无效",
    "Cannot open CH375 device (index %1)": "无法打开 CH375 设备（索引 %1）",
    "Failed to read firmware version (device did not respond)": "读取固件版本失败（设备无响应）",
    "Unexpected version response: 0x%1": "版本响应异常：0x%1",
    "Failed to send the enter-IAP-mode command": "发送进入 IAP 模式命令失败",
    "The device is in use by another program.\n"
    "Close the program that currently uses the board "
    "(for example the logic analyzer software) and refresh.":
        "设备正被其他程序占用。\n"
        "请关闭当前使用该设备的程序（例如逻辑分析仪上位机软件）后刷新重试。",

    # ---------------- LibusbDev ----------------
    "libusb is not available": "libusb 不可用",
    "Unable to initialise libusb (error %1)": "libusb 初始化失败（错误 %1）",
    "Failed to enumerate the USB devices (libusb error %1)": "枚举 USB 设备失败（libusb 错误 %1）",
    "Cannot open the USB device (libusb error %1). The board must be bound to a "
    "generic USB driver (WinUSB on Windows) and must not be in use by another "
    "program.":
        "无法打开 USB 设备（libusb 错误 %1）。设备需要绑定通用 USB 驱动"
        "（Windows 上为 WinUSB），且不能被其他程序占用。",
    "Cannot claim the USB interface (libusb error %1). Close other programs that "
    "use the device and try again.":
        "无法占用 USB 接口（libusb 错误 %1）。请关闭使用该设备的其他程序后重试。",
    "Failed to send command 0x%1 (libusb error %2)": "发送命令 0x%1 失败（libusb 错误 %2）",
    "The device did not answer command 0x%1 (libusb error %2)":
        "设备未应答命令 0x%1（libusb 错误 %2）",
    "The device is no longer present (bus %1, address %2)":
        "设备已不存在（总线 %1，地址 %2）",
    " (in use)": "（被占用）",

    # ---------------- ThemeManager / View menu ----------------
    "Follow System(&S)": "跟随系统(&S)",
    "Light(&L)": "浅色(&L)",
    "Dark(&D)": "深色(&D)",

    # ---------------- FirmwareImage ----------------
    "Invalid HEX file: cannot parse line %1": "HEX 格式错误：第 %1 行无法解析",
    "Invalid HEX file: line %1 is too short": "HEX 格式错误：第 %1 行长度不足",
    "HEX checksum error on line %1 (0x%2)": "HEX 校验和错误：第 %1 行 (0x%2)",
    "Invalid HEX file: data length mismatch on line %1": "HEX 格式错误：第 %1 行数据长度不符",
    "HEX file contains no valid data record": "HEX 文件中没有有效的数据记录",
    "HEX address range out of bounds: 0x%1 - 0x%2": "HEX 地址范围异常：0x%1 - 0x%2",
    "Cannot open firmware file: %1": "无法打开固件文件：%1",
    "Firmware file is empty": "固件文件为空",
    "%1 B": "%1 字节",
    "%1 KB (%2 bytes)": "%1 KB（%2 字节）",
    "%1 MB (%2 bytes)": "%1 MB（%2 字节）",

    # ---------------- IapWorker ----------------
    "Unknown error": "未知错误",
    "Failed to initialize hidapi": "hidapi 初始化失败",
    "Cancelled while waiting for the IAP device": "已取消：等待 IAP 设备",
    "Connected to IAP device (VID:0x%1 PID:0x%2)": "已连接 IAP 设备 (VID:0x%1 PID:0x%2)",
    "Waiting for the IAP device (VID:0x%1 PID:0x%2) ...": "等待 IAP 设备出现 (VID:0x%1 PID:0x%2) ...",
    "IAP device not found after waiting %1 seconds": "未找到 IAP 设备，已等待 %1 秒",
    "Write cancelled": "写入被取消",
    "HID write failed: %1": "HID 写入失败：%1",
    "HID write timed out (%1 ms)": "HID 写入超时（%1 ms）",
    "Read cancelled": "读取被取消",
    "HID read failed: %1": "HID 读取失败：%1",
    "Upgrade cancelled": "已取消升级",
    "Device is already in IAP mode, skipping the mode switch": "设备已处于 IAP 模式，跳过模式切换",
    "No usable CH375 device index, cannot send the switch command":
        "没有可用的 CH375 设备索引，无法发送切换命令",
    "Sending enter-IAP-mode command to device (CH375 index %1) ...":
        "向设备（CH375 索引 %1）发送进入 IAP 模式命令 ...",
    "Sending enter-IAP-mode command over libusb (bus %1, address %2) ...":
        "通过 libusb 发送进入 IAP 模式命令（总线 %1，地址 %2）...",
    "Failed to enter IAP mode: %1": "进入 IAP 模式失败：%1",
    "Command sent, waiting for the device to reset into a HID IAP device ...":
        "命令已发送，等待设备复位并切换为 HID IAP 设备 ...",
    "Erasing FLASH, start address 0x%1": "擦除 FLASH，起始地址 0x%1",
    "Erasing FLASH ...": "擦除 FLASH ...",
    "Failed to send the erase command": "发送擦除命令失败",
    "Erase response timed out": "擦除响应超时",
    "Erase failed, error code: %1": "擦除失败，错误码：%1",
    "Erase complete": "擦除完成",
    "Programming FLASH, %1 bytes in total": "编程 FLASH，共 %1 字节",
    "Programming FLASH ...": "编程 FLASH ...",
    "Failed to write data, offset %1": "写入数据失败，偏移 %1",
    "Programming response timed out, offset %1": "编程响应超时，偏移 %1",
    "Programming failed, error code %1, offset %2": "编程失败，错误码 %1，偏移 %2",
    "Programming FLASH ... %1%": "编程 FLASH ... %1%",
    "Programming complete": "编程完成",
    "Verifying FLASH ...": "校验 FLASH ...",
    "Failed to send the verify command, offset %1": "发送校验命令失败，偏移 %1",
    "Verify response timed out, offset %1": "校验响应超时，偏移 %1",
    "Verification failed, error code %1, address 0x%2": "校验失败，错误码 %1，地址 0x%2",
    "Verifying FLASH ... %1%": "校验 FLASH ... %1%",
    "Verification succeeded": "校验成功",
    "Sending the upgrade-finish command ...": "发送升级结束命令 ...",
    "Finishing upgrade ...": "结束升级 ...",
    "Failed to send the finish command": "发送结束命令失败",
    "Device confirmed the upgrade": "设备确认升级完成",
    "Device has reset (no response is normal)": "设备已复位（无应答属正常现象）",
    "Reading firmware file ...": "读取固件文件 ...",
    "Failed to load firmware: %1": "固件加载失败：%1",
    "Firmware loaded: %1": "已加载固件：%1",
    "  Format: %1, size: %2 bytes": "  格式：%1，大小：%2 字节",
    "Intel HEX": "Intel HEX",
    "BIN": "BIN",
    "  Address range: 0x%1 - 0x%2": "  地址范围：0x%1 - 0x%2",
    "  Checksum: 0x%1": "  校验和：0x%1",
    "Firmware data is empty": "固件数据为空",
    "Starting upgrade ...": "开始升级 ...",
    "========== Firmware upgrade started %1 ==========": "========== 开始固件升级 %1 ==========",
    "Failed to load the firmware file": "固件文件加载失败",
    "Entering IAP mode ...": "进入 IAP 模式 ...",
    "Unable to enter IAP mode": "无法进入 IAP 模式",
    "Looking for the IAP device ...": "查找 IAP 设备 ...",
    "No device in IAP mode found": "未找到 IAP 模式的设备",
    "Connected to the IAP device": "已连接 IAP 设备",
    "Failed to erase FLASH": "擦除 FLASH 失败",
    "Failed to program FLASH": "编程 FLASH 失败",
    "Failed to verify FLASH": "校验 FLASH 失败",
    "Failed to finish the upgrade": "结束升级失败",
    "Upgrade complete": "升级完成",
    "========== Firmware upgrade succeeded ==========": "========== 固件升级成功 ==========",
    "Firmware upgrade succeeded, the device will restart": "固件升级成功，设备将重新启动",

    # ---------------- LanguageManager ----------------
    "Follow System(&A)": "跟随系统(&A)",
    "English(&E)": "English(&E)",
    "Simplified Chinese(&C)": "简体中文(&C)",
    "Simplified Chinese": "简体中文",
    "English": "English",

    # ---------------- MainWindow ----------------
    "CH32H417 Logic Analyzer Firmware Upgrade Tool": "CH32H417 逻辑分析仪固件升级工具",
    "Device": "设备",
    "Firmware File": "固件文件",
    "IAP Settings": "IAP 参数",
    "Device List:": "设备列表：",
    "Device Status:": "设备状态：",
    "Firmware Version:": "固件版本：",
    "File Path:": "文件路径：",
    "Firmware Info:": "固件信息：",
    "BIN Base Address: 0x": "BIN 基地址：0x",
    "VID: 0x": "VID：0x",
    "PID: 0x": "PID：0x",
    "Defaults: VID=0x1A86 PID=0xFE17": "默认值 VID=0x1A86 PID=0xFE17",
    "Refresh(&R)": "刷新(&R)",
    "Browse(&B)...": "浏览(&B)...",
    "Programming start address for .bin files (hexadecimal, e.g. 08006000)":
        ".bin 文件的烧录起始地址（十六进制，例如 08006000）",
    "Hexadecimal, e.g. 08006000": "十六进制，例如 08006000",
    "Select or drop a .hex / .bin firmware file": "选择或直接拖入 .hex / .bin 固件文件",
    "Upgrade Log": "升级日志",
    "Start Upgrade(&S)": "开始升级(&S)",
    "Exit(&X)": "退出(&X)",
    "File(&F)": "文件(&F)",
    "Open Firmware(&O)...": "打开固件(&O)...",
    "Tools(&T)": "工具(&T)",
    "Refresh Devices(&R)": "刷新设备(&R)",
    "Clear Log(&L)": "清空日志(&L)",
    "View(&V)": "视图(&V)",
    "Language(&L)": "语言(&L)",
    "Help(&H)": "帮助(&H)",
    "About(&A)": "关于(&A)",
    "(No device found)": "(未发现设备)",
    "No device found": "未发现设备",
    "IAP Mode": "IAP 模式",
    "Run Mode": "运行模式",
    "<font color='%1'>Connected (application mode, CH375 channel)</font>":
        "<font color='%1'>已连接（运行模式，CH375 通道）</font>",
    "<font color='%1'>Connected (application mode, %2 channel)</font>":
        "<font color='%1'>已连接（运行模式，%2 通道）</font>",
    "Software version: v%1  Hardware version: v%2": "软件版本：v%1　硬件版本：v%2",
    "Read failed": "读取失败",
    "<font color='%1'>Connected (IAP upgrade mode)</font>":
        "<font color='%1'>已连接（IAP 升级模式）</font>",
    "<font color='%1'>Connected (IAP upgrade mode, HID channel)</font>":
        "<font color='%1'>已连接（IAP 升级模式，HID 通道）</font>",
    "-": "-",
    "<font color='%1'>No device found</font>": "<font color='%1'>未发现设备</font>",
    "<font color='%1'>Device in use by another program</font>":
        "<font color='%1'>设备正被其他程序占用</font>",
    "Select Firmware File": "选择固件文件",
    "Firmware Files (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binary Files (*.bin);;All Files (*.*)":
        "固件文件 (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;二进制文件 (*.bin);;所有文件 (*.*)",
    "<font color='%1'>No valid firmware file selected</font>":
        "<font color='%1'>尚未选择有效的固件文件</font>",
    "<font color='%1'>%2</font>": "<font color='%1'>%2</font>",
    "%1  Size: %2  Address: 0x%3 - 0x%4  Checksum: 0x%5":
        "%1　大小：%2　地址：0x%3 - 0x%4　校验和：0x%5",
    "Hint": "提示",
    "Please select a valid firmware file first.": "请先选择一个有效的固件文件。",
    "No Device Found": "未发现设备",
    "No CH32H417 device was detected.\n\n"
    "If the device is already in IAP mode (for example powered up with the button "
    "held down), you can continue;\notherwise please connect the device first.\n\nContinue?":
        "当前没有检测到 CH32H417 设备。\n\n"
        "如果设备已经处于 IAP 模式（例如按住按键上电），可以继续升级；\n"
        "否则请先连接设备。\n\n是否继续？",
    "Firmware Error": "固件错误",
    "Preparing ...": "准备中 ...",
    "Target device: %1": "目标设备：%1",
    "Target device: CH375 #%1": "目标设备：CH375 #%1",
    "Target device: libusb (bus %1, address %2)": "目标设备：libusb（总线 %1，地址 %2）",
    "Target device: IAP HID (VID:0x%1 PID:0x%2)": "目标设备：IAP HID (VID:0x%1 PID:0x%2)",
    "Upgrade Complete": "升级完成",
    "Complete": "完成",
    "Firmware upgrade succeeded!\nThe device will restart and run the new firmware.":
        "固件升级成功！\n设备将重启并运行新固件。",
    "Upgrade Failed": "升级失败",
    "Failed": "失败",
    "Please power-cycle the device (disconnect and reconnect the USB cable or the "
    "power supply) and run the upgrade again.":
        "请给设备重新上电（拔插 USB 线或断开再接通电源），然后重新执行升级。",
    "Ready": "就绪",
    "About": "关于",
    "<h3>CH32H417 Logic Analyzer<br>Firmware Upgrade Tool</h3>"
    "<p>Version: %1</p>"
    "<p><b>WeAct Studio</b><br>"
    "Copyright (C) 2026 WeAct Studio. All rights reserved.</p>"
    "<p>This program is free software: you can redistribute it and/or modify it "
    "under the terms of the GNU General Public License as published by the Free "
    "Software Foundation, either version 3 of the License, or (at your option) "
    "any later version. It is distributed in the hope that it will be useful, but "
    "WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY "
    "or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for "
    "more details.</p>"
    "<p>License: GPL-3.0-or-later<br>"
    "<a href='https://www.gnu.org/licenses/gpl-3.0.html'>"
    "https://www.gnu.org/licenses/gpl-3.0.html</a></p>"
    "<p>Built with Qt %2, statically compiled with MSYS2 (MINGW64).</p>"
    "<p>Upgrade sequence: the enter-IAP command is sent over the CH375 "
    "channel, the device resets into a HID IAP device, then erase / "
    "program / verify / finish.</p>"
    "<p>The CH375 driver must be installed.</p>":
        "<h3>CH32H417 逻辑分析仪<br>固件升级工具</h3>"
        "<p>版本：%1</p>"
        "<p><b>WeAct Studio</b><br>"
        "Copyright (C) 2026 WeAct Studio 保留所有权利。</p>"
        "<p>本程序为自由软件：您可以依据自由软件基金会发布的 GNU 通用公共许可证"
        "第 3 版或（按您选择的）任何更新版本的条款重新发布和/或修改本程序。"
        "发布本程序是希望它能有所用处，但不提供任何担保，甚至不隐含"
        "适销性或特定用途适用性的担保。详见 GNU 通用公共许可证。</p>"
        "<p>许可协议：GPL-3.0-or-later<br>"
        "<a href='https://www.gnu.org/licenses/gpl-3.0.html'>"
        "https://www.gnu.org/licenses/gpl-3.0.html</a></p>"
        "<p>基于 Qt %2 开发，使用 MSYS2 (MINGW64) 静态编译。</p>"
        "<p>升级流程：CH375 通道发送进入 IAP 命令 → 设备复位为 HID IAP 设备 → "
        "擦除 / 编程 / 校验 / 结束。</p>"
        "<p>需要安装 CH375 驱动。</p>",
    "Upgrade in Progress": "正在升级",
    "An upgrade is running; exiting now may corrupt the device firmware.\n"
    "Are you sure you want to exit?":
        "升级正在进行中，现在退出可能导致设备固件损坏。\n确定要退出吗？",
}


def fill(path, translator):
    """Fill every <translation> of the given .ts file using translator()."""
    tree = ET.parse(path)
    root = tree.getroot()
    missing = []

    for ctx in root:
        if ctx.tag != 'context':
            continue
        for msg in ctx.findall('message'):
            src = msg.find('source')
            if src is None:
                continue
            source = src.text or ''
            tr = msg.find('translation')
            if tr is None:
                tr = ET.SubElement(msg, 'translation')

            text = translator(source)
            if text is None:
                missing.append((ctx.find('name').text, source))
                text = ''
                tr.set('type', 'unfinished')
            else:
                tr.attrib.pop('type', None)

            tr.text = text

    with open(path, 'wb') as f:
        f.write(b'<?xml version="1.0" encoding="utf-8"?>\n<!DOCTYPE TS>\n')
        tree.write(f, encoding='utf-8', xml_declaration=False)

    return missing


def main():
    root_dir = sys.argv[1] if len(sys.argv) > 1 else '.'
    base = os.path.join(root_dir, 'translations')

    missing = fill(os.path.join(base, 'app_zh_CN.ts'), lambda s: ZH.get(s))

    print('zh_CN: filled, missing %d' % len(missing))
    for ctx, src in missing:
        print('  [MISSING][%s] %s' % (ctx, src.replace('\n', '\\n')))


if __name__ == '__main__':
    main()
