<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="zh_CN">
<context>
    <name>Ch375Dev</name>
    <message>
        <location filename="../src/ch375dev.cpp" line="79" />
        <source>The device is in use by another program.
Close the program that currently uses the board (for example the logic analyzer software) and refresh.</source>
        <translation>设备正被其他程序占用。
请关闭当前使用该设备的程序（例如逻辑分析仪上位机软件）后刷新重试。</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="101" />
        <source>Unable to load CH375DLL64.DLL / CH375DLL.DLL.
Make sure the CH375 driver is installed and that the driver DLL is placed next to this program or in a directory on the system search path.</source>
        <translation>无法加载 CH375DLL64.DLL / CH375DLL.DLL。
请确认已安装 CH375 驱动，且驱动 DLL 位于本程序目录或系统可搜索路径中。</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="210" />
        <location filename="../src/ch375dev.cpp" line="267" />
        <source>Invalid device index</source>
        <translation>设备索引无效</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="221" />
        <location filename="../src/ch375dev.cpp" line="278" />
        <source>Cannot open CH375 device (index %1)</source>
        <translation>无法打开 CH375 设备（索引 %1）</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="247" />
        <source>Failed to read firmware version (device did not respond)</source>
        <translation>读取固件版本失败（设备无响应）</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="254" />
        <source>Unexpected version response: 0x%1</source>
        <translation>版本响应异常：0x%1</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="296" />
        <source>Failed to send the enter-IAP-mode command</source>
        <translation>发送进入 IAP 模式命令失败</translation>
    </message>
</context>
<context>
    <name>IapWorker</name>
    <message>
        <location filename="../src/iapworker.cpp" line="31" />
        <source>Unknown error</source>
        <translation>未知错误</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="81" />
        <source>Failed to initialize hidapi</source>
        <translation>hidapi 初始化失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="91" />
        <source>Cancelled while waiting for the IAP device</source>
        <translation>已取消：等待 IAP 设备</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="98" />
        <source>Connected to IAP device (VID:0x%1 PID:0x%2)</source>
        <translation>已连接 IAP 设备 (VID:0x%1 PID:0x%2)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="105" />
        <source>Waiting for the IAP device (VID:0x%1 PID:0x%2) ...</source>
        <translation>等待 IAP 设备出现 (VID:0x%1 PID:0x%2) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="112" />
        <source>IAP device not found after waiting %1 seconds</source>
        <translation>未找到 IAP 设备，已等待 %1 秒</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="140" />
        <source>Write cancelled</source>
        <translation>写入被取消</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="154" />
        <source>HID write failed: %1</source>
        <translation>HID 写入失败：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="159" />
        <source>HID write timed out (%1 ms)</source>
        <translation>HID 写入超时（%1 ms）</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="174" />
        <source>Read cancelled</source>
        <translation>读取被取消</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="191" />
        <source>HID read failed: %1</source>
        <translation>HID 读取失败：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="206" />
        <location filename="../src/iapworker.cpp" line="256" />
        <location filename="../src/iapworker.cpp" line="313" />
        <location filename="../src/iapworker.cpp" line="386" />
        <source>Upgrade cancelled</source>
        <translation>已取消升级</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="218" />
        <source>Device is already in IAP mode, skipping the mode switch</source>
        <translation>设备已处于 IAP 模式，跳过模式切换</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="227" />
        <source>No usable CH375 device index, cannot send the switch command</source>
        <translation>没有可用的 CH375 设备索引，无法发送切换命令</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="240" />
        <source>Sending enter-IAP-mode command to device (CH375 index %1) ...</source>
        <translation>向设备（CH375 索引 %1）发送进入 IAP 模式命令 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="248" />
        <source>Failed to enter IAP mode: %1</source>
        <translation>进入 IAP 模式失败：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="252" />
        <source>Command sent, waiting for the device to reset into a HID IAP device ...</source>
        <translation>命令已发送，等待设备复位并切换为 HID IAP 设备 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="270" />
        <source>Erasing FLASH, start address 0x%1</source>
        <translation>擦除 FLASH，起始地址 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="271" />
        <source>Erasing FLASH ...</source>
        <translation>擦除 FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="283" />
        <source>Failed to send the erase command</source>
        <translation>发送擦除命令失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="290" />
        <source>Erase response timed out</source>
        <translation>擦除响应超时</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="295" />
        <source>Erase failed, error code: %1</source>
        <translation>擦除失败，错误码：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="299" />
        <source>Erase complete</source>
        <translation>擦除完成</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="305" />
        <source>Programming FLASH, %1 bytes in total</source>
        <translation>编程 FLASH，共 %1 字节</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="326" />
        <source>Failed to write data, offset %1</source>
        <translation>写入数据失败，偏移 %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="336" />
        <source>Programming response timed out, offset %1</source>
        <translation>编程响应超时，偏移 %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="344" />
        <source>Programming failed, error code %1, offset %2</source>
        <translation>编程失败，错误码 %1，偏移 %2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="306" />
        <location filename="../src/iapworker.cpp" line="361" />
        <source>Programming FLASH ... %1%</source>
        <translation>编程 FLASH ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="371" />
        <source>Programming complete</source>
        <translation>编程完成</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="377" />
        <source>Verifying FLASH ...</source>
        <translation>校验 FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="403" />
        <source>Failed to send the verify command, offset %1</source>
        <translation>发送校验命令失败，偏移 %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="413" />
        <source>Verify response timed out, offset %1</source>
        <translation>校验响应超时，偏移 %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="421" />
        <source>Verification failed, error code %1, address 0x%2</source>
        <translation>校验失败，错误码 %1，地址 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="378" />
        <location filename="../src/iapworker.cpp" line="437" />
        <source>Verifying FLASH ... %1%</source>
        <translation>校验 FLASH ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="211" />
        <source>The device is in use by another program.
Close the program that currently uses the board (for example the logic analyzer software) and refresh.</source>
        <translation>设备正被其他程序占用。
请关闭当前使用该设备的程序（例如逻辑分析仪上位机软件）后刷新重试。</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="237" />
        <source>Sending enter-IAP-mode command over libusb (bus %1, address %2) ...</source>
        <translation>通过 libusb 发送进入 IAP 模式命令（总线 %1，地址 %2）...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="440" />
        <source>Verification succeeded</source>
        <translation>校验成功</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="446" />
        <source>Sending the upgrade-finish command ...</source>
        <translation>发送升级结束命令 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="447" />
        <source>Finishing upgrade ...</source>
        <translation>结束升级 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="455" />
        <source>Failed to send the finish command</source>
        <translation>发送结束命令失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="464" />
        <source>Device confirmed the upgrade</source>
        <translation>设备确认升级完成</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="466" />
        <source>Device has reset (no response is normal)</source>
        <translation>设备已复位（无应答属正常现象）</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="481" />
        <source>Reading firmware file ...</source>
        <translation>读取固件文件 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="484" />
        <source>Failed to load firmware: %1</source>
        <translation>固件加载失败：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="488" />
        <source>Firmware loaded: %1</source>
        <translation>已加载固件：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="489" />
        <source>  Format: %1, size: %2 bytes</source>
        <translation>  格式：%1，大小：%2 字节</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="490" />
        <source>Intel HEX</source>
        <translation>Intel HEX</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="490" />
        <source>BIN</source>
        <translation>BIN</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="492" />
        <source>  Address range: 0x%1 - 0x%2</source>
        <translation>  地址范围：0x%1 - 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="495" />
        <source>  Checksum: 0x%1</source>
        <translation>  校验和：0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="498" />
        <source>Firmware data is empty</source>
        <translation>固件数据为空</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="511" />
        <source>Starting upgrade ...</source>
        <translation>开始升级 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="512" />
        <source>========== Firmware upgrade started %1 ==========</source>
        <translation>========== 开始固件升级 %1 ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="519" />
        <source>Failed to load the firmware file</source>
        <translation>固件文件加载失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="524" />
        <source>Entering IAP mode ...</source>
        <translation>进入 IAP 模式 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="526" />
        <source>Unable to enter IAP mode</source>
        <translation>无法进入 IAP 模式</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="531" />
        <source>Looking for the IAP device ...</source>
        <translation>查找 IAP 设备 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="533" />
        <source>No device in IAP mode found</source>
        <translation>未找到 IAP 模式的设备</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="536" />
        <source>Connected to the IAP device</source>
        <translation>已连接 IAP 设备</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="541" />
        <source>Failed to erase FLASH</source>
        <translation>擦除 FLASH 失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="549" />
        <source>Failed to program FLASH</source>
        <translation>编程 FLASH 失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="558" />
        <source>Failed to verify FLASH</source>
        <translation>校验 FLASH 失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="565" />
        <source>Failed to finish the upgrade</source>
        <translation>结束升级失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="571" />
        <source>Upgrade complete</source>
        <translation>升级完成</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="572" />
        <source>========== Firmware upgrade succeeded ==========</source>
        <translation>========== 固件升级成功 ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="573" />
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
        <location filename="../src/mainwindow.cpp" line="730" />
        <location filename="../src/mainwindow.cpp" line="737" />
        <location filename="../src/mainwindow.cpp" line="744" />
        <source>-</source>
        <translation>-</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="407" />
        <source>CH32H417 Logic Analyzer Firmware Upgrade Tool</source>
        <translation>CH32H417 逻辑分析仪固件升级工具</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="83" />
        <source> (in use)</source>
        <translation>（被占用）</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="410" />
        <source>Device</source>
        <translation>设备</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="411" />
        <source>Firmware File</source>
        <translation>固件文件</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="412" />
        <source>IAP Settings</source>
        <translation>IAP 参数</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="415" />
        <source>Device List:</source>
        <translation>设备列表：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="416" />
        <source>Device Status:</source>
        <translation>设备状态：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="417" />
        <source>Firmware Version:</source>
        <translation>固件版本：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="418" />
        <source>File Path:</source>
        <translation>文件路径：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="419" />
        <source>Firmware Info:</source>
        <translation>固件信息：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="422" />
        <source>BIN Base Address: 0x</source>
        <translation>BIN 基地址：0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="424" />
        <source>VID: 0x</source>
        <translation>VID：0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="425" />
        <source>PID: 0x</source>
        <translation>PID：0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="426" />
        <source>Defaults: VID=0x1A86 PID=0xFE17</source>
        <translation>默认值 VID=0x1A86 PID=0xFE17</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="429" />
        <source>Refresh(&amp;R)</source>
        <translation>刷新(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="430" />
        <source>Browse(&amp;B)...</source>
        <translation>浏览(&amp;B)...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="431" />
        <source>Programming start address for .bin files (hexadecimal, e.g. 08006000)</source>
        <translation>.bin 文件的烧录起始地址（十六进制，例如 08006000）</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="432" />
        <source>Select or drop a .hex / .bin firmware file</source>
        <translation>选择或直接拖入 .hex / .bin 固件文件</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="434" />
        <source>Upgrade Log</source>
        <translation>升级日志</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="435" />
        <source>Start Upgrade(&amp;S)</source>
        <translation>开始升级(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="436" />
        <location filename="../src/mainwindow.cpp" line="445" />
        <source>Exit(&amp;X)</source>
        <translation>退出(&amp;X)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="443" />
        <source>File(&amp;F)</source>
        <translation>文件(&amp;F)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="444" />
        <source>Open Firmware(&amp;O)...</source>
        <translation>打开固件(&amp;O)...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="446" />
        <source>Tools(&amp;T)</source>
        <translation>工具(&amp;T)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="447" />
        <source>Refresh Devices(&amp;R)</source>
        <translation>刷新设备(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="448" />
        <source>Clear Log(&amp;L)</source>
        <translation>清空日志(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="449" />
        <source>View(&amp;V)</source>
        <translation>视图(&amp;V)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="450" />
        <source>Language(&amp;L)</source>
        <translation>语言(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="451" />
        <source>Help(&amp;H)</source>
        <translation>帮助(&amp;H)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="452" />
        <source>About(&amp;A)</source>
        <translation>关于(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="577" />
        <source>Hexadecimal, e.g. 08006000</source>
        <translation>十六进制，例如 08006000</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="626" />
        <source>(No device found)</source>
        <translation>(未发现设备)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="628" />
        <source>No device found</source>
        <translation>未发现设备</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="720" />
        <source>Read failed</source>
        <translation>读取失败</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="723" />
        <source>Software version: v%1  Hardware version: v%2</source>
        <translation>软件版本：v%1　硬件版本：v%2</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="729" />
        <source>&lt;font color='%1'&gt;Connected (IAP upgrade mode)&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;已连接（IAP 升级模式）&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="736" />
        <source>&lt;font color='%1'&gt;Device in use by another program&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;设备正被其他程序占用&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="743" />
        <source>&lt;font color='%1'&gt;No device found&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;未发现设备&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="809" />
        <source>Select Firmware File</source>
        <translation>选择固件文件</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="811" />
        <source>Firmware Files (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binary Files (*.bin);;All Files (*.*)</source>
        <translation>固件文件 (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;二进制文件 (*.bin);;所有文件 (*.*)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="829" />
        <source>&lt;font color='%1'&gt;No valid firmware file selected&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;尚未选择有效的固件文件&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="843" />
        <source>%1  Size: %2  Address: 0x%3 - 0x%4  Checksum: 0x%5</source>
        <translation>%1　大小：%2　地址：0x%3 - 0x%4　校验和：0x%5</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="844" />
        <source>Intel HEX</source>
        <translation>Intel HEX</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="844" />
        <source>BIN</source>
        <translation>BIN</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="877" />
        <source>Hint</source>
        <translation>提示</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="877" />
        <source>Please select a valid firmware file first.</source>
        <translation>请先选择一个有效的固件文件。</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="883" />
        <source>No Device Found</source>
        <translation>未发现设备</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="884" />
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
        <location filename="../src/mainwindow.cpp" line="896" />
        <source>Firmware Error</source>
        <translation>固件错误</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="916" />
        <source>Preparing ...</source>
        <translation>准备中 ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1069" />
        <source>&lt;h3&gt;CH32H417 Logic Analyzer&lt;br&gt;Firmware Upgrade Tool&lt;/h3&gt;&lt;p&gt;Version: %1&lt;/p&gt;&lt;p&gt;&lt;b&gt;WeAct Studio&lt;/b&gt;&lt;br&gt;Copyright (C) 2026 WeAct Studio. All rights reserved.&lt;/p&gt;&lt;p&gt;This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.&lt;/p&gt;&lt;p&gt;License: GPL-3.0-or-later&lt;br&gt;&lt;a href='https://www.gnu.org/licenses/gpl-3.0.html'&gt;https://www.gnu.org/licenses/gpl-3.0.html&lt;/a&gt;&lt;/p&gt;&lt;p&gt;Built with Qt %2, statically compiled with MSYS2 (MINGW64).&lt;/p&gt;&lt;p&gt;Upgrade sequence: the enter-IAP command is sent over the CH375 channel, the device resets into a HID IAP device, then erase / program / verify / finish.&lt;/p&gt;&lt;p&gt;The CH375 driver must be installed.&lt;/p&gt;</source>
        <translation>&lt;h3&gt;CH32H417 逻辑分析仪&lt;br&gt;固件升级工具&lt;/h3&gt;&lt;p&gt;版本：%1&lt;/p&gt;&lt;p&gt;&lt;b&gt;WeAct Studio&lt;/b&gt;&lt;br&gt;Copyright (C) 2026 WeAct Studio 保留所有权利。&lt;/p&gt;&lt;p&gt;本程序为自由软件：您可以依据自由软件基金会发布的 GNU 通用公共许可证第 3 版或（按您选择的）任何更新版本的条款重新发布和/或修改本程序。发布本程序是希望它能有所用处，但不提供任何担保，甚至不隐含适销性或特定用途适用性的担保。详见 GNU 通用公共许可证。&lt;/p&gt;&lt;p&gt;许可协议：GPL-3.0-or-later&lt;br&gt;&lt;a href='https://www.gnu.org/licenses/gpl-3.0.html'&gt;https://www.gnu.org/licenses/gpl-3.0.html&lt;/a&gt;&lt;/p&gt;&lt;p&gt;基于 Qt %2 开发，使用 MSYS2 (MINGW64) 静态编译。&lt;/p&gt;&lt;p&gt;升级流程：CH375 通道发送进入 IAP 命令 → 设备复位为 HID IAP 设备 → 擦除 / 编程 / 校验 / 结束。&lt;/p&gt;&lt;p&gt;需要安装 CH375 驱动。&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="965" />
        <location filename="../src/mainwindow.cpp" line="996" />
        <source>Upgrade Complete</source>
        <translation>升级完成</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="713" />
        <source>&lt;font color='%1'&gt;Connected (application mode, %2 channel)&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;已连接（运行模式，%2 通道）&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="920" />
        <source>Target device: IAP HID (VID:0x%1 PID:0x%2)</source>
        <translation>目标设备：IAP HID (VID:0x%1 PID:0x%2)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="924" />
        <source>Target device: libusb (bus %1, address %2)</source>
        <translation>目标设备：libusb（总线 %1，地址 %2）</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="927" />
        <source>Target device: CH375 #%1</source>
        <translation>目标设备：CH375 #%1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="967" />
        <source>Complete</source>
        <translation>完成</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="968" />
        <source>Firmware upgrade succeeded!
The device will restart and run the new firmware.</source>
        <translation>固件升级成功！
设备将重启并运行新固件。</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="972" />
        <location filename="../src/mainwindow.cpp" line="999" />
        <source>Upgrade Failed</source>
        <translation>升级失败</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="974" />
        <location filename="../src/mainwindow.cpp" line="979" />
        <source>Please power-cycle the device (disconnect and reconnect the USB cable or the power supply) and run the upgrade again.</source>
        <translation>请给设备重新上电（拔插 USB 线或断开再接通电源），然后重新执行升级。</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="977" />
        <source>Failed</source>
        <translation>失败</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1003" />
        <source>Ready</source>
        <translation>就绪</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1065" />
        <source>About</source>
        <translation>关于</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1122" />
        <source>Upgrade in Progress</source>
        <translation>正在升级</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1123" />
        <source>An upgrade is running; exiting now may corrupt the device firmware.
Are you sure you want to exit?</source>
        <translation>升级正在进行中，现在退出可能导致设备固件损坏。
确定要退出吗？</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="838" />
        <source>&lt;font color='%1'&gt;%2&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;%2&lt;/font&gt;</translation>
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