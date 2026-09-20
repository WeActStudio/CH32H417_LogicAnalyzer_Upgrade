# -*- coding: utf-8 -*-
"""
填充 Qt 翻译文件：

- translations/app_zh_CN.ts : 源语言即简体中文，译文与原文相同
- translations/app_en.ts    : 填入英文译文

用法：
    python tools/i18n_fill.py <工程目录>
"""
import sys
import os
import xml.etree.ElementTree as ET

# 源文（简体中文） -> 英文译文
EN = {
    # ---------------- Ch375Dev ----------------
    "无法加载 CH375DLL64.DLL / CH375DLL.DLL。\n请确认已安装 CH375 驱动，且驱动 DLL 位于本程序目录或系统可搜索路径中。":
        "Unable to load CH375DLL64.DLL / CH375DLL.DLL.\n"
        "Please make sure the CH375 driver is installed and the driver DLL is in the "
        "application folder or another directory searched by the system.",
    "设备索引无效": "Invalid device index",
    "无法打开 CH375 设备 (索引 %1)": "Cannot open CH375 device (index %1)",
    "读取固件版本失败（设备无响应）": "Failed to read firmware version (device not responding)",
    "版本响应异常：0x%1": "Unexpected version response: 0x%1",
    "发送进入 IAP 模式命令失败": "Failed to send the enter-IAP-mode command",

    # ---------------- ThemeManager / 视图菜单 ----------------
    "视图(&V)": "View(&V)",
    "跟随系统(&S)": "Follow System(&S)",
    "浅色(&L)": "Light(&L)",
    "深色(&D)": "Dark(&D)",

    # ---------------- FirmwareImage ----------------
    "HEX 格式错误：第 %1 行无法解析": "HEX format error: line %1 cannot be parsed",
    "HEX 格式错误：第 %1 行长度不足": "HEX format error: line %1 is too short",
    "HEX 校验和错误：第 %1 行 (0x%2)": "HEX checksum error: line %1 (0x%2)",
    "HEX 格式错误：第 %1 行数据长度不符": "HEX format error: data length mismatch at line %1",
    "HEX 文件中没有有效的数据记录": "No valid data records in the HEX file",
    "HEX 地址范围异常：0x%1 - 0x%2": "HEX address range abnormal: 0x%1 - 0x%2",
    "无法打开固件文件：%1": "Cannot open firmware file: %1",
    "固件文件为空": "Firmware file is empty",

    # ---------------- IapWorker ----------------
    "未知错误": "Unknown error",
    "hidapi 初始化失败": "hidapi initialization failed",
    "已取消：等待 IAP 设备": "Cancelled: waiting for IAP device",
    "已连接 IAP 设备 (VID:0x%1 PID:0x%2)": "Connected to IAP device (VID:0x%1 PID:0x%2)",
    "等待 IAP 设备出现 (VID:0x%1 PID:0x%2) ...": "Waiting for IAP device (VID:0x%1 PID:0x%2) ...",
    "未找到 IAP 设备，已等待 %1 秒": "IAP device not found after waiting %1 seconds",
    "写入被取消": "Write cancelled",
    "HID 写入失败：%1": "HID write failed: %1",
    "HID 写入超时 (%1 ms)": "HID write timed out (%1 ms)",
    "读取被取消": "Read cancelled",
    "HID 读取失败：%1": "HID read failed: %1",
    "已取消升级": "Upgrade cancelled",
    "设备已处于 IAP 模式，跳过模式切换": "Device already in IAP mode, skipping mode switch",
    "没有可用的 CH375 设备索引，无法发送切换命令":
        "No usable CH375 device index, cannot send the switch command",
    "向设备 (CH375 索引 %1) 发送进入 IAP 模式命令 ...":
        "Sending enter-IAP-mode command to device (CH375 index %1) ...",
    "进入 IAP 模式失败：%1": "Failed to enter IAP mode: %1",
    "命令已发送，等待设备复位并切换为 HID IAP 设备 ...":
        "Command sent, waiting for the device to reset and re-enumerate as an HID IAP device ...",
    "擦除 FLASH，起始地址 0x%1": "Erasing FLASH from address 0x%1",
    "擦除 FLASH ...": "Erasing FLASH ...",
    "发送擦除命令失败": "Failed to send the erase command",
    "擦除响应超时": "Erase response timed out",
    "擦除失败，错误码：%1": "Erase failed, error code: %1",
    "擦除完成": "Erase completed",
    "编程 FLASH，共 %1 字节": "Programming FLASH, %1 bytes in total",
    "编程 FLASH ...": "Programming FLASH ...",
    "写入数据失败，偏移 %1": "Failed to write data at offset %1",
    "编程响应超时，偏移 %1": "Programming response timed out at offset %1",
    "编程失败，错误码 %1，偏移 %2": "Programming failed, error code %1, offset %2",
    "编程完成": "Programming completed",
    "校验 FLASH ...": "Verifying FLASH ...",
    "校验 FLASH ... %1%": "Verifying FLASH ... %1%",
    "编程 FLASH ... %1%": "Programming FLASH ... %1%",
    "发送校验命令失败，偏移 %1": "Failed to send verify command at offset %1",
    "校验响应超时，偏移 %1": "Verify response timed out at offset %1",
    "校验失败，错误码 %1，地址 0x%2": "Verification failed, error code %1, address 0x%2",
    "校验成功": "Verification succeeded",
    "发送升级结束命令 ...": "Sending finish-upgrade command ...",
    "结束升级 ...": "Finishing upgrade ...",
    "发送结束命令失败": "Failed to send the finish command",
    "设备确认升级完成": "Device confirmed the upgrade",
    "设备已复位（无应答属正常现象）": "Device has reset (no response is normal)",
    "读取固件文件 ...": "Reading firmware file ...",
    "固件加载失败：%1": "Failed to load firmware: %1",
    "已加载固件：%1": "Firmware loaded: %1",
    "  格式：%1，大小：%2 字节": "  Format: %1, size: %2 bytes",
    "Intel HEX": "Intel HEX",
    "BIN": "BIN",
    "  地址范围：0x%1 - 0x%2": "  Address range: 0x%1 - 0x%2",
    "  校验和：0x%1": "  Checksum: 0x%1",
    "固件数据为空": "Firmware data is empty",
    "开始升级 ...": "Starting upgrade ...",
    "========== 开始固件升级 %1 ==========": "========== Starting firmware upgrade %1 ==========",
    "固件文件加载失败": "Failed to load the firmware file",
    "进入 IAP 模式 ...": "Entering IAP mode ...",
    "无法进入 IAP 模式": "Unable to enter IAP mode",
    "查找 IAP 设备 ...": "Searching for IAP device ...",
    "未找到 IAP 模式的设备": "No device in IAP mode was found",
    "已连接 IAP 设备": "Connected to IAP device",
    "擦除 FLASH 失败": "Failed to erase FLASH",
    "编程 FLASH 失败": "Failed to program FLASH",
    "校验 FLASH 失败": "Failed to verify FLASH",
    "结束升级失败": "Failed to finish the upgrade",
    "升级完成": "Upgrade completed",
    "========== 固件升级成功 ==========": "========== Firmware upgrade succeeded ==========",
    "固件升级成功，设备将重新启动": "Firmware upgrade succeeded, the device will restart",
    "%1 KB (%2 bytes)": "%1 KB (%2 bytes)",
    "%1 MB (%2 bytes)": "%1 MB (%2 bytes)",

    # ---------------- LanguageManager ----------------
    "跟随系统(&A)": "Follow System(&A)",
    "English(&E)": "English(&E)",
    "简体中文(&C)": "Simplified Chinese(&C)",
    "简体中文": "Simplified Chinese",
    "English": "English",

    # ---------------- MainWindow ----------------
    "CH32H417 逻辑分析仪固件升级工具": "CH32H417 Logic Analyzer Firmware Upgrade Tool",
    "设备": "Device",
    "固件文件": "Firmware File",
    "IAP 参数": "IAP Parameters",
    "设备列表：": "Device list:",
    "设备状态：": "Device status:",
    "固件版本：": "Firmware version:",
    "文件路径：": "File path:",
    "固件信息：": "Firmware info:",
    "BIN 基地址：0x": "BIN base address: 0x",
    "VID：0x": "VID: 0x",
    "PID：0x": "PID: 0x",
    "默认值 VID=0x1A86 PID=0xFE17": "Default VID=0x1A86 PID=0xFE17",
    "刷新(&R)": "&Refresh",
    "浏览(&B)...": "&Browse...",
    ".bin 文件的烧录起始地址（十六进制，例如 08006000）":
        "Programming start address for .bin files (hexadecimal, e.g. 08006000)",
    "十六进制，例如 08006000": "Hexadecimal, e.g. 08006000",
    "选择或直接拖入 .hex / .bin 固件文件": "Select or drag and drop a .hex / .bin firmware file",
    "升级日志：": "Upgrade log:",
    "开始升级(&S)": "&Start Upgrade",
    "取消(&C)": "&Cancel",
    "退出(&X)": "E&xit",
    "文件(&F)": "&File",
    "打开固件(&O)...": "&Open Firmware...",
    "工具(&T)": "&Tools",
    "刷新设备(&R)": "&Refresh Devices",
    "清空日志(&L)": "Clear &Log",
    "语言(&L)": "&Language",
    "帮助(&H)": "&Help",
    "关于(&A)": "&About",
    "(未发现设备)": "(No device found)",
    "CH32H417": "CH32H417",
    "<font color='%1'>已连接（运行模式，CH375 通道）</font>":
        "<font color='%1'>Connected (run mode, CH375 channel)</font>",
    "软件版本：v%1　硬件版本：v%2": "Software version: v%1    Hardware version: v%2",
    "读取失败": "Failed to read",
    "<font color='%1'>已连接（IAP 升级模式，HID 通道）</font>":
        "<font color='%1'>Connected (IAP upgrade mode, HID channel)</font>",
    "-": "-",
    "<font color='%1'>未发现设备</font>": "<font color='%1'>No device found</font>",
    "选择固件文件": "Select Firmware File",
    "固件文件 (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;二进制文件 (*.bin);;所有文件 (*.*)":
        "Firmware Files (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binary Files (*.bin);;All Files (*.*)",
    "<font color='%1'>尚未选择有效的固件文件</font>":
        "<font color='%1'>No valid firmware file selected</font>",
    "<font color='%1'>%2</font>": "<font color='%1'>%2</font>",
    "%1　大小：%2　地址：0x%3 - 0x%4　校验和：0x%5":
        "%1  Size: %2  Address: 0x%3 - 0x%4  Checksum: 0x%5",
    "提示": "Notice",
    "请先选择一个有效的固件文件。": "Please select a valid firmware file first.",
    "未发现设备": "No Device Found",
    "当前没有检测到 CH32H417 设备。\n\n如果设备已经处于 IAP 模式（例如按住按键上电），可以继续升级；\n否则请先连接设备。\n\n是否继续？":
        "No CH32H417 device was detected.\n\n"
        "If the device is already in IAP mode (for example, powered on with the button held), "
        "you can continue;\notherwise please connect the device first.\n\nContinue?",
    "固件错误": "Firmware Error",
    "准备中 ...": "Preparing ...",
    "目标设备：%1": "Target device: %1",
    "正在请求取消 ...": "Requesting cancellation ...",
    "完成": "Completed",
    "固件升级成功！\n设备将重启并运行新固件。":
        "Firmware upgrade succeeded!\nThe device will restart and run the new firmware.",
    "升级失败": "Upgrade failed",
    "失败": "Failed",
    "就绪": "Ready",
    "关于": "About",
    "<h3>CH32H417 逻辑分析仪固件升级工具</h3><p>版本：%1</p><p>基于 Qt 6 开发，使用 MSYS2 (MINGW64) 静态编译。</p><p>升级流程：CH375 通道发送进入 IAP 命令 → 设备复位为 HID IAP 设备 → 擦除 / 编程 / 校验 / 结束。</p><p>需要安装 CH375 驱动。</p>":
        "<h3>CH32H417 Logic Analyzer Firmware Upgrade Tool</h3>"
        "<p>Version: %1</p>"
        "<p>Built with Qt 6, statically compiled with MSYS2 (MINGW64).</p>"
        "<p>Upgrade flow: send the enter-IAP command over the CH375 channel → the device resets and "
        "re-enumerates as an HID IAP device → erase / program / verify / finish.</p>"
        "<p>The CH375 driver must be installed.</p>",
    "正在升级": "Upgrading",
    "升级正在进行中，现在退出可能导致设备固件损坏。\n确定要退出吗？":
        "An upgrade is in progress. Exiting now may corrupt the device firmware.\n"
        "Are you sure you want to quit?",
}


def fill(path, translator):
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

    # 中文：源语言即中文，译文同原文
    missing_zh = fill(os.path.join(base, 'app_zh_CN.ts'), lambda s: s)
    # 英文
    missing_en = fill(os.path.join(base, 'app_en.ts'), lambda s: EN.get(s))

    print('zh_CN: filled, missing %d' % len(missing_zh))
    print('en   : filled, missing %d' % len(missing_en))
    for ctx, src in missing_en:
        print('  [MISSING][%s] %s' % (ctx, src.replace('\n', '\\n')))


if __name__ == '__main__':
    main()
