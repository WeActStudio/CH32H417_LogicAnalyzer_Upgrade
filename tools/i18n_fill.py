# -*- coding: utf-8 -*-
"""
Fill the Qt translation files with the Simplified Chinese, Russian, German and
Spanish translations.

English is the source language of every tr() string in the source code, so only
translations/app_<lang>.ts needs a translation; switching the UI to English just
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

    # ---------------- SerialDev ----------------
    "Serial port enumeration is only supported on Windows": "仅支持在 Windows 上枚举串口",
    "Cannot enumerate the COM ports (error %1)": "无法枚举 COM 口（错误 %1）",
    "Serial port access is only supported on Windows": "仅支持在 Windows 上访问串口",
    "%1 is open in another program.\n"
    "Close the program (for example a serial terminal) and retry.":
        "%1 已被其他程序打开。\n"
        "请关闭该程序（例如串口终端）后重试。",
    "Cannot open %1 (error %2)": "无法打开 %1（错误 %2）",
    "Cannot query the settings of %1 (error %2)": "无法查询 %1 的设置（错误 %2）",
    "Cannot set the IAP baud rate on %1 (error %2)": "无法在 %1 上设置 IAP 波特率（错误 %2）",
    "The firmware version cannot be read on the USB-UART (serial) channel":
        "无法通过 USB 转串口（serial）通道读取固件版本",

    # ---------------- IapCtl ----------------
    "No IAP device found (VID:0x%1 PID:0x%2).\n"
    "These commands only work while the board sits in the bootloader.":
        "未找到 IAP 设备 (VID:0x%1 PID:0x%2)。\n"
        "这些命令只能在设备处于引导程序（IAP）时使用。",
    "Unexpected answer from the bootloader: 0x%1": "引导程序应答异常：0x%1",
    "The bootloader did not answer (timeout)": "引导程序无应答（超时）",
    "Failed to send command 0x%1 to the bootloader": "向引导程序发送命令 0x%1 失败",
    "The bootloader refused the request (error code %1)":
        "引导程序拒绝了该请求（错误码 %1）",
    "Slot number out of range (0..%1)": "槽位编号超出范围（0..%1）",

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
    "Opening %1 at the IAP baud rate %2 ...": "正在以 IAP 波特率 %2 打开 %1 ...",
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
    "Russian(&R)": "俄语(&R)",
    "German(&G)": "德语(&G)",
    "Spanish(&S)": "西班牙语(&S)",
    "Simplified Chinese": "简体中文",
    "English": "English",
    "Russian": "俄语",
    "German": "德语",
    "Spanish": "西班牙语",

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
    "Slot %1: 0x%2": "槽 %1：0x%2",
    "Reboot into Active Slot(&B)": "重启到当前槽(&B)",
    "Switch APP Slot(&S)": "切换 APP 槽(&S)",
    "Rebooting the device into its active slot ...": "正在把设备重启到当前槽 ...",
    "Reboot failed: %1": "重启失败：%1",
    "Reboot request accepted, the device restarts ...":
        "重启请求已接受，设备即将重启 ...",
    "Switching to APP slot %1 (0x%2) ...": "正在切换到 APP 槽 %1（0x%2）...",
    "Slot switch failed: %1": "切换槽位失败：%1",
    "Slot %1 is now active, the device reboots into it ...":
        "槽 %1 现已生效，设备将重启进入该槽 ...",
    "Not available while an upgrade is running": "升级进行中不可用",
    "Needs a board that sits in the IAP bootloader": "需要设备处于 IAP 引导程序模式",
    "Not Available": "不可用",
    "Wait for the running upgrade to finish.": "请等待当前升级完成。",
    "This command needs a board that sits in the IAP bootloader, "
    "the current device is in application mode.":
        "该命令需要设备处于 IAP 引导程序模式，当前设备处于运行模式。",
    "No CH32H417 device in IAP mode found.\n"
    "These commands need a board that sits in the bootloader "
    "(power-cycle it with the button held).":
        "未找到处于 IAP 模式的 CH32H417 设备。\n"
        "这些命令需要设备处于引导程序中（按住按键重新上电）。",
    "Reboot into &IAP": "重启到 IAP(&I)",
    "Reboot into:": "重启到：",
    "Slot %1": "槽 %1",
    "Make slot %1 (0x%2) the active one and boot it":
        "把槽 %1（0x%2）设为当前槽并启动",
    "Leave &IAP": "退出 IAP(&I)",
    "Reboot the board and run the active APP slot again":
        "重启设备并再次运行当前 APP 槽",
    "Reboot the board into its bootloader (IAP mode)":
        "将设备重启进入引导程序（IAP 模式）",
    "Rebooting the device out of IAP mode ...": "正在把设备退出 IAP 模式 ...",
    "Leaving IAP failed: %1": "退出 IAP 失败：%1",
    "Device is now in IAP mode": "设备已处于 IAP 模式",
    "Device is in IAP Mode": "设备处于 IAP 模式",
    "The device rebooted into IAP mode": "设备已重启进入 IAP 模式",
    "Programming start address for .bin files (hexadecimal, e.g. 08006000). "
    "On the WeAct Studio Logic Analyzer V2 pick one of the three APP slots: "
    "slot 0 = logic analyzer, slot 1 = USB to UART, slot 2 = example.":
        ".bin 文件的烧录起始地址（十六进制，如 08006000）。\n"
        "WeAct Studio Logic Analyzer V2 请选择三个 APP 槽之一："
        "槽 0 = 逻辑分析仪，槽 1 = USB 转串口，槽 2 = 示例。",
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
    "Target device: serial (COM port %1)": "目标设备：串口（COM 口 %1）",
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
    "<p>Upgrade sequence: the enter-IAP command goes out over whichever "
    "USB channel the board is on - CH375, libusb / WinUSB, or the COM "
    "port of the USB-to-UART firmware. The board then resets into a HID "
    "IAP device, followed by erase / program / verify / finish.</p>"
    "<p>A board that already sits in IAP mode can also be rebooted into "
    "its active slot, or switched to another APP slot, without "
    "downloading anything.</p>"
    "<p>Windows needs one driver for the board: the WCH CH375 driver, or "
    "WinUSB when the board is bound to libusb.</p>":
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
        "<p>升级流程：进入 IAP 命令通过板子所在的 USB 通道发出 —— CH375、"
        "libusb / WinUSB，或 USB 转串口固件的 COM 口 —— 随后设备复位为 HID "
        "IAP 设备，再执行擦除 / 编程 / 校验 / 结束。</p>"
        "<p>已经处于 IAP 模式的板子还可以直接重启回当前槽，或切换到其它 APP "
        "槽，无需下载固件。</p>"
        "<p>Windows 需要为板子安装其中一种驱动：WCH CH375 驱动；"
        "若板子绑定到 libusb，则安装 WinUSB。</p>",
    "Upgrade in Progress": "正在升级",
    "An upgrade is running; exiting now may corrupt the device firmware.\n"
    "Are you sure you want to exit?":
        "升级正在进行中，现在退出可能导致设备固件损坏。\n确定要退出吗？",
}


# English source text -> Russian translation
RU = {
    # ---------------- Ch375Dev ----------------
    "Unable to load CH375DLL64.DLL / CH375DLL.DLL.\n"
    "Make sure the CH375 driver is installed and that the driver DLL is placed "
    "next to this program or in a directory on the system search path.":
        "Не удалось загрузить CH375DLL64.DLL / CH375DLL.DLL.\n"
        "Убедитесь, что драйвер CH375 установлен, а DLL драйвера находится рядом "
        "с программой или в каталоге системного пути поиска.",
    "Invalid device index": "Недопустимый индекс устройства",
    "Cannot open CH375 device (index %1)": "Не удалось открыть устройство CH375 (индекс %1)",
    "Failed to read firmware version (device did not respond)":
        "Не удалось прочитать версию прошивки (устройство не отвечает)",
    "Unexpected version response: 0x%1": "Неожиданный ответ о версии: 0x%1",
    "Failed to send the enter-IAP-mode command":
        "Не удалось отправить команду перехода в режим IAP",
    "The device is in use by another program.\n"
    "Close the program that currently uses the board "
    "(for example the logic analyzer software) and refresh.":
        "Устройство занято другой программой.\n"
        "Закройте программу, использующую плату (например, программу логического "
        "анализатора), и обновите список.",

    # ---------------- LibusbDev ----------------
    "libusb is not available": "libusb недоступен",
    "Unable to initialise libusb (error %1)": "Не удалось инициализировать libusb (ошибка %1)",
    "Failed to enumerate the USB devices (libusb error %1)":
        "Не удалось перечислить USB-устройства (ошибка libusb %1)",
    "Cannot open the USB device (libusb error %1). The board must be bound to a "
    "generic USB driver (WinUSB on Windows) and must not be in use by another "
    "program.":
        "Не удалось открыть USB-устройство (ошибка libusb %1). Плата должна быть "
        "привязана к универсальному USB-драйверу (WinUSB в Windows) и не должна "
        "использоваться другой программой.",
    "Cannot claim the USB interface (libusb error %1). Close other programs that "
    "use the device and try again.":
        "Не удалось занять USB-интерфейс (ошибка libusb %1). Закройте другие "
        "программы, использующие устройство, и повторите попытку.",
    "Failed to send command 0x%1 (libusb error %2)":
        "Не удалось отправить команду 0x%1 (ошибка libusb %2)",
    "The device did not answer command 0x%1 (libusb error %2)":
        "Устройство не ответило на команду 0x%1 (ошибка libusb %2)",
    "The device is no longer present (bus %1, address %2)":
        "Устройство больше не найдено (шина %1, адрес %2)",
    " (in use)": " (занято)",

    # ---------------- SerialDev ----------------
    "Serial port enumeration is only supported on Windows":
        "Перечисление последовательных портов поддерживается только в Windows",
    "Cannot enumerate the COM ports (error %1)": "Не удалось перечислить COM-порты (ошибка %1)",
    "Serial port access is only supported on Windows":
        "Доступ к последовательному порту поддерживается только в Windows",
    "%1 is open in another program.\n"
    "Close the program (for example a serial terminal) and retry.":
        "%1 открыт в другой программе.\n"
        "Закройте эту программу (например, терминал) и повторите попытку.",
    "Cannot open %1 (error %2)": "Не удалось открыть %1 (ошибка %2)",
    "Cannot query the settings of %1 (error %2)":
        "Не удалось получить настройки %1 (ошибка %2)",
    "Cannot set the IAP baud rate on %1 (error %2)":
        "Не удалось задать скорость IAP на %1 (ошибка %2)",
    "The firmware version cannot be read on the USB-UART (serial) channel":
        "Версию прошивки нельзя прочитать через канал USB-UART (последовательный)",

    # ---------------- IapCtl ----------------
    "No IAP device found (VID:0x%1 PID:0x%2).\n"
    "These commands only work while the board sits in the bootloader.":
        "Устройство IAP не найдено (VID:0x%1 PID:0x%2).\n"
        "Эти команды работают только когда плата находится в загрузчике.",
    "Unexpected answer from the bootloader: 0x%1": "Неожиданный ответ загрузчика: 0x%1",
    "The bootloader did not answer (timeout)": "Загрузчик не ответил (тайм-аут)",
    "Failed to send command 0x%1 to the bootloader":
        "Не удалось отправить команду 0x%1 загрузчику",
    "The bootloader refused the request (error code %1)":
        "Загрузчик отклонил запрос (код ошибки %1)",
    "Slot number out of range (0..%1)": "Номер слота вне диапазона (0..%1)",

    # ---------------- ThemeManager / View menu ----------------
    "Follow System(&S)": "Как в системе(&S)",
    "Light(&L)": "Светлая(&L)",
    "Dark(&D)": "Тёмная(&D)",

    # ---------------- FirmwareImage ----------------
    "Invalid HEX file: cannot parse line %1": "Некорректный HEX-файл: не удалось разобрать строку %1",
    "Invalid HEX file: line %1 is too short": "Некорректный HEX-файл: строка %1 слишком коротка",
    "HEX checksum error on line %1 (0x%2)": "Ошибка контрольной суммы HEX в строке %1 (0x%2)",
    "Invalid HEX file: data length mismatch on line %1":
        "Некорректный HEX-файл: несоответствие длины данных в строке %1",
    "HEX file contains no valid data record": "HEX-файл не содержит ни одной записи данных",
    "HEX address range out of bounds: 0x%1 - 0x%2":
        "Диапазон адресов HEX вне допустимых пределов: 0x%1 - 0x%2",
    "Cannot open firmware file: %1": "Не удалось открыть файл прошивки: %1",
    "Firmware file is empty": "Файл прошивки пуст",
    "%1 B": "%1 Б",
    "%1 KB (%2 bytes)": "%1 КБ (%2 байт)",
    "%1 MB (%2 bytes)": "%1 МБ (%2 байт)",

    # ---------------- IapWorker ----------------
    "Unknown error": "Неизвестная ошибка",
    "Failed to initialize hidapi": "Не удалось инициализировать hidapi",
    "Cancelled while waiting for the IAP device": "Отменено во время ожидания устройства IAP",
    "Connected to IAP device (VID:0x%1 PID:0x%2)":
        "Подключено к устройству IAP (VID:0x%1 PID:0x%2)",
    "Waiting for the IAP device (VID:0x%1 PID:0x%2) ...":
        "Ожидание устройства IAP (VID:0x%1 PID:0x%2) ...",
    "IAP device not found after waiting %1 seconds":
        "Устройство IAP не найдено после ожидания %1 с",
    "Write cancelled": "Запись отменена",
    "HID write failed: %1": "Ошибка записи HID: %1",
    "HID write timed out (%1 ms)": "Тайм-аут записи HID (%1 мс)",
    "Read cancelled": "Чтение отменено",
    "HID read failed: %1": "Ошибка чтения HID: %1",
    "Upgrade cancelled": "Обновление отменено",
    "Device is already in IAP mode, skipping the mode switch":
        "Устройство уже в режиме IAP, переключение режима пропущено",
    "No usable CH375 device index, cannot send the switch command":
        "Нет доступного индекса устройства CH375, команду переключения отправить нельзя",
    "Sending enter-IAP-mode command to device (CH375 index %1) ...":
        "Отправка устройству команды перехода в режим IAP (индекс CH375 %1) ...",
    "Sending enter-IAP-mode command over libusb (bus %1, address %2) ...":
        "Отправка команды перехода в режим IAP через libusb (шина %1, адрес %2) ...",
    "Opening %1 at the IAP baud rate %2 ...": "Открытие %1 со скоростью IAP %2 ...",
    "Failed to enter IAP mode: %1": "Не удалось перейти в режим IAP: %1",
    "Command sent, waiting for the device to reset into a HID IAP device ...":
        "Команда отправлена, ожидание перезагрузки устройства в HID-устройство IAP ...",
    "Erasing FLASH, start address 0x%1": "Стирание FLASH, начальный адрес 0x%1",
    "Erasing FLASH ...": "Стирание FLASH ...",
    "Failed to send the erase command": "Не удалось отправить команду стирания",
    "Erase response timed out": "Тайм-аут ответа на стирание",
    "Erase failed, error code: %1": "Ошибка стирания, код ошибки: %1",
    "Erase complete": "Стирание завершено",
    "Programming FLASH, %1 bytes in total": "Программирование FLASH, всего %1 байт",
    "Programming FLASH ...": "Программирование FLASH ...",
    "Failed to write data, offset %1": "Не удалось записать данные, смещение %1",
    "Programming response timed out, offset %1":
        "Тайм-аут ответа при программировании, смещение %1",
    "Programming failed, error code %1, offset %2":
        "Ошибка программирования, код %1, смещение %2",
    "Programming FLASH ... %1%": "Программирование FLASH ... %1%",
    "Programming complete": "Программирование завершено",
    "Verifying FLASH ...": "Проверка FLASH ...",
    "Failed to send the verify command, offset %1":
        "Не удалось отправить команду проверки, смещение %1",
    "Verify response timed out, offset %1": "Тайм-аут ответа проверки, смещение %1",
    "Verification failed, error code %1, address 0x%2":
        "Проверка не пройдена, код ошибки %1, адрес 0x%2",
    "Verifying FLASH ... %1%": "Проверка FLASH ... %1%",
    "Verification succeeded": "Проверка успешна",
    "Sending the upgrade-finish command ...": "Отправка команды завершения обновления ...",
    "Finishing upgrade ...": "Завершение обновления ...",
    "Failed to send the finish command": "Не удалось отправить команду завершения",
    "Device confirmed the upgrade": "Устройство подтвердило обновление",
    "Device has reset (no response is normal)":
        "Устройство перезагрузилось (отсутствие ответа — норма)",
    "Reading firmware file ...": "Чтение файла прошивки ...",
    "Failed to load firmware: %1": "Не удалось загрузить прошивку: %1",
    "Firmware loaded: %1": "Прошивка загружена: %1",
    "  Format: %1, size: %2 bytes": "  Формат: %1, размер: %2 байт",
    "Intel HEX": "Intel HEX",
    "BIN": "BIN",
    "  Address range: 0x%1 - 0x%2": "  Диапазон адресов: 0x%1 - 0x%2",
    "  Checksum: 0x%1": "  Контрольная сумма: 0x%1",
    "Firmware data is empty": "Данные прошивки пусты",
    "Starting upgrade ...": "Начало обновления ...",
    "========== Firmware upgrade started %1 ==========":
        "========== Начало обновления прошивки %1 ==========",
    "Failed to load the firmware file": "Не удалось загрузить файл прошивки",
    "Entering IAP mode ...": "Переход в режим IAP ...",
    "Unable to enter IAP mode": "Не удалось перейти в режим IAP",
    "Looking for the IAP device ...": "Поиск устройства IAP ...",
    "No device in IAP mode found": "Устройство в режиме IAP не найдено",
    "Connected to the IAP device": "Подключено к устройству IAP",
    "Failed to erase FLASH": "Не удалось стереть FLASH",
    "Failed to program FLASH": "Не удалось запрограммировать FLASH",
    "Failed to verify FLASH": "Не удалось проверить FLASH",
    "Failed to finish the upgrade": "Не удалось завершить обновление",
    "Upgrade complete": "Обновление завершено",
    "========== Firmware upgrade succeeded ==========":
        "========== Обновление прошивки успешно ==========",
    "Firmware upgrade succeeded, the device will restart":
        "Прошивка обновлена, устройство перезапустится",

    # ---------------- LanguageManager ----------------
    "Follow System(&A)": "Как в системе(&A)",
    "English(&E)": "Английский(&E)",
    "Simplified Chinese(&C)": "Китайский (упрощённый)(&C)",
    "Russian(&R)": "Русский(&R)",
    "German(&G)": "Немецкий(&G)",
    "Spanish(&S)": "Испанский(&S)",
    "Simplified Chinese": "Китайский (упрощённый)",
    "English": "Английский",
    "Russian": "Русский",
    "German": "Немецкий",
    "Spanish": "Испанский",

    # ---------------- MainWindow ----------------
    "CH32H417 Logic Analyzer Firmware Upgrade Tool":
        "CH32H417 — обновление прошивки логического анализатора",
    "Device": "Устройство",
    "Firmware File": "Файл прошивки",
    "IAP Settings": "Параметры IAP",
    "Device List:": "Список устройств:",
    "Device Status:": "Состояние устройства:",
    "Firmware Version:": "Версия прошивки:",
    "File Path:": "Путь к файлу:",
    "Firmware Info:": "Прошивка:",
    "BIN Base Address: 0x": "Адрес BIN: 0x",
    "VID: 0x": "VID: 0x",
    "PID: 0x": "PID: 0x",
    "Defaults: VID=0x1A86 PID=0xFE17": "По умолчанию: VID=0x1A86 PID=0xFE17",
    "Refresh(&R)": "Обновить(&R)",
    "Browse(&B)...": "Обзор(&B)...",
    "Programming start address for .bin files (hexadecimal, e.g. 08006000)":
        "Начальный адрес программирования для файлов .bin (шестнадцатеричный, например 08006000)",
    "Hexadecimal, e.g. 08006000": "Шестнадцатеричное, например 08006000",
    "Select or drop a .hex / .bin firmware file":
        "Выберите или перетащите файл прошивки .hex / .bin",
    "Upgrade Log": "Журнал обновления",
    "Start Upgrade(&S)": "Начать обновление(&S)",
    "Exit(&X)": "Выход(&X)",
    "File(&F)": "Файл(&F)",
    "Open Firmware(&O)...": "Открыть прошивку(&O)...",
    "Tools(&T)": "Инструменты(&T)",
    "Refresh Devices(&R)": "Обновить устройства(&R)",
    "Clear Log(&L)": "Очистить журнал(&L)",
    "View(&V)": "Вид(&V)",
    "Language(&L)": "Язык(&L)",
    "Help(&H)": "Справка(&H)",
    "About(&A)": "О программе(&A)",
    "(No device found)": "(Устройство не найдено)",
    "No device found": "Устройство не найдено",
    "IAP Mode": "Режим IAP",
    "Run Mode": "Режим работы",
    "<font color='%1'>Connected (application mode, CH375 channel)</font>":
        "<font color='%1'>Подключено (режим приложения, канал CH375)</font>",
    "<font color='%1'>Connected (application mode, %2 channel)</font>":
        "<font color='%1'>Подключено (режим приложения, канал %2)</font>",
    "Software version: v%1  Hardware version: v%2":
        "Версия ПО: v%1  Версия оборудования: v%2",
    "Read failed": "Ошибка чтения",
    "<font color='%1'>Connected (IAP upgrade mode)</font>":
        "<font color='%1'>Подключено (режим обновления IAP)</font>",
    "<font color='%1'>Connected (IAP upgrade mode, HID channel)</font>":
        "<font color='%1'>Подключено (режим обновления IAP, канал HID)</font>",
    "-": "-",
    "<font color='%1'>No device found</font>":
        "<font color='%1'>Устройство не найдено</font>",
    "<font color='%1'>Device in use by another program</font>":
        "<font color='%1'>Устройство занято другой программой</font>",
    "Slot %1: 0x%2": "Слот %1: 0x%2",
    "Reboot into Active Slot(&B)": "Перезагрузить в активный слот(&B)",
    "Switch APP Slot(&S)": "Переключить слот APP(&S)",
    "Rebooting the device into its active slot ...":
        "Перезагрузка устройства в активный слот ...",
    "Reboot failed: %1": "Ошибка перезагрузки: %1",
    "Reboot request accepted, the device restarts ...":
        "Запрос на перезагрузку принят, устройство перезапускается ...",
    "Switching to APP slot %1 (0x%2) ...": "Переключение на слот APP %1 (0x%2) ...",
    "Slot switch failed: %1": "Ошибка переключения слота: %1",
    "Slot %1 is now active, the device reboots into it ...":
        "Слот %1 теперь активен, устройство перезагружается в него ...",
    "Not available while an upgrade is running": "Недоступно во время обновления",
    "Needs a board that sits in the IAP bootloader":
        "Требуется плата, находящаяся в загрузчике IAP",
    "Not Available": "Недоступно",
    "Wait for the running upgrade to finish.": "Дождитесь завершения текущего обновления.",
    "This command needs a board that sits in the IAP bootloader, "
    "the current device is in application mode.":
        "Эта команда требует плату в загрузчике IAP, текущее устройство находится "
        "в режиме приложения.",
    "No CH32H417 device in IAP mode found.\n"
    "These commands need a board that sits in the bootloader "
    "(power-cycle it with the button held).":
        "Устройство CH32H417 в режиме IAP не найдено.\n"
        "Эти команды требуют плату в загрузчике (переподключите питание, "
        "удерживая кнопку).",
    "Reboot into &IAP": "Перезагрузить в &IAP",
    "Reboot into:": "Перезагрузить в:",
    "Slot %1": "Слот %1",
    "Make slot %1 (0x%2) the active one and boot it":
        "Сделать слот %1 (0x%2) активным и загрузить его",
    "Leave &IAP": "Выйти из &IAP",
    "Reboot the board and run the active APP slot again":
        "Перезагрузить плату и снова запустить активный слот APP",
    "Reboot the board into its bootloader (IAP mode)":
        "Перезагрузить плату в загрузчик (режим IAP)",
    "Rebooting the device out of IAP mode ...": "Вывод устройства из режима IAP ...",
    "Leaving IAP failed: %1": "Не удалось выйти из IAP: %1",
    "Device is now in IAP mode": "Устройство теперь в режиме IAP",
    "Device is in IAP Mode": "Устройство в режиме IAP",
    "The device rebooted into IAP mode": "Устройство перезагрузилось в режим IAP",
    "Programming start address for .bin files (hexadecimal, e.g. 08006000). "
    "On the WeAct Studio Logic Analyzer V2 pick one of the three APP slots: "
    "slot 0 = logic analyzer, slot 1 = USB to UART, slot 2 = example.":
        "Начальный адрес программирования для файлов .bin (шестнадцатеричный, "
        "например 08006000).\n"
        "На WeAct Studio Logic Analyzer V2 выберите один из трёх слотов APP: "
        "слот 0 = логический анализатор, слот 1 = USB-UART, слот 2 = пример.",
    "Select Firmware File": "Выбор файла прошивки",
    "Firmware Files (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binary Files (*.bin);;All Files (*.*)":
        "Файлы прошивки (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;"
        "Двоичные файлы (*.bin);;Все файлы (*.*)",
    "<font color='%1'>No valid firmware file selected</font>":
        "<font color='%1'>Не выбран корректный файл прошивки</font>",
    "<font color='%1'>%2</font>": "<font color='%1'>%2</font>",
    "%1  Size: %2  Address: 0x%3 - 0x%4  Checksum: 0x%5":
        "%1  Размер: %2  Адрес: 0x%3 - 0x%4  КС: 0x%5",
    "Hint": "Подсказка",
    "Please select a valid firmware file first.":
        "Сначала выберите корректный файл прошивки.",
    "No Device Found": "Устройство не найдено",
    "No CH32H417 device was detected.\n\n"
    "If the device is already in IAP mode (for example powered up with the button "
    "held down), you can continue;\notherwise please connect the device first.\n\nContinue?":
        "Устройство CH32H417 не обнаружено.\n\n"
        "Если устройство уже в режиме IAP (например, включено с зажатой кнопкой), "
        "можно продолжить;\nиначе сначала подключите устройство.\n\nПродолжить?",
    "Firmware Error": "Ошибка прошивки",
    "Preparing ...": "Подготовка ...",
    "Target device: %1": "Целевое устройство: %1",
    "Target device: CH375 #%1": "Целевое устройство: CH375 #%1",
    "Target device: libusb (bus %1, address %2)":
        "Целевое устройство: libusb (шина %1, адрес %2)",
    "Target device: serial (COM port %1)":
        "Целевое устройство: последовательный порт (COM %1)",
    "Target device: IAP HID (VID:0x%1 PID:0x%2)":
        "Целевое устройство: IAP HID (VID:0x%1 PID:0x%2)",
    "Upgrade Complete": "Обновление завершено",
    "Complete": "Готово",
    "Firmware upgrade succeeded!\nThe device will restart and run the new firmware.":
        "Прошивка успешно обновлена!\n"
        "Устройство перезапустится и запустит новую прошивку.",
    "Upgrade Failed": "Обновление не удалось",
    "Failed": "Ошибка",
    "Please power-cycle the device (disconnect and reconnect the USB cable or the "
    "power supply) and run the upgrade again.":
        "Переподключите питание устройства (отсоедините и снова подключите USB-кабель "
        "или блок питания) и повторите обновление.",
    "Ready": "Готово",
    "About": "О программе",
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
    "<p>Upgrade sequence: the enter-IAP command goes out over whichever "
    "USB channel the board is on - CH375, libusb / WinUSB, or the COM "
    "port of the USB-to-UART firmware. The board then resets into a HID "
    "IAP device, followed by erase / program / verify / finish.</p>"
    "<p>A board that already sits in IAP mode can also be rebooted into "
    "its active slot, or switched to another APP slot, without "
    "downloading anything.</p>"
    "<p>Windows needs one driver for the board: the WCH CH375 driver, or "
    "WinUSB when the board is bound to libusb.</p>":
        "<h3>CH32H417 логический анализатор<br>Средство обновления прошивки</h3>"
        "<p>Версия: %1</p>"
        "<p><b>WeAct Studio</b><br>"
        "Copyright (C) 2026 WeAct Studio. Все права защищены.</p>"
        "<p>Эта программа является свободным программным обеспечением: вы можете "
        "распространять и/или изменять её на условиях GNU General Public License, "
        "опубликованной Free Software Foundation, версии 3 либо (по вашему выбору) "
        "любой более поздней версии. Программа распространяется в надежде, что она "
        "будет полезна, но БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ, в том числе без подразумеваемых "
        "гарантий ТОВАРНОЙ ПРИГОДНОСТИ или ПРИГОДНОСТИ ДЛЯ КОНКРЕТНОЙ ЦЕЛИ. "
        "Подробности см. в GNU General Public License.</p>"
        "<p>Лицензия: GPL-3.0-or-later<br>"
        "<a href='https://www.gnu.org/licenses/gpl-3.0.html'>"
        "https://www.gnu.org/licenses/gpl-3.0.html</a></p>"
        "<p>Собрано с Qt %2, статически скомпоновано в MSYS2 (MINGW64).</p>"
        "<p>Порядок обновления: команда входа в IAP отправляется по тому USB-каналу, "
        "на котором находится плата — CH375, libusb / WinUSB или COM-порт прошивки "
        "USB-UART. Затем плата перезагружается как HID-устройство IAP, после чего "
        "выполняются стирание / программирование / проверка / завершение.</p>"
        "<p>Плату, уже находящуюся в режиме IAP, можно также перезагрузить в её "
        "активный слот или переключить в другой слот APP без загрузки прошивки.</p>"
        "<p>В Windows для платы нужен один драйвер: драйвер WCH CH375 либо WinUSB, "
        "если плата привязана к libusb.</p>",
    "Upgrade in Progress": "Идёт обновление",
    "An upgrade is running; exiting now may corrupt the device firmware.\n"
    "Are you sure you want to exit?":
        "Идёт обновление; выход сейчас может повредить прошивку устройства.\n"
        "Вы уверены, что хотите выйти?",
}


# English source text -> German translation
DE = {
    # ---------------- Ch375Dev ----------------
    "Unable to load CH375DLL64.DLL / CH375DLL.DLL.\n"
    "Make sure the CH375 driver is installed and that the driver DLL is placed "
    "next to this program or in a directory on the system search path.":
        "CH375DLL64.DLL / CH375DLL.DLL konnte nicht geladen werden.\n"
        "Stellen Sie sicher, dass der CH375-Treiber installiert ist und die "
        "Treiber-DLL neben diesem Programm oder in einem Verzeichnis des "
        "System-Suchpfads liegt.",
    "Invalid device index": "Ungültiger Geräteindex",
    "Cannot open CH375 device (index %1)":
        "CH375-Gerät kann nicht geöffnet werden (Index %1)",
    "Failed to read firmware version (device did not respond)":
        "Firmware-Version konnte nicht gelesen werden (Gerät antwortet nicht)",
    "Unexpected version response: 0x%1": "Unerwartete Versionsantwort: 0x%1",
    "Failed to send the enter-IAP-mode command":
        "Befehl zum Wechsel in den IAP-Modus konnte nicht gesendet werden",
    "The device is in use by another program.\n"
    "Close the program that currently uses the board "
    "(for example the logic analyzer software) and refresh.":
        "Das Gerät wird von einem anderen Programm verwendet.\n"
        "Schließen Sie das Programm, das die Platine gerade nutzt (zum Beispiel "
        "die Logikanalysator-Software), und aktualisieren Sie die Liste.",

    # ---------------- LibusbDev ----------------
    "libusb is not available": "libusb ist nicht verfügbar",
    "Unable to initialise libusb (error %1)":
        "libusb konnte nicht initialisiert werden (Fehler %1)",
    "Failed to enumerate the USB devices (libusb error %1)":
        "USB-Geräte konnten nicht aufgelistet werden (libusb-Fehler %1)",
    "Cannot open the USB device (libusb error %1). The board must be bound to a "
    "generic USB driver (WinUSB on Windows) and must not be in use by another "
    "program.":
        "Das USB-Gerät kann nicht geöffnet werden (libusb-Fehler %1). Die Platine "
        "muss an einen generischen USB-Treiber gebunden sein (WinUSB unter Windows) "
        "und darf nicht von einem anderen Programm verwendet werden.",
    "Cannot claim the USB interface (libusb error %1). Close other programs that "
    "use the device and try again.":
        "Die USB-Schnittstelle kann nicht belegt werden (libusb-Fehler %1). "
        "Schließen Sie andere Programme, die das Gerät nutzen, und versuchen Sie "
        "es erneut.",
    "Failed to send command 0x%1 (libusb error %2)":
        "Befehl 0x%1 konnte nicht gesendet werden (libusb-Fehler %2)",
    "The device did not answer command 0x%1 (libusb error %2)":
        "Das Gerät hat nicht auf Befehl 0x%1 geantwortet (libusb-Fehler %2)",
    "The device is no longer present (bus %1, address %2)":
        "Das Gerät ist nicht mehr vorhanden (Bus %1, Adresse %2)",
    " (in use)": " (belegt)",

    # ---------------- SerialDev ----------------
    "Serial port enumeration is only supported on Windows":
        "Das Auflisten von COM-Ports wird nur unter Windows unterstützt",
    "Cannot enumerate the COM ports (error %1)":
        "COM-Ports können nicht aufgelistet werden (Fehler %1)",
    "Serial port access is only supported on Windows":
        "Der Zugriff auf COM-Ports wird nur unter Windows unterstützt",
    "%1 is open in another program.\n"
    "Close the program (for example a serial terminal) and retry.":
        "%1 ist in einem anderen Programm geöffnet.\n"
        "Schließen Sie das Programm (zum Beispiel ein serielles Terminal) und "
        "versuchen Sie es erneut.",
    "Cannot open %1 (error %2)": "%1 kann nicht geöffnet werden (Fehler %2)",
    "Cannot query the settings of %1 (error %2)":
        "Die Einstellungen von %1 können nicht abgefragt werden (Fehler %2)",
    "Cannot set the IAP baud rate on %1 (error %2)":
        "Die IAP-Baudrate kann auf %1 nicht gesetzt werden (Fehler %2)",
    "The firmware version cannot be read on the USB-UART (serial) channel":
        "Die Firmware-Version kann über den USB-UART-Kanal (seriell) nicht gelesen werden",

    # ---------------- IapCtl ----------------
    "No IAP device found (VID:0x%1 PID:0x%2).\n"
    "These commands only work while the board sits in the bootloader.":
        "Kein IAP-Gerät gefunden (VID:0x%1 PID:0x%2).\n"
        "Diese Befehle funktionieren nur, solange sich die Platine im Bootloader "
        "befindet.",
    "Unexpected answer from the bootloader: 0x%1":
        "Unerwartete Antwort vom Bootloader: 0x%1",
    "The bootloader did not answer (timeout)":
        "Der Bootloader hat nicht geantwortet (Zeitüberschreitung)",
    "Failed to send command 0x%1 to the bootloader":
        "Befehl 0x%1 konnte nicht an den Bootloader gesendet werden",
    "The bootloader refused the request (error code %1)":
        "Der Bootloader hat die Anfrage abgelehnt (Fehlercode %1)",
    "Slot number out of range (0..%1)": "Slot-Nummer außerhalb des Bereichs (0..%1)",

    # ---------------- ThemeManager / View menu ----------------
    "Follow System(&S)": "Systemeinstellung folgen(&S)",
    "Light(&L)": "Hell(&L)",
    "Dark(&D)": "Dunkel(&D)",

    # ---------------- FirmwareImage ----------------
    "Invalid HEX file: cannot parse line %1":
        "Ungültige HEX-Datei: Zeile %1 kann nicht gelesen werden",
    "Invalid HEX file: line %1 is too short":
        "Ungültige HEX-Datei: Zeile %1 ist zu kurz",
    "HEX checksum error on line %1 (0x%2)":
        "HEX-Prüfsummenfehler in Zeile %1 (0x%2)",
    "Invalid HEX file: data length mismatch on line %1":
        "Ungültige HEX-Datei: Datenlänge stimmt in Zeile %1 nicht",
    "HEX file contains no valid data record":
        "Die HEX-Datei enthält keinen gültigen Datensatz",
    "HEX address range out of bounds: 0x%1 - 0x%2":
        "HEX-Adressbereich außerhalb der Grenzen: 0x%1 - 0x%2",
    "Cannot open firmware file: %1": "Firmware-Datei kann nicht geöffnet werden: %1",
    "Firmware file is empty": "Die Firmware-Datei ist leer",
    "%1 B": "%1 B",
    "%1 KB (%2 bytes)": "%1 KB (%2 Bytes)",
    "%1 MB (%2 bytes)": "%1 MB (%2 Bytes)",

    # ---------------- IapWorker ----------------
    "Unknown error": "Unbekannter Fehler",
    "Failed to initialize hidapi": "hidapi konnte nicht initialisiert werden",
    "Cancelled while waiting for the IAP device":
        "Abgebrochen beim Warten auf das IAP-Gerät",
    "Connected to IAP device (VID:0x%1 PID:0x%2)":
        "Mit IAP-Gerät verbunden (VID:0x%1 PID:0x%2)",
    "Waiting for the IAP device (VID:0x%1 PID:0x%2) ...":
        "Warten auf das IAP-Gerät (VID:0x%1 PID:0x%2) ...",
    "IAP device not found after waiting %1 seconds":
        "IAP-Gerät nach %1 Sekunden nicht gefunden",
    "Write cancelled": "Schreiben abgebrochen",
    "HID write failed: %1": "HID-Schreiben fehlgeschlagen: %1",
    "HID write timed out (%1 ms)": "Zeitüberschreitung beim HID-Schreiben (%1 ms)",
    "Read cancelled": "Lesen abgebrochen",
    "HID read failed: %1": "HID-Lesen fehlgeschlagen: %1",
    "Upgrade cancelled": "Aktualisierung abgebrochen",
    "Device is already in IAP mode, skipping the mode switch":
        "Gerät ist bereits im IAP-Modus, Moduswechsel wird übersprungen",
    "No usable CH375 device index, cannot send the switch command":
        "Kein nutzbarer CH375-Geräteindex, der Umschaltbefehl kann nicht gesendet werden",
    "Sending enter-IAP-mode command to device (CH375 index %1) ...":
        "Sende Befehl zum Wechsel in den IAP-Modus an das Gerät (CH375-Index %1) ...",
    "Sending enter-IAP-mode command over libusb (bus %1, address %2) ...":
        "Sende Befehl zum Wechsel in den IAP-Modus über libusb (Bus %1, Adresse %2) ...",
    "Opening %1 at the IAP baud rate %2 ...": "Öffne %1 mit IAP-Baudrate %2 ...",
    "Failed to enter IAP mode: %1": "Wechsel in den IAP-Modus fehlgeschlagen: %1",
    "Command sent, waiting for the device to reset into a HID IAP device ...":
        "Befehl gesendet, warte auf Neustart des Geräts als HID-IAP-Gerät ...",
    "Erasing FLASH, start address 0x%1": "FLASH wird gelöscht, Startadresse 0x%1",
    "Erasing FLASH ...": "FLASH wird gelöscht ...",
    "Failed to send the erase command": "Löschbefehl konnte nicht gesendet werden",
    "Erase response timed out": "Zeitüberschreitung bei der Löschantwort",
    "Erase failed, error code: %1": "Löschen fehlgeschlagen, Fehlercode: %1",
    "Erase complete": "Löschen abgeschlossen",
    "Programming FLASH, %1 bytes in total": "FLASH wird beschrieben, insgesamt %1 Bytes",
    "Programming FLASH ...": "FLASH wird beschrieben ...",
    "Failed to write data, offset %1":
        "Daten konnten nicht geschrieben werden, Offset %1",
    "Programming response timed out, offset %1":
        "Zeitüberschreitung der Programmierantwort, Offset %1",
    "Programming failed, error code %1, offset %2":
        "Programmierung fehlgeschlagen, Fehlercode %1, Offset %2",
    "Programming FLASH ... %1%": "FLASH wird beschrieben ... %1%",
    "Programming complete": "Programmierung abgeschlossen",
    "Verifying FLASH ...": "FLASH wird geprüft ...",
    "Failed to send the verify command, offset %1":
        "Prüfbefehl konnte nicht gesendet werden, Offset %1",
    "Verify response timed out, offset %1":
        "Zeitüberschreitung der Prüfantwort, Offset %1",
    "Verification failed, error code %1, address 0x%2":
        "Prüfung fehlgeschlagen, Fehlercode %1, Adresse 0x%2",
    "Verifying FLASH ... %1%": "FLASH wird geprüft ... %1%",
    "Verification succeeded": "Prüfung erfolgreich",
    "Sending the upgrade-finish command ...":
        "Sende Befehl zum Abschluss der Aktualisierung ...",
    "Finishing upgrade ...": "Aktualisierung wird abgeschlossen ...",
    "Failed to send the finish command": "Abschlussbefehl konnte nicht gesendet werden",
    "Device confirmed the upgrade": "Gerät hat die Aktualisierung bestätigt",
    "Device has reset (no response is normal)":
        "Gerät wurde neu gestartet (keine Antwort ist normal)",
    "Reading firmware file ...": "Firmware-Datei wird gelesen ...",
    "Failed to load firmware: %1": "Firmware konnte nicht geladen werden: %1",
    "Firmware loaded: %1": "Firmware geladen: %1",
    "  Format: %1, size: %2 bytes": "  Format: %1, Größe: %2 Bytes",
    "Intel HEX": "Intel HEX",
    "BIN": "BIN",
    "  Address range: 0x%1 - 0x%2": "  Adressbereich: 0x%1 - 0x%2",
    "  Checksum: 0x%1": "  Prüfsumme: 0x%1",
    "Firmware data is empty": "Die Firmware-Daten sind leer",
    "Starting upgrade ...": "Aktualisierung wird gestartet ...",
    "========== Firmware upgrade started %1 ==========":
        "========== Firmware-Aktualisierung gestartet %1 ==========",
    "Failed to load the firmware file":
        "Die Firmware-Datei konnte nicht geladen werden",
    "Entering IAP mode ...": "Wechsel in den IAP-Modus ...",
    "Unable to enter IAP mode": "Wechsel in den IAP-Modus nicht möglich",
    "Looking for the IAP device ...": "Suche nach dem IAP-Gerät ...",
    "No device in IAP mode found": "Kein Gerät im IAP-Modus gefunden",
    "Connected to the IAP device": "Mit dem IAP-Gerät verbunden",
    "Failed to erase FLASH": "FLASH konnte nicht gelöscht werden",
    "Failed to program FLASH": "FLASH konnte nicht beschrieben werden",
    "Failed to verify FLASH": "FLASH konnte nicht geprüft werden",
    "Failed to finish the upgrade":
        "Die Aktualisierung konnte nicht abgeschlossen werden",
    "Upgrade complete": "Aktualisierung abgeschlossen",
    "========== Firmware upgrade succeeded ==========":
        "========== Firmware-Aktualisierung erfolgreich ==========",
    "Firmware upgrade succeeded, the device will restart":
        "Firmware-Aktualisierung erfolgreich, das Gerät wird neu gestartet",

    # ---------------- LanguageManager ----------------
    "Follow System(&A)": "Systemeinstellung folgen(&A)",
    "English(&E)": "Englisch(&E)",
    "Simplified Chinese(&C)": "Chinesisch (vereinfacht)(&C)",
    "Russian(&R)": "Russisch(&R)",
    "German(&G)": "Deutsch(&G)",
    "Spanish(&S)": "Spanisch(&S)",
    "Simplified Chinese": "Chinesisch (vereinfacht)",
    "English": "Englisch",
    "Russian": "Russisch",
    "German": "Deutsch",
    "Spanish": "Spanisch",

    # ---------------- MainWindow ----------------
    "CH32H417 Logic Analyzer Firmware Upgrade Tool":
        "CH32H417 Logikanalysator – Firmware-Aktualisierung",
    "Device": "Gerät",
    "Firmware File": "Firmware-Datei",
    "IAP Settings": "IAP-Einstellungen",
    "Device List:": "Geräteliste:",
    "Device Status:": "Gerätestatus:",
    "Firmware Version:": "Firmware-Version:",
    "File Path:": "Dateipfad:",
    "Firmware Info:": "Firmware-Info:",
    "BIN Base Address: 0x": "BIN-Basisadresse: 0x",
    "VID: 0x": "VID: 0x",
    "PID: 0x": "PID: 0x",
    "Defaults: VID=0x1A86 PID=0xFE17": "Standard: VID=0x1A86 PID=0xFE17",
    "Refresh(&R)": "Aktualisieren(&R)",
    "Browse(&B)...": "Durchsuchen(&B)...",
    "Programming start address for .bin files (hexadecimal, e.g. 08006000)":
        "Startadresse zum Beschreiben von .bin-Dateien (hexadezimal, z. B. 08006000)",
    "Hexadecimal, e.g. 08006000": "Hexadezimal, z. B. 08006000",
    "Select or drop a .hex / .bin firmware file":
        ".hex-/.bin-Firmware-Datei auswählen oder ablegen",
    "Upgrade Log": "Aktualisierungsprotokoll",
    "Start Upgrade(&S)": "Aktualisierung starten(&S)",
    "Exit(&X)": "Beenden(&X)",
    "File(&F)": "Datei(&F)",
    "Open Firmware(&O)...": "Firmware öffnen(&O)...",
    "Tools(&T)": "Werkzeuge(&T)",
    "Refresh Devices(&R)": "Geräte aktualisieren(&R)",
    "Clear Log(&L)": "Protokoll leeren(&L)",
    "View(&V)": "Ansicht(&V)",
    "Language(&L)": "Sprache(&L)",
    "Help(&H)": "Hilfe(&H)",
    "About(&A)": "Über(&A)",
    "(No device found)": "(Kein Gerät gefunden)",
    "No device found": "Kein Gerät gefunden",
    "IAP Mode": "IAP-Modus",
    "Run Mode": "Anwendungsmodus",
    "<font color='%1'>Connected (application mode, CH375 channel)</font>":
        "<font color='%1'>Verbunden (Anwendungsmodus, CH375-Kanal)</font>",
    "<font color='%1'>Connected (application mode, %2 channel)</font>":
        "<font color='%1'>Verbunden (Anwendungsmodus, Kanal %2)</font>",
    "Software version: v%1  Hardware version: v%2":
        "Softwareversion: v%1  Hardwareversion: v%2",
    "Read failed": "Lesen fehlgeschlagen",
    "<font color='%1'>Connected (IAP upgrade mode)</font>":
        "<font color='%1'>Verbunden (IAP-Aktualisierungsmodus)</font>",
    "<font color='%1'>Connected (IAP upgrade mode, HID channel)</font>":
        "<font color='%1'>Verbunden (IAP-Aktualisierungsmodus, HID-Kanal)</font>",
    "-": "-",
    "<font color='%1'>No device found</font>":
        "<font color='%1'>Kein Gerät gefunden</font>",
    "<font color='%1'>Device in use by another program</font>":
        "<font color='%1'>Gerät wird von einem anderen Programm verwendet</font>",
    "Slot %1: 0x%2": "Slot %1: 0x%2",
    "Reboot into Active Slot(&B)": "In aktiven Slot neu starten(&B)",
    "Switch APP Slot(&S)": "APP-Slot wechseln(&S)",
    "Rebooting the device into its active slot ...":
        "Gerät wird in den aktiven Slot neu gestartet ...",
    "Reboot failed: %1": "Neustart fehlgeschlagen: %1",
    "Reboot request accepted, the device restarts ...":
        "Neustartanforderung angenommen, das Gerät startet neu ...",
    "Switching to APP slot %1 (0x%2) ...": "Wechsle zu APP-Slot %1 (0x%2) ...",
    "Slot switch failed: %1": "Slot-Wechsel fehlgeschlagen: %1",
    "Slot %1 is now active, the device reboots into it ...":
        "Slot %1 ist jetzt aktiv, das Gerät startet darin neu ...",
    "Not available while an upgrade is running":
        "Während einer Aktualisierung nicht verfügbar",
    "Needs a board that sits in the IAP bootloader":
        "Erfordert eine Platine im IAP-Bootloader",
    "Not Available": "Nicht verfügbar",
    "Wait for the running upgrade to finish.":
        "Warten Sie, bis die laufende Aktualisierung beendet ist.",
    "This command needs a board that sits in the IAP bootloader, "
    "the current device is in application mode.":
        "Dieser Befehl erfordert eine Platine im IAP-Bootloader, das aktuelle "
        "Gerät ist im Anwendungsmodus.",
    "No CH32H417 device in IAP mode found.\n"
    "These commands need a board that sits in the bootloader "
    "(power-cycle it with the button held).":
        "Kein CH32H417-Gerät im IAP-Modus gefunden.\n"
        "Diese Befehle erfordern eine Platine im Bootloader (schalten Sie die "
        "Stromversorgung bei gedrückter Taste aus und wieder ein).",
    "Reboot into &IAP": "In &IAP neu starten",
    "Reboot into:": "Neu starten in:",
    "Slot %1": "Slot %1",
    "Make slot %1 (0x%2) the active one and boot it":
        "Slot %1 (0x%2) aktivieren und starten",
    "Leave &IAP": "&IAP verlassen",
    "Reboot the board and run the active APP slot again":
        "Platine neu starten und den aktiven APP-Slot erneut ausführen",
    "Reboot the board into its bootloader (IAP mode)":
        "Platine in den Bootloader (IAP-Modus) neu starten",
    "Rebooting the device out of IAP mode ...":
        "Gerät wird aus dem IAP-Modus neu gestartet ...",
    "Leaving IAP failed: %1": "Verlassen des IAP-Modus fehlgeschlagen: %1",
    "Device is now in IAP mode": "Gerät ist jetzt im IAP-Modus",
    "Device is in IAP Mode": "Gerät ist im IAP-Modus",
    "The device rebooted into IAP mode":
        "Das Gerät wurde in den IAP-Modus neu gestartet",
    "Programming start address for .bin files (hexadecimal, e.g. 08006000). "
    "On the WeAct Studio Logic Analyzer V2 pick one of the three APP slots: "
    "slot 0 = logic analyzer, slot 1 = USB to UART, slot 2 = example.":
        "Startadresse zum Beschreiben von .bin-Dateien (hexadezimal, z. B. 08006000).\n"
        "Beim WeAct Studio Logic Analyzer V2 einen der drei APP-Slots wählen: "
        "Slot 0 = Logikanalysator, Slot 1 = USB zu UART, Slot 2 = Beispiel.",
    "Select Firmware File": "Firmware-Datei auswählen",
    "Firmware Files (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binary Files (*.bin);;All Files (*.*)":
        "Firmware-Dateien (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;"
        "Binärdateien (*.bin);;Alle Dateien (*.*)",
    "<font color='%1'>No valid firmware file selected</font>":
        "<font color='%1'>Keine gültige Firmware-Datei ausgewählt</font>",
    "<font color='%1'>%2</font>": "<font color='%1'>%2</font>",
    "%1  Size: %2  Address: 0x%3 - 0x%4  Checksum: 0x%5":
        "%1  Größe: %2  Adresse: 0x%3 - 0x%4  Prüfsumme: 0x%5",
    "Hint": "Hinweis",
    "Please select a valid firmware file first.":
        "Bitte wählen Sie zuerst eine gültige Firmware-Datei.",
    "No Device Found": "Kein Gerät gefunden",
    "No CH32H417 device was detected.\n\n"
    "If the device is already in IAP mode (for example powered up with the button "
    "held down), you can continue;\notherwise please connect the device first.\n\nContinue?":
        "Es wurde kein CH32H417-Gerät erkannt.\n\n"
        "Wenn das Gerät bereits im IAP-Modus ist (zum Beispiel mit gedrückter Taste "
        "eingeschaltet), können Sie fortfahren;\nandernfalls schließen Sie das Gerät "
        "bitte zuerst an.\n\nFortfahren?",
    "Firmware Error": "Firmware-Fehler",
    "Preparing ...": "Vorbereitung ...",
    "Target device: %1": "Zielgerät: %1",
    "Target device: CH375 #%1": "Zielgerät: CH375 #%1",
    "Target device: libusb (bus %1, address %2)":
        "Zielgerät: libusb (Bus %1, Adresse %2)",
    "Target device: serial (COM port %1)": "Zielgerät: seriell (COM-Port %1)",
    "Target device: IAP HID (VID:0x%1 PID:0x%2)":
        "Zielgerät: IAP HID (VID:0x%1 PID:0x%2)",
    "Upgrade Complete": "Aktualisierung abgeschlossen",
    "Complete": "Fertig",
    "Firmware upgrade succeeded!\nThe device will restart and run the new firmware.":
        "Firmware-Aktualisierung erfolgreich!\n"
        "Das Gerät wird neu gestartet und führt die neue Firmware aus.",
    "Upgrade Failed": "Aktualisierung fehlgeschlagen",
    "Failed": "Fehlgeschlagen",
    "Please power-cycle the device (disconnect and reconnect the USB cable or the "
    "power supply) and run the upgrade again.":
        "Schalten Sie die Stromversorgung des Geräts aus und wieder ein (USB-Kabel "
        "oder Netzteil trennen und wieder verbinden) und führen Sie die "
        "Aktualisierung erneut aus.",
    "Ready": "Bereit",
    "About": "Über",
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
    "<p>Upgrade sequence: the enter-IAP command goes out over whichever "
    "USB channel the board is on - CH375, libusb / WinUSB, or the COM "
    "port of the USB-to-UART firmware. The board then resets into a HID "
    "IAP device, followed by erase / program / verify / finish.</p>"
    "<p>A board that already sits in IAP mode can also be rebooted into "
    "its active slot, or switched to another APP slot, without "
    "downloading anything.</p>"
    "<p>Windows needs one driver for the board: the WCH CH375 driver, or "
    "WinUSB when the board is bound to libusb.</p>":
        "<h3>CH32H417 Logikanalysator<br>Firmware-Aktualisierungswerkzeug</h3>"
        "<p>Version: %1</p>"
        "<p><b>WeAct Studio</b><br>"
        "Copyright (C) 2026 WeAct Studio. Alle Rechte vorbehalten.</p>"
        "<p>Dieses Programm ist freie Software: Sie können es unter den Bedingungen "
        "der GNU General Public License, wie von der Free Software Foundation "
        "veröffentlicht, weitergeben und/oder ändern, entweder gemäß Version 3 der "
        "Lizenz oder (nach Ihrer Wahl) jeder späteren Version. Die Veröffentlichung "
        "erfolgt in der Hoffnung, dass es nützlich ist, aber OHNE JEDE GEWÄHRLEISTUNG, "
        "sogar ohne die implizite Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR "
        "EINEN BESTIMMTEN ZWECK. Details finden Sie in der GNU General Public "
        "License.</p>"
        "<p>Lizenz: GPL-3.0-or-later<br>"
        "<a href='https://www.gnu.org/licenses/gpl-3.0.html'>"
        "https://www.gnu.org/licenses/gpl-3.0.html</a></p>"
        "<p>Erstellt mit Qt %2, statisch gelinkt mit MSYS2 (MINGW64).</p>"
        "<p>Ablauf der Aktualisierung: Der Befehl zum Wechsel in den IAP-Modus geht "
        "über den USB-Kanal, an dem die Platine hängt – CH375, libusb / WinUSB oder "
        "der COM-Port der USB-UART-Firmware. Danach startet die Platine als "
        "HID-IAP-Gerät neu, gefolgt von Löschen / Beschreiben / Prüfen / "
        "Abschließen.</p>"
        "<p>Eine Platine, die bereits im IAP-Modus ist, kann auch ohne "
        "Firmware-Download in ihren aktiven Slot neu gestartet oder in einen "
        "anderen APP-Slot umgeschaltet werden.</p>"
        "<p>Windows benötigt einen Treiber für die Platine: den WCH CH375-Treiber "
        "oder WinUSB, wenn die Platine an libusb gebunden ist.</p>",
    "Upgrade in Progress": "Aktualisierung läuft",
    "An upgrade is running; exiting now may corrupt the device firmware.\n"
    "Are you sure you want to exit?":
        "Eine Aktualisierung läuft; ein Abbruch jetzt kann die Geräte-Firmware "
        "beschädigen.\nMöchten Sie das Programm wirklich beenden?",
}


# English source text -> Spanish translation
ES = {
    # ---------------- Ch375Dev ----------------
    "Unable to load CH375DLL64.DLL / CH375DLL.DLL.\n"
    "Make sure the CH375 driver is installed and that the driver DLL is placed "
    "next to this program or in a directory on the system search path.":
        "No se puede cargar CH375DLL64.DLL / CH375DLL.DLL.\n"
        "Asegúrese de que el controlador CH375 esté instalado y de que la DLL del "
        "controlador se encuentre junto a este programa o en un directorio de la "
        "ruta de búsqueda del sistema.",
    "Invalid device index": "Índice de dispositivo no válido",
    "Cannot open CH375 device (index %1)":
        "No se puede abrir el dispositivo CH375 (índice %1)",
    "Failed to read firmware version (device did not respond)":
        "No se pudo leer la versión del firmware (el dispositivo no responde)",
    "Unexpected version response: 0x%1": "Respuesta de versión inesperada: 0x%1",
    "Failed to send the enter-IAP-mode command":
        "No se pudo enviar el comando de entrada al modo IAP",
    "The device is in use by another program.\n"
    "Close the program that currently uses the board "
    "(for example the logic analyzer software) and refresh.":
        "El dispositivo está siendo usado por otro programa.\n"
        "Cierre el programa que utiliza la placa (por ejemplo, el software del "
        "analizador lógico) y actualice la lista.",

    # ---------------- LibusbDev ----------------
    "libusb is not available": "libusb no está disponible",
    "Unable to initialise libusb (error %1)":
        "No se pudo inicializar libusb (error %1)",
    "Failed to enumerate the USB devices (libusb error %1)":
        "No se pudieron enumerar los dispositivos USB (error de libusb %1)",
    "Cannot open the USB device (libusb error %1). The board must be bound to a "
    "generic USB driver (WinUSB on Windows) and must not be in use by another "
    "program.":
        "No se puede abrir el dispositivo USB (error de libusb %1). La placa debe "
        "estar vinculada a un controlador USB genérico (WinUSB en Windows) y no "
        "debe estar en uso por otro programa.",
    "Cannot claim the USB interface (libusb error %1). Close other programs that "
    "use the device and try again.":
        "No se puede reclamar la interfaz USB (error de libusb %1). Cierre los "
        "programas que usan el dispositivo e inténtelo de nuevo.",
    "Failed to send command 0x%1 (libusb error %2)":
        "No se pudo enviar el comando 0x%1 (error de libusb %2)",
    "The device did not answer command 0x%1 (libusb error %2)":
        "El dispositivo no respondió al comando 0x%1 (error de libusb %2)",
    "The device is no longer present (bus %1, address %2)":
        "El dispositivo ya no está presente (bus %1, dirección %2)",
    " (in use)": " (en uso)",

    # ---------------- SerialDev ----------------
    "Serial port enumeration is only supported on Windows":
        "La enumeración de puertos serie solo se admite en Windows",
    "Cannot enumerate the COM ports (error %1)":
        "No se pueden enumerar los puertos COM (error %1)",
    "Serial port access is only supported on Windows":
        "El acceso al puerto serie solo se admite en Windows",
    "%1 is open in another program.\n"
    "Close the program (for example a serial terminal) and retry.":
        "%1 está abierto en otro programa.\n"
        "Cierre el programa (por ejemplo, un terminal serie) e inténtelo de nuevo.",
    "Cannot open %1 (error %2)": "No se puede abrir %1 (error %2)",
    "Cannot query the settings of %1 (error %2)":
        "No se puede consultar la configuración de %1 (error %2)",
    "Cannot set the IAP baud rate on %1 (error %2)":
        "No se puede establecer la velocidad IAP en %1 (error %2)",
    "The firmware version cannot be read on the USB-UART (serial) channel":
        "La versión del firmware no se puede leer en el canal USB-UART (serie)",

    # ---------------- IapCtl ----------------
    "No IAP device found (VID:0x%1 PID:0x%2).\n"
    "These commands only work while the board sits in the bootloader.":
        "No se encontró ningún dispositivo IAP (VID:0x%1 PID:0x%2).\n"
        "Estos comandos solo funcionan mientras la placa está en el gestor de "
        "arranque.",
    "Unexpected answer from the bootloader: 0x%1":
        "Respuesta inesperada del gestor de arranque: 0x%1",
    "The bootloader did not answer (timeout)":
        "El gestor de arranque no respondió (tiempo de espera agotado)",
    "Failed to send command 0x%1 to the bootloader":
        "No se pudo enviar el comando 0x%1 al gestor de arranque",
    "The bootloader refused the request (error code %1)":
        "El gestor de arranque rechazó la solicitud (código de error %1)",
    "Slot number out of range (0..%1)": "Número de ranura fuera de rango (0..%1)",

    # ---------------- ThemeManager / View menu ----------------
    "Follow System(&S)": "Seguir al sistema(&S)",
    "Light(&L)": "Claro(&L)",
    "Dark(&D)": "Oscuro(&D)",

    # ---------------- FirmwareImage ----------------
    "Invalid HEX file: cannot parse line %1":
        "Archivo HEX no válido: no se puede analizar la línea %1",
    "Invalid HEX file: line %1 is too short":
        "Archivo HEX no válido: la línea %1 es demasiado corta",
    "HEX checksum error on line %1 (0x%2)":
        "Error de suma de comprobación HEX en la línea %1 (0x%2)",
    "Invalid HEX file: data length mismatch on line %1":
        "Archivo HEX no válido: la longitud de datos no coincide en la línea %1",
    "HEX file contains no valid data record":
        "El archivo HEX no contiene ningún registro de datos válido",
    "HEX address range out of bounds: 0x%1 - 0x%2":
        "Rango de direcciones HEX fuera de los límites: 0x%1 - 0x%2",
    "Cannot open firmware file: %1": "No se puede abrir el archivo de firmware: %1",
    "Firmware file is empty": "El archivo de firmware está vacío",
    "%1 B": "%1 B",
    "%1 KB (%2 bytes)": "%1 KB (%2 bytes)",
    "%1 MB (%2 bytes)": "%1 MB (%2 bytes)",

    # ---------------- IapWorker ----------------
    "Unknown error": "Error desconocido",
    "Failed to initialize hidapi": "No se pudo inicializar hidapi",
    "Cancelled while waiting for the IAP device":
        "Cancelado mientras se esperaba el dispositivo IAP",
    "Connected to IAP device (VID:0x%1 PID:0x%2)":
        "Conectado al dispositivo IAP (VID:0x%1 PID:0x%2)",
    "Waiting for the IAP device (VID:0x%1 PID:0x%2) ...":
        "Esperando el dispositivo IAP (VID:0x%1 PID:0x%2) ...",
    "IAP device not found after waiting %1 seconds":
        "No se encontró el dispositivo IAP tras esperar %1 segundos",
    "Write cancelled": "Escritura cancelada",
    "HID write failed: %1": "Error de escritura HID: %1",
    "HID write timed out (%1 ms)": "Tiempo de espera agotado al escribir HID (%1 ms)",
    "Read cancelled": "Lectura cancelada",
    "HID read failed: %1": "Error de lectura HID: %1",
    "Upgrade cancelled": "Actualización cancelada",
    "Device is already in IAP mode, skipping the mode switch":
        "El dispositivo ya está en modo IAP, se omite el cambio de modo",
    "No usable CH375 device index, cannot send the switch command":
        "No hay un índice de dispositivo CH375 utilizable, no se puede enviar el "
        "comando de cambio",
    "Sending enter-IAP-mode command to device (CH375 index %1) ...":
        "Enviando el comando de entrada al modo IAP al dispositivo (índice CH375 %1) ...",
    "Sending enter-IAP-mode command over libusb (bus %1, address %2) ...":
        "Enviando el comando de entrada al modo IAP por libusb (bus %1, dirección %2) ...",
    "Opening %1 at the IAP baud rate %2 ...":
        "Abriendo %1 con la velocidad IAP %2 ...",
    "Failed to enter IAP mode: %1": "No se pudo entrar en el modo IAP: %1",
    "Command sent, waiting for the device to reset into a HID IAP device ...":
        "Comando enviado, esperando a que el dispositivo se reinicie como "
        "dispositivo HID IAP ...",
    "Erasing FLASH, start address 0x%1": "Borrando FLASH, dirección inicial 0x%1",
    "Erasing FLASH ...": "Borrando FLASH ...",
    "Failed to send the erase command": "No se pudo enviar el comando de borrado",
    "Erase response timed out": "Tiempo de espera agotado en la respuesta de borrado",
    "Erase failed, error code: %1": "Error al borrar, código de error: %1",
    "Erase complete": "Borrado completado",
    "Programming FLASH, %1 bytes in total": "Programando FLASH, %1 bytes en total",
    "Programming FLASH ...": "Programando FLASH ...",
    "Failed to write data, offset %1":
        "No se pudieron escribir los datos, desplazamiento %1",
    "Programming response timed out, offset %1":
        "Tiempo de espera agotado en la respuesta de programación, desplazamiento %1",
    "Programming failed, error code %1, offset %2":
        "Error de programación, código %1, desplazamiento %2",
    "Programming FLASH ... %1%": "Programando FLASH ... %1%",
    "Programming complete": "Programación completada",
    "Verifying FLASH ...": "Verificando FLASH ...",
    "Failed to send the verify command, offset %1":
        "No se pudo enviar el comando de verificación, desplazamiento %1",
    "Verify response timed out, offset %1":
        "Tiempo de espera agotado en la respuesta de verificación, desplazamiento %1",
    "Verification failed, error code %1, address 0x%2":
        "Verificación fallida, código de error %1, dirección 0x%2",
    "Verifying FLASH ... %1%": "Verificando FLASH ... %1%",
    "Verification succeeded": "Verificación correcta",
    "Sending the upgrade-finish command ...":
        "Enviando el comando de finalización de la actualización ...",
    "Finishing upgrade ...": "Finalizando la actualización ...",
    "Failed to send the finish command":
        "No se pudo enviar el comando de finalización",
    "Device confirmed the upgrade": "El dispositivo confirmó la actualización",
    "Device has reset (no response is normal)":
        "El dispositivo se ha reiniciado (la ausencia de respuesta es normal)",
    "Reading firmware file ...": "Leyendo el archivo de firmware ...",
    "Failed to load firmware: %1": "No se pudo cargar el firmware: %1",
    "Firmware loaded: %1": "Firmware cargado: %1",
    "  Format: %1, size: %2 bytes": "  Formato: %1, tamaño: %2 bytes",
    "Intel HEX": "Intel HEX",
    "BIN": "BIN",
    "  Address range: 0x%1 - 0x%2": "  Rango de direcciones: 0x%1 - 0x%2",
    "  Checksum: 0x%1": "  Suma de comprobación: 0x%1",
    "Firmware data is empty": "Los datos del firmware están vacíos",
    "Starting upgrade ...": "Iniciando la actualización ...",
    "========== Firmware upgrade started %1 ==========":
        "========== Actualización de firmware iniciada %1 ==========",
    "Failed to load the firmware file":
        "No se pudo cargar el archivo de firmware",
    "Entering IAP mode ...": "Entrando en el modo IAP ...",
    "Unable to enter IAP mode": "No se puede entrar en el modo IAP",
    "Looking for the IAP device ...": "Buscando el dispositivo IAP ...",
    "No device in IAP mode found": "No se encontró ningún dispositivo en modo IAP",
    "Connected to the IAP device": "Conectado al dispositivo IAP",
    "Failed to erase FLASH": "No se pudo borrar la FLASH",
    "Failed to program FLASH": "No se pudo programar la FLASH",
    "Failed to verify FLASH": "No se pudo verificar la FLASH",
    "Failed to finish the upgrade": "No se pudo finalizar la actualización",
    "Upgrade complete": "Actualización completada",
    "========== Firmware upgrade succeeded ==========":
        "========== Actualización de firmware correcta ==========",
    "Firmware upgrade succeeded, the device will restart":
        "Actualización de firmware correcta, el dispositivo se reiniciará",

    # ---------------- LanguageManager ----------------
    "Follow System(&A)": "Seguir al sistema(&A)",
    "English(&E)": "Inglés(&E)",
    "Simplified Chinese(&C)": "Chino simplificado(&C)",
    "Russian(&R)": "Ruso(&R)",
    "German(&G)": "Alemán(&G)",
    "Spanish(&S)": "Español(&S)",
    "Simplified Chinese": "Chino simplificado",
    "English": "Inglés",
    "Russian": "Ruso",
    "German": "Alemán",
    "Spanish": "Español",

    # ---------------- MainWindow ----------------
    "CH32H417 Logic Analyzer Firmware Upgrade Tool":
        "Herramienta de actualización de firmware del analizador lógico CH32H417",
    "Device": "Dispositivo",
    "Firmware File": "Archivo de firmware",
    "IAP Settings": "Ajustes de IAP",
    "Device List:": "Lista de dispositivos:",
    "Device Status:": "Estado del dispositivo:",
    "Firmware Version:": "Versión del firmware:",
    "File Path:": "Ruta del archivo:",
    "Firmware Info:": "Información del firmware:",
    "BIN Base Address: 0x": "Dirección base del BIN: 0x",
    "VID: 0x": "VID: 0x",
    "PID: 0x": "PID: 0x",
    "Defaults: VID=0x1A86 PID=0xFE17": "Valores por defecto: VID=0x1A86 PID=0xFE17",
    "Refresh(&R)": "Actualizar(&R)",
    "Browse(&B)...": "Examinar(&B)...",
    "Programming start address for .bin files (hexadecimal, e.g. 08006000)":
        "Dirección de inicio de programación para archivos .bin (hexadecimal, "
        "p. ej. 08006000)",
    "Hexadecimal, e.g. 08006000": "Hexadecimal, p. ej. 08006000",
    "Select or drop a .hex / .bin firmware file":
        "Seleccione o arrastre un archivo de firmware .hex / .bin",
    "Upgrade Log": "Registro de actualización",
    "Start Upgrade(&S)": "Iniciar actualización(&S)",
    "Exit(&X)": "Salir(&X)",
    "File(&F)": "Archivo(&F)",
    "Open Firmware(&O)...": "Abrir firmware(&O)...",
    "Tools(&T)": "Herramientas(&T)",
    "Refresh Devices(&R)": "Actualizar dispositivos(&R)",
    "Clear Log(&L)": "Borrar registro(&L)",
    "View(&V)": "Ver(&V)",
    "Language(&L)": "Idioma(&L)",
    "Help(&H)": "Ayuda(&H)",
    "About(&A)": "Acerca de(&A)",
    "(No device found)": "(No se encontró ningún dispositivo)",
    "No device found": "No se encontró ningún dispositivo",
    "IAP Mode": "Modo IAP",
    "Run Mode": "Modo aplicación",
    "<font color='%1'>Connected (application mode, CH375 channel)</font>":
        "<font color='%1'>Conectado (modo aplicación, canal CH375)</font>",
    "<font color='%1'>Connected (application mode, %2 channel)</font>":
        "<font color='%1'>Conectado (modo aplicación, canal %2)</font>",
    "Software version: v%1  Hardware version: v%2":
        "Versión de software: v%1  Versión de hardware: v%2",
    "Read failed": "Error de lectura",
    "<font color='%1'>Connected (IAP upgrade mode)</font>":
        "<font color='%1'>Conectado (modo de actualización IAP)</font>",
    "<font color='%1'>Connected (IAP upgrade mode, HID channel)</font>":
        "<font color='%1'>Conectado (modo de actualización IAP, canal HID)</font>",
    "-": "-",
    "<font color='%1'>No device found</font>":
        "<font color='%1'>No se encontró ningún dispositivo</font>",
    "<font color='%1'>Device in use by another program</font>":
        "<font color='%1'>Dispositivo en uso por otro programa</font>",
    "Slot %1: 0x%2": "Ranura %1: 0x%2",
    "Reboot into Active Slot(&B)": "Reiniciar en la ranura activa(&B)",
    "Switch APP Slot(&S)": "Cambiar ranura APP(&S)",
    "Rebooting the device into its active slot ...":
        "Reiniciando el dispositivo en su ranura activa ...",
    "Reboot failed: %1": "Error al reiniciar: %1",
    "Reboot request accepted, the device restarts ...":
        "Solicitud de reinicio aceptada, el dispositivo se reinicia ...",
    "Switching to APP slot %1 (0x%2) ...":
        "Cambiando a la ranura APP %1 (0x%2) ...",
    "Slot switch failed: %1": "Error al cambiar de ranura: %1",
    "Slot %1 is now active, the device reboots into it ...":
        "La ranura %1 está ahora activa, el dispositivo se reinicia en ella ...",
    "Not available while an upgrade is running":
        "No disponible mientras hay una actualización en curso",
    "Needs a board that sits in the IAP bootloader":
        "Requiere una placa en el gestor de arranque IAP",
    "Not Available": "No disponible",
    "Wait for the running upgrade to finish.":
        "Espere a que finalice la actualización en curso.",
    "This command needs a board that sits in the IAP bootloader, "
    "the current device is in application mode.":
        "Este comando requiere una placa en el gestor de arranque IAP; el "
        "dispositivo actual está en modo aplicación.",
    "No CH32H417 device in IAP mode found.\n"
    "These commands need a board that sits in the bootloader "
    "(power-cycle it with the button held).":
        "No se encontró ningún dispositivo CH32H417 en modo IAP.\n"
        "Estos comandos requieren una placa en el gestor de arranque (corte y "
        "restablezca la alimentación con el botón pulsado).",
    "Reboot into &IAP": "Reiniciar en &IAP",
    "Reboot into:": "Reiniciar en:",
    "Slot %1": "Ranura %1",
    "Make slot %1 (0x%2) the active one and boot it":
        "Hacer activa la ranura %1 (0x%2) y arrancarla",
    "Leave &IAP": "Salir de &IAP",
    "Reboot the board and run the active APP slot again":
        "Reiniciar la placa y ejecutar de nuevo la ranura APP activa",
    "Reboot the board into its bootloader (IAP mode)":
        "Reiniciar la placa en su gestor de arranque (modo IAP)",
    "Rebooting the device out of IAP mode ...":
        "Reiniciando el dispositivo fuera del modo IAP ...",
    "Leaving IAP failed: %1": "Error al salir del modo IAP: %1",
    "Device is now in IAP mode": "El dispositivo está ahora en modo IAP",
    "Device is in IAP Mode": "El dispositivo está en modo IAP",
    "The device rebooted into IAP mode": "El dispositivo se reinició en modo IAP",
    "Programming start address for .bin files (hexadecimal, e.g. 08006000). "
    "On the WeAct Studio Logic Analyzer V2 pick one of the three APP slots: "
    "slot 0 = logic analyzer, slot 1 = USB to UART, slot 2 = example.":
        "Dirección de inicio de programación para archivos .bin (hexadecimal, "
        "p. ej. 08006000).\n"
        "En el WeAct Studio Logic Analyzer V2 elija una de las tres ranuras APP: "
        "ranura 0 = analizador lógico, ranura 1 = USB a UART, ranura 2 = ejemplo.",
    "Select Firmware File": "Seleccionar archivo de firmware",
    "Firmware Files (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binary Files (*.bin);;All Files (*.*)":
        "Archivos de firmware (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;"
        "Archivos binarios (*.bin);;Todos los archivos (*.*)",
    "<font color='%1'>No valid firmware file selected</font>":
        "<font color='%1'>No se ha seleccionado un archivo de firmware válido</font>",
    "<font color='%1'>%2</font>": "<font color='%1'>%2</font>",
    "%1  Size: %2  Address: 0x%3 - 0x%4  Checksum: 0x%5":
        "%1  Tamaño: %2  Dirección: 0x%3 - 0x%4  Suma: 0x%5",
    "Hint": "Sugerencia",
    "Please select a valid firmware file first.":
        "Seleccione primero un archivo de firmware válido.",
    "No Device Found": "No se encontró ningún dispositivo",
    "No CH32H417 device was detected.\n\n"
    "If the device is already in IAP mode (for example powered up with the button "
    "held down), you can continue;\notherwise please connect the device first.\n\nContinue?":
        "No se detectó ningún dispositivo CH32H417.\n\n"
        "Si el dispositivo ya está en modo IAP (por ejemplo, encendido con el botón "
        "pulsado), puede continuar;\nde lo contrario, conecte primero el "
        "dispositivo.\n\n¿Continuar?",
    "Firmware Error": "Error de firmware",
    "Preparing ...": "Preparando ...",
    "Target device: %1": "Dispositivo de destino: %1",
    "Target device: CH375 #%1": "Dispositivo de destino: CH375 #%1",
    "Target device: libusb (bus %1, address %2)":
        "Dispositivo de destino: libusb (bus %1, dirección %2)",
    "Target device: serial (COM port %1)":
        "Dispositivo de destino: serie (puerto COM %1)",
    "Target device: IAP HID (VID:0x%1 PID:0x%2)":
        "Dispositivo de destino: IAP HID (VID:0x%1 PID:0x%2)",
    "Upgrade Complete": "Actualización completada",
    "Complete": "Completado",
    "Firmware upgrade succeeded!\nThe device will restart and run the new firmware.":
        "¡Actualización de firmware correcta!\n"
        "El dispositivo se reiniciará y ejecutará el nuevo firmware.",
    "Upgrade Failed": "Actualización fallida",
    "Failed": "Fallido",
    "Please power-cycle the device (disconnect and reconnect the USB cable or the "
    "power supply) and run the upgrade again.":
        "Corte y restablezca la alimentación del dispositivo (desconecte y vuelva a "
        "conectar el cable USB o la fuente de alimentación) y repita la "
        "actualización.",
    "Ready": "Listo",
    "About": "Acerca de",
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
    "<p>Upgrade sequence: the enter-IAP command goes out over whichever "
    "USB channel the board is on - CH375, libusb / WinUSB, or the COM "
    "port of the USB-to-UART firmware. The board then resets into a HID "
    "IAP device, followed by erase / program / verify / finish.</p>"
    "<p>A board that already sits in IAP mode can also be rebooted into "
    "its active slot, or switched to another APP slot, without "
    "downloading anything.</p>"
    "<p>Windows needs one driver for the board: the WCH CH375 driver, or "
    "WinUSB when the board is bound to libusb.</p>":
        "<h3>Analizador lógico CH32H417<br>Herramienta de actualización de "
        "firmware</h3>"
        "<p>Versión: %1</p>"
        "<p><b>WeAct Studio</b><br>"
        "Copyright (C) 2026 WeAct Studio. Todos los derechos reservados.</p>"
        "<p>Este programa es software libre: puede redistribuirlo y/o modificarlo "
        "según los términos de la Licencia Pública General de GNU publicada por la "
        "Free Software Foundation, ya sea la versión 3 de la licencia o (a su "
        "elección) cualquier versión posterior. Se distribuye con la esperanza de "
        "que sea útil, pero SIN NINGUNA GARANTÍA, ni siquiera la garantía implícita "
        "de COMERCIABILIDAD o IDONEIDAD PARA UN PROPÓSITO PARTICULAR. Consulte la "
        "Licencia Pública General de GNU para más detalles.</p>"
        "<p>Licencia: GPL-3.0-or-later<br>"
        "<a href='https://www.gnu.org/licenses/gpl-3.0.html'>"
        "https://www.gnu.org/licenses/gpl-3.0.html</a></p>"
        "<p>Compilado con Qt %2, enlazado estáticamente con MSYS2 (MINGW64).</p>"
        "<p>Secuencia de actualización: el comando de entrada al modo IAP se envía "
        "por el canal USB en el que esté la placa: CH375, libusb / WinUSB o el "
        "puerto COM del firmware USB a UART. Después la placa se reinicia como "
        "dispositivo HID IAP y se ejecutan borrado / programación / verificación / "
        "finalización.</p>"
        "<p>Una placa que ya esté en modo IAP también puede reiniciarse en su "
        "ranura activa o cambiarse a otra ranura APP sin descargar nada.</p>"
        "<p>Windows necesita un controlador para la placa: el controlador WCH "
        "CH375 o WinUSB si la placa está vinculada a libusb.</p>",
    "Upgrade in Progress": "Actualización en curso",
    "An upgrade is running; exiting now may corrupt the device firmware.\n"
    "Are you sure you want to exit?":
        "Hay una actualización en curso; salir ahora puede dañar el firmware del "
        "dispositivo.\n¿Seguro que desea salir?",
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

    for name, table in (('app_zh_CN.ts', ZH),
                        ('app_ru.ts', RU),
                        ('app_de.ts', DE),
                        ('app_es.ts', ES)):
        path = os.path.join(base, name)
        if not os.path.exists(path):
            print('%s: missing, run lupdate first' % name)
            continue

        missing = fill(path, lambda s, t=table: t.get(s))

        print('%s: filled, missing %d' % (name, len(missing)))
        for ctx, src in missing:
            print('  [MISSING][%s] %s' % (ctx, src.replace('\n', '\\n')))


if __name__ == '__main__':
    main()
