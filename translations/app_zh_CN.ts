<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="zh_CN">
<context>
    <name>Ch375Dev</name>
    <message>
        <location filename="../src/ch375dev.cpp" line="80" />
        <source>The device is in use by another program.
Close the program that currently uses the board (for example the logic analyzer software) and refresh.</source>
        <translation>设备正被其他程序占用。
请关闭当前使用该设备的程序（例如逻辑分析仪上位机软件）后刷新重试。</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="102" />
        <source>Unable to load CH375DLL64.DLL / CH375DLL.DLL.
Make sure the CH375 driver is installed and that the driver DLL is placed next to this program or in a directory on the system search path.</source>
        <translation>无法加载 CH375DLL64.DLL / CH375DLL.DLL。
请确认已安装 CH375 驱动，且驱动 DLL 位于本程序目录或系统可搜索路径中。</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="211" />
        <location filename="../src/ch375dev.cpp" line="268" />
        <source>Invalid device index</source>
        <translation>设备索引无效</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="222" />
        <location filename="../src/ch375dev.cpp" line="279" />
        <source>Cannot open CH375 device (index %1)</source>
        <translation>无法打开 CH375 设备（索引 %1）</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="248" />
        <source>Failed to read firmware version (device did not respond)</source>
        <translation>读取固件版本失败（设备无响应）</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="255" />
        <source>Unexpected version response: 0x%1</source>
        <translation>版本响应异常：0x%1</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="297" />
        <source>Failed to send the enter-IAP-mode command</source>
        <translation>发送进入 IAP 模式命令失败</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="332" />
        <source>The firmware version cannot be read on the USB-UART (serial) channel</source>
        <translation>无法通过 USB 转串口（serial）通道读取固件版本</translation>
    </message>
</context>
<context>
    <name>IapWorker</name>
    <message>
        <location filename="../src/iapworker.cpp" line="32" />
        <source>Unknown error</source>
        <translation>未知错误</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="82" />
        <source>Failed to initialize hidapi</source>
        <translation>hidapi 初始化失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="92" />
        <source>Cancelled while waiting for the IAP device</source>
        <translation>已取消：等待 IAP 设备</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="99" />
        <source>Connected to IAP device (VID:0x%1 PID:0x%2)</source>
        <translation>已连接 IAP 设备 (VID:0x%1 PID:0x%2)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="106" />
        <source>Waiting for the IAP device (VID:0x%1 PID:0x%2) ...</source>
        <translation>等待 IAP 设备出现 (VID:0x%1 PID:0x%2) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="113" />
        <source>IAP device not found after waiting %1 seconds</source>
        <translation>未找到 IAP 设备，已等待 %1 秒</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="141" />
        <source>Write cancelled</source>
        <translation>写入被取消</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="155" />
        <source>HID write failed: %1</source>
        <translation>HID 写入失败：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="160" />
        <source>HID write timed out (%1 ms)</source>
        <translation>HID 写入超时（%1 ms）</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="175" />
        <source>Read cancelled</source>
        <translation>读取被取消</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="192" />
        <source>HID read failed: %1</source>
        <translation>HID 读取失败：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="207" />
        <location filename="../src/iapworker.cpp" line="263" />
        <location filename="../src/iapworker.cpp" line="320" />
        <location filename="../src/iapworker.cpp" line="393" />
        <source>Upgrade cancelled</source>
        <translation>已取消升级</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="219" />
        <source>Device is already in IAP mode, skipping the mode switch</source>
        <translation>设备已处于 IAP 模式，跳过模式切换</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="229" />
        <source>No usable CH375 device index, cannot send the switch command</source>
        <translation>没有可用的 CH375 设备索引，无法发送切换命令</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="251" />
        <source>Sending enter-IAP-mode command to device (CH375 index %1) ...</source>
        <translation>向设备（CH375 索引 %1）发送进入 IAP 模式命令 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="255" />
        <source>Failed to enter IAP mode: %1</source>
        <translation>进入 IAP 模式失败：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="259" />
        <source>Command sent, waiting for the device to reset into a HID IAP device ...</source>
        <translation>命令已发送，等待设备复位并切换为 HID IAP 设备 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="277" />
        <source>Erasing FLASH, start address 0x%1</source>
        <translation>擦除 FLASH，起始地址 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="278" />
        <source>Erasing FLASH ...</source>
        <translation>擦除 FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="290" />
        <source>Failed to send the erase command</source>
        <translation>发送擦除命令失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="297" />
        <source>Erase response timed out</source>
        <translation>擦除响应超时</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="302" />
        <source>Erase failed, error code: %1</source>
        <translation>擦除失败，错误码：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="306" />
        <source>Erase complete</source>
        <translation>擦除完成</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="312" />
        <source>Programming FLASH, %1 bytes in total</source>
        <translation>编程 FLASH，共 %1 字节</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="333" />
        <source>Failed to write data, offset %1</source>
        <translation>写入数据失败，偏移 %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="343" />
        <source>Programming response timed out, offset %1</source>
        <translation>编程响应超时，偏移 %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="351" />
        <source>Programming failed, error code %1, offset %2</source>
        <translation>编程失败，错误码 %1，偏移 %2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="313" />
        <location filename="../src/iapworker.cpp" line="368" />
        <source>Programming FLASH ... %1%</source>
        <translation>编程 FLASH ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="378" />
        <source>Programming complete</source>
        <translation>编程完成</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="384" />
        <source>Verifying FLASH ...</source>
        <translation>校验 FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="410" />
        <source>Failed to send the verify command, offset %1</source>
        <translation>发送校验命令失败，偏移 %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="420" />
        <source>Verify response timed out, offset %1</source>
        <translation>校验响应超时，偏移 %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="428" />
        <source>Verification failed, error code %1, address 0x%2</source>
        <translation>校验失败，错误码 %1，地址 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="385" />
        <location filename="../src/iapworker.cpp" line="444" />
        <source>Verifying FLASH ... %1%</source>
        <translation>校验 FLASH ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="212" />
        <source>The device is in use by another program.
Close the program that currently uses the board (for example the logic analyzer software) and refresh.</source>
        <translation>设备正被其他程序占用。
请关闭当前使用该设备的程序（例如逻辑分析仪上位机软件）后刷新重试。</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="243" />
        <source>Opening %1 at the IAP baud rate %2 ...</source>
        <translation>正在以 IAP 波特率 %2 打开 %1 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="247" />
        <source>Sending enter-IAP-mode command over libusb (bus %1, address %2) ...</source>
        <translation>通过 libusb 发送进入 IAP 模式命令（总线 %1，地址 %2）...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="447" />
        <source>Verification succeeded</source>
        <translation>校验成功</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="453" />
        <source>Sending the upgrade-finish command ...</source>
        <translation>发送升级结束命令 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="454" />
        <source>Finishing upgrade ...</source>
        <translation>结束升级 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="462" />
        <source>Failed to send the finish command</source>
        <translation>发送结束命令失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="471" />
        <source>Device confirmed the upgrade</source>
        <translation>设备确认升级完成</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="473" />
        <source>Device has reset (no response is normal)</source>
        <translation>设备已复位（无应答属正常现象）</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="488" />
        <source>Reading firmware file ...</source>
        <translation>读取固件文件 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="491" />
        <source>Failed to load firmware: %1</source>
        <translation>固件加载失败：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="495" />
        <source>Firmware loaded: %1</source>
        <translation>已加载固件：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="496" />
        <source>  Format: %1, size: %2 bytes</source>
        <translation>  格式：%1，大小：%2 字节</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="497" />
        <source>Intel HEX</source>
        <translation>Intel HEX</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="497" />
        <source>BIN</source>
        <translation>BIN</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="499" />
        <source>  Address range: 0x%1 - 0x%2</source>
        <translation>  地址范围：0x%1 - 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="502" />
        <source>  Checksum: 0x%1</source>
        <translation>  校验和：0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="505" />
        <source>Firmware data is empty</source>
        <translation>固件数据为空</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="518" />
        <source>Starting upgrade ...</source>
        <translation>开始升级 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="519" />
        <source>========== Firmware upgrade started %1 ==========</source>
        <translation>========== 开始固件升级 %1 ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="529" />
        <source>Failed to load the firmware file</source>
        <translation>固件文件加载失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="534" />
        <source>Entering IAP mode ...</source>
        <translation>进入 IAP 模式 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="536" />
        <source>Unable to enter IAP mode</source>
        <translation>无法进入 IAP 模式</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="542" />
        <source>Device is now in IAP mode</source>
        <translation>设备已处于 IAP 模式</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="543" />
        <source>The device rebooted into IAP mode</source>
        <translation>设备已重启进入 IAP 模式</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="548" />
        <source>Looking for the IAP device ...</source>
        <translation>查找 IAP 设备 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="550" />
        <source>No device in IAP mode found</source>
        <translation>未找到 IAP 模式的设备</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="553" />
        <source>Connected to the IAP device</source>
        <translation>已连接 IAP 设备</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="558" />
        <source>Failed to erase FLASH</source>
        <translation>擦除 FLASH 失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="566" />
        <source>Failed to program FLASH</source>
        <translation>编程 FLASH 失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="575" />
        <source>Failed to verify FLASH</source>
        <translation>校验 FLASH 失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="582" />
        <source>Failed to finish the upgrade</source>
        <translation>结束升级失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="588" />
        <source>Upgrade complete</source>
        <translation>升级完成</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="589" />
        <source>========== Firmware upgrade succeeded ==========</source>
        <translation>========== 固件升级成功 ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="590" />
        <source>Firmware upgrade succeeded, the device will restart</source>
        <translation>固件升级成功，设备将重新启动</translation>
    </message>
</context>
<context>
    <name>LanguageManager</name>
    <message>
        <location filename="../src/languagemanager.cpp" line="94" />
        <source>Follow System(&amp;A)</source>
        <translation>跟随系统(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="95" />
        <source>English(&amp;E)</source>
        <translation>English(&amp;E)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="96" />
        <source>Simplified Chinese(&amp;C)</source>
        <translation>简体中文(&amp;C)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="124" />
        <source>Simplified Chinese</source>
        <translation>简体中文</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="127" />
        <source>English</source>
        <translation>English</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../src/mainwindow.cpp" line="893" />
        <location filename="../src/mainwindow.cpp" line="912" />
        <location filename="../src/mainwindow.cpp" line="919" />
        <location filename="../src/mainwindow.cpp" line="926" />
        <source>-</source>
        <translation>-</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="469" />
        <source>CH32H417 Logic Analyzer Firmware Upgrade Tool</source>
        <translation>CH32H417 逻辑分析仪固件升级工具</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="84" />
        <source> (in use)</source>
        <translation>（被占用）</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="472" />
        <source>Device</source>
        <translation>设备</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="473" />
        <source>Firmware File</source>
        <translation>固件文件</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="474" />
        <source>IAP Settings</source>
        <translation>IAP 参数</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="477" />
        <source>Device List:</source>
        <translation>设备列表：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="478" />
        <source>Device Status:</source>
        <translation>设备状态：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="479" />
        <source>Firmware Version:</source>
        <translation>固件版本：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="480" />
        <source>File Path:</source>
        <translation>文件路径：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="481" />
        <source>Firmware Info:</source>
        <translation>固件信息：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="484" />
        <source>BIN Base Address: 0x</source>
        <translation>BIN 基地址：0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="486" />
        <source>VID: 0x</source>
        <translation>VID：0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="487" />
        <source>PID: 0x</source>
        <translation>PID：0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="488" />
        <source>Defaults: VID=0x1A86 PID=0xFE17</source>
        <translation>默认值 VID=0x1A86 PID=0xFE17</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="491" />
        <source>Refresh(&amp;R)</source>
        <translation>刷新(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="492" />
        <source>Browse(&amp;B)...</source>
        <translation>浏览(&amp;B)...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="497" />
        <source>Programming start address for .bin files (hexadecimal, e.g. 08006000). On the WeAct Studio Logic Analyzer V2 pick one of the three APP slots: slot 0 = logic analyzer, slot 1 = USB to UART, slot 2 = example.</source>
        <translation>.bin 文件的烧录起始地址（十六进制，如 08006000）。
WeAct Studio Logic Analyzer V2 请选择三个 APP 槽之一：槽 0 = 逻辑分析仪，槽 1 = USB 转串口，槽 2 = 示例。</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="500" />
        <source>Select or drop a .hex / .bin firmware file</source>
        <translation>选择或直接拖入 .hex / .bin 固件文件</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="502" />
        <source>Upgrade Log</source>
        <translation>升级日志</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="503" />
        <source>Reboot into:</source>
        <translation>重启到：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="505" />
        <source>Slot %1</source>
        <translation>槽 %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="507" />
        <source>Make slot %1 (0x%2) the active one and boot it</source>
        <translation>把槽 %1（0x%2）设为当前槽并启动</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="510" />
        <source>Start Upgrade(&amp;S)</source>
        <translation>开始升级(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="511" />
        <location filename="../src/mainwindow.cpp" line="520" />
        <source>Exit(&amp;X)</source>
        <translation>退出(&amp;X)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="518" />
        <source>File(&amp;F)</source>
        <translation>文件(&amp;F)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="519" />
        <source>Open Firmware(&amp;O)...</source>
        <translation>打开固件(&amp;O)...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="521" />
        <source>Tools(&amp;T)</source>
        <translation>工具(&amp;T)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="522" />
        <source>Refresh Devices(&amp;R)</source>
        <translation>刷新设备(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="523" />
        <source>Reboot into Active Slot(&amp;B)</source>
        <translation>重启到当前槽(&amp;B)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="524" />
        <source>Switch APP Slot(&amp;S)</source>
        <translation>切换 APP 槽(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="526" />
        <location filename="../src/mainwindow.cpp" line="728" />
        <source>Slot %1: 0x%2</source>
        <translation>槽 %1：0x%2</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="530" />
        <source>Clear Log(&amp;L)</source>
        <translation>清空日志(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="531" />
        <source>View(&amp;V)</source>
        <translation>视图(&amp;V)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="532" />
        <source>Language(&amp;L)</source>
        <translation>语言(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="533" />
        <source>Help(&amp;H)</source>
        <translation>帮助(&amp;H)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="534" />
        <source>About(&amp;A)</source>
        <translation>关于(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="694" />
        <source>Hexadecimal, e.g. 08006000</source>
        <translation>十六进制，例如 08006000</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="793" />
        <source>(No device found)</source>
        <translation>(未发现设备)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="795" />
        <source>No device found</source>
        <translation>未发现设备</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="895" />
        <source>The firmware version cannot be read on the USB-UART (serial) channel</source>
        <translation>无法通过 USB 转串口（serial）通道读取固件版本</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="901" />
        <source>Read failed</source>
        <translation>读取失败</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="904" />
        <source>Software version: v%1  Hardware version: v%2</source>
        <translation>软件版本：v%1　硬件版本：v%2</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="911" />
        <source>&lt;font color='%1'&gt;Connected (IAP upgrade mode)&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;已连接（IAP 升级模式）&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="918" />
        <source>&lt;font color='%1'&gt;Device in use by another program&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;设备正被其他程序占用&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="925" />
        <source>&lt;font color='%1'&gt;No device found&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;未发现设备&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="964" />
        <source>Leave &amp;IAP</source>
        <translation>退出 IAP(&amp;I)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="965" />
        <source>Reboot into &amp;IAP</source>
        <translation>重启到 IAP(&amp;I)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="969" />
        <source>Reboot the board and run the active APP slot again</source>
        <translation>重启设备并再次运行当前 APP 槽</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="970" />
        <source>Reboot the board into its bootloader (IAP mode)</source>
        <translation>将设备重启进入引导程序（IAP 模式）</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="980" />
        <source>Rebooting the device out of IAP mode ...</source>
        <translation>正在把设备退出 IAP 模式 ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="988" />
        <source>Leaving IAP failed: %1</source>
        <translation>退出 IAP 失败：%1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1038" />
        <source>Not available while an upgrade is running</source>
        <translation>升级进行中不可用</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1041" />
        <source>Needs a board that sits in the IAP bootloader</source>
        <translation>需要设备处于 IAP 引导程序模式</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1051" />
        <location filename="../src/mainwindow.cpp" line="1059" />
        <source>Not Available</source>
        <translation>不可用</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1052" />
        <source>Wait for the running upgrade to finish.</source>
        <translation>请等待当前升级完成。</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1056" />
        <source>This command needs a board that sits in the IAP bootloader, the current device is in application mode.</source>
        <translation>该命令需要设备处于 IAP 引导程序模式，当前设备处于运行模式。</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1060" />
        <source>No CH32H417 device in IAP mode found.
These commands need a board that sits in the bootloader (power-cycle it with the button held).</source>
        <translation>未找到处于 IAP 模式的 CH32H417 设备。
这些命令需要设备处于引导程序中（按住按键重新上电）。</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1072" />
        <source>Rebooting the device into its active slot ...</source>
        <translation>正在把设备重启到当前槽 ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1080" />
        <source>Reboot failed: %1</source>
        <translation>重启失败：%1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="993" />
        <location filename="../src/mainwindow.cpp" line="1085" />
        <source>Reboot request accepted, the device restarts ...</source>
        <translation>重启请求已接受，设备即将重启 ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1114" />
        <source>Switching to APP slot %1 (0x%2) ...</source>
        <translation>正在切换到 APP 槽 %1（0x%2）...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1123" />
        <source>Slot switch failed: %1</source>
        <translation>切换槽位失败：%1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1128" />
        <source>Slot %1 is now active, the device reboots into it ...</source>
        <translation>槽 %1 现已生效，设备将重启进入该槽 ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1197" />
        <source>Select Firmware File</source>
        <translation>选择固件文件</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1199" />
        <source>Firmware Files (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binary Files (*.bin);;All Files (*.*)</source>
        <translation>固件文件 (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;二进制文件 (*.bin);;所有文件 (*.*)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1217" />
        <source>&lt;font color='%1'&gt;No valid firmware file selected&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;尚未选择有效的固件文件&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1231" />
        <source>%1  Size: %2  Address: 0x%3 - 0x%4  Checksum: 0x%5</source>
        <translation>%1　大小：%2　地址：0x%3 - 0x%4　校验和：0x%5</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1232" />
        <source>Intel HEX</source>
        <translation>Intel HEX</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1232" />
        <source>BIN</source>
        <translation>BIN</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1267" />
        <source>Hint</source>
        <translation>提示</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1267" />
        <source>Please select a valid firmware file first.</source>
        <translation>请先选择一个有效的固件文件。</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1273" />
        <source>No Device Found</source>
        <translation>未发现设备</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1274" />
        <source>No CH32H417 device was detected.

If the device is already in IAP mode (for example powered up with the button held down), you can continue;
otherwise please connect the device first.

Continue?</source>
        <translation>当前没有检测到 CH32H417 设备。

如果设备已经处于 IAP 模式（例如按住按键上电），可以继续升级；
否则请先连接设备。

是否继续？</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1286" />
        <source>Firmware Error</source>
        <translation>固件错误</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1319" />
        <source>Preparing ...</source>
        <translation>准备中 ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1328" />
        <source>Target device: serial (COM port %1)</source>
        <translation>目标设备：串口（COM 口 %1）</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1376" />
        <source>Device is in IAP Mode</source>
        <translation>设备处于 IAP 模式</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1394" />
        <location filename="../src/mainwindow.cpp" line="1425" />
        <source>Upgrade Complete</source>
        <translation>升级完成</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="888" />
        <source>&lt;font color='%1'&gt;Connected (application mode, %2 channel)&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;已连接（运行模式，%2 通道）&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1324" />
        <source>Target device: IAP HID (VID:0x%1 PID:0x%2)</source>
        <translation>目标设备：IAP HID (VID:0x%1 PID:0x%2)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1330" />
        <source>Target device: libusb (bus %1, address %2)</source>
        <translation>目标设备：libusb（总线 %1，地址 %2）</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1333" />
        <source>Target device: CH375 #%1</source>
        <translation>目标设备：CH375 #%1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1396" />
        <source>Complete</source>
        <translation>完成</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1397" />
        <source>Firmware upgrade succeeded!
The device will restart and run the new firmware.</source>
        <translation>固件升级成功！
设备将重启并运行新固件。</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1401" />
        <location filename="../src/mainwindow.cpp" line="1428" />
        <source>Upgrade Failed</source>
        <translation>升级失败</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1383" />
        <location filename="../src/mainwindow.cpp" line="1403" />
        <location filename="../src/mainwindow.cpp" line="1408" />
        <source>Please power-cycle the device (disconnect and reconnect the USB cable or the power supply) and run the upgrade again.</source>
        <translation>请给设备重新上电（拔插 USB 线或断开再接通电源），然后重新执行升级。</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="989" />
        <location filename="../src/mainwindow.cpp" line="1081" />
        <location filename="../src/mainwindow.cpp" line="1124" />
        <location filename="../src/mainwindow.cpp" line="1381" />
        <location filename="../src/mainwindow.cpp" line="1386" />
        <location filename="../src/mainwindow.cpp" line="1406" />
        <source>Failed</source>
        <translation>失败</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1432" />
        <source>Ready</source>
        <translation>就绪</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1494" />
        <source>About</source>
        <translation>关于</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1498" />
        <source>&lt;h3&gt;CH32H417 Logic Analyzer&lt;br&gt;Firmware Upgrade Tool&lt;/h3&gt;&lt;p&gt;Version: %1&lt;/p&gt;&lt;p&gt;&lt;b&gt;WeAct Studio&lt;/b&gt;&lt;br&gt;Copyright (C) 2026 WeAct Studio. All rights reserved.&lt;/p&gt;&lt;p&gt;This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.&lt;/p&gt;&lt;p&gt;License: GPL-3.0-or-later&lt;br&gt;&lt;a href='https://www.gnu.org/licenses/gpl-3.0.html'&gt;https://www.gnu.org/licenses/gpl-3.0.html&lt;/a&gt;&lt;/p&gt;&lt;p&gt;Built with Qt %2, statically compiled with MSYS2 (MINGW64).&lt;/p&gt;&lt;p&gt;Upgrade sequence: the enter-IAP command goes out over whichever USB channel the board is on - CH375, libusb / WinUSB, or the COM port of the USB-to-UART firmware. The board then resets into a HID IAP device, followed by erase / program / verify / finish.&lt;/p&gt;&lt;p&gt;A board that already sits in IAP mode can also be rebooted into its active slot, or switched to another APP slot, without downloading anything.&lt;/p&gt;&lt;p&gt;Windows needs one driver for the board: the WCH CH375 driver, or WinUSB when the board is bound to libusb.&lt;/p&gt;</source>
        <translation>&lt;h3&gt;CH32H417 逻辑分析仪&lt;br&gt;固件升级工具&lt;/h3&gt;&lt;p&gt;版本：%1&lt;/p&gt;&lt;p&gt;&lt;b&gt;WeAct Studio&lt;/b&gt;&lt;br&gt;Copyright (C) 2026 WeAct Studio 保留所有权利。&lt;/p&gt;&lt;p&gt;本程序为自由软件：您可以依据自由软件基金会发布的 GNU 通用公共许可证第 3 版或（按您选择的）任何更新版本的条款重新发布和/或修改本程序。发布本程序是希望它能有所用处，但不提供任何担保，甚至不隐含适销性或特定用途适用性的担保。详见 GNU 通用公共许可证。&lt;/p&gt;&lt;p&gt;许可协议：GPL-3.0-or-later&lt;br&gt;&lt;a href='https://www.gnu.org/licenses/gpl-3.0.html'&gt;https://www.gnu.org/licenses/gpl-3.0.html&lt;/a&gt;&lt;/p&gt;&lt;p&gt;基于 Qt %2 开发，使用 MSYS2 (MINGW64) 静态编译。&lt;/p&gt;&lt;p&gt;升级流程：进入 IAP 命令通过板子所在的 USB 通道发出 —— CH375、libusb / WinUSB，或 USB 转串口固件的 COM 口 —— 随后设备复位为 HID IAP 设备，再执行擦除 / 编程 / 校验 / 结束。&lt;/p&gt;&lt;p&gt;已经处于 IAP 模式的板子还可以直接重启回当前槽，或切换到其它 APP 槽，无需下载固件。&lt;/p&gt;&lt;p&gt;Windows 需要为板子安装其中一种驱动：WCH CH375 驱动；若板子绑定到 libusb，则安装 WinUSB。&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1556" />
        <source>Upgrade in Progress</source>
        <translation>正在升级</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1557" />
        <source>An upgrade is running; exiting now may corrupt the device firmware.
Are you sure you want to exit?</source>
        <translation>升级正在进行中，现在退出可能导致设备固件损坏。
确定要退出吗？</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1226" />
        <source>&lt;font color='%1'&gt;%2&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;%2&lt;/font&gt;</translation>
    </message>
</context>
<context>
    <name>SerialDev</name>
    <message>
        <location filename="../src/serialdev.cpp" line="104" />
        <source>Serial port enumeration is only supported on Windows</source>
        <translation>仅支持在 Windows 上枚举串口</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="111" />
        <source>Cannot enumerate the COM ports (error %1)</source>
        <translation>无法枚举 COM 口（错误 %1）</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="233" />
        <source>Serial port access is only supported on Windows</source>
        <translation>仅支持在 Windows 上访问串口</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="245" />
        <source>%1 is open in another program.
Close the program (for example a serial terminal) and retry.</source>
        <translation>%1 已被其他程序打开。
请关闭该程序（例如串口终端）后重试。</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="251" />
        <source>Cannot open %1 (error %2)</source>
        <translation>无法打开 %1（错误 %2）</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="262" />
        <source>Cannot query the settings of %1 (error %2)</source>
        <translation>无法查询 %1 的设置（错误 %2）</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="305" />
        <source>Cannot set the IAP baud rate on %1 (error %2)</source>
        <translation>无法在 %1 上设置 IAP 波特率（错误 %2）</translation>
    </message>
</context>
<context>
    <name>ThemeManager</name>
    <message>
        <location filename="../src/thememanager.cpp" line="166" />
        <source>Follow System(&amp;S)</source>
        <translation>跟随系统(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/thememanager.cpp" line="168" />
        <source>Light(&amp;L)</source>
        <translation>浅色(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/thememanager.cpp" line="171" />
        <source>Dark(&amp;D)</source>
        <translation>深色(&amp;D)</translation>
    </message>
</context>
</TS>