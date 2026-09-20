<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="en_US">
<context>
    <name>Ch375Dev</name>
    <message>
        <location filename="../src/ch375dev.cpp" line="72" />
        <source>无法加载 CH375DLL64.DLL / CH375DLL.DLL。
请确认已安装 CH375 驱动，且驱动 DLL 位于本程序目录或系统可搜索路径中。</source>
        <translation>Unable to load CH375DLL64.DLL / CH375DLL.DLL.
Please make sure the CH375 driver is installed and the driver DLL is in the application folder or another directory searched by the system.</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="168" />
        <location filename="../src/ch375dev.cpp" line="225" />
        <source>设备索引无效</source>
        <translation>Invalid device index</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="179" />
        <location filename="../src/ch375dev.cpp" line="236" />
        <source>无法打开 CH375 设备 (索引 %1)</source>
        <translation>Cannot open CH375 device (index %1)</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="205" />
        <source>读取固件版本失败（设备无响应）</source>
        <translation>Failed to read firmware version (device not responding)</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="212" />
        <source>版本响应异常：0x%1</source>
        <translation>Unexpected version response: 0x%1</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="254" />
        <source>发送进入 IAP 模式命令失败</source>
        <translation>Failed to send the enter-IAP-mode command</translation>
    </message>
</context>
<context>
    <name>FirmwareImage</name>
    <message>
        <location filename="../src/firmwareimage.cpp" line="98" />
        <source>HEX 校验和错误：第 %1 行 (0x%2)</source>
        <translation>HEX checksum error: line %1 (0x%2)</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="167" />
        <source>HEX 地址范围异常：0x%1 - 0x%2</source>
        <translation>HEX address range abnormal: 0x%1 - 0x%2</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="251" />
        <source>%1 KB (%2 bytes)</source>
        <translation>%1 KB (%2 bytes)</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="254" />
        <source>%1 MB (%2 bytes)</source>
        <translation>%1 MB (%2 bytes)</translation>
    </message>
</context>
<context>
    <name>IapWorker</name>
    <message>
        <location filename="../src/iapworker.cpp" line="30" />
        <source>未知错误</source>
        <translation>Unknown error</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="80" />
        <source>hidapi 初始化失败</source>
        <translation>hidapi initialization failed</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="90" />
        <source>已取消：等待 IAP 设备</source>
        <translation>Cancelled: waiting for IAP device</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="97" />
        <source>已连接 IAP 设备 (VID:0x%1 PID:0x%2)</source>
        <translation>Connected to IAP device (VID:0x%1 PID:0x%2)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="104" />
        <source>等待 IAP 设备出现 (VID:0x%1 PID:0x%2) ...</source>
        <translation>Waiting for IAP device (VID:0x%1 PID:0x%2) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="111" />
        <source>未找到 IAP 设备，已等待 %1 秒</source>
        <translation>IAP device not found after waiting %1 seconds</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="139" />
        <source>写入被取消</source>
        <translation>Write cancelled</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="153" />
        <source>HID 写入失败：%1</source>
        <translation>HID write failed: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="158" />
        <source>HID 写入超时 (%1 ms)</source>
        <translation>HID write timed out (%1 ms)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="173" />
        <source>读取被取消</source>
        <translation>Read cancelled</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="190" />
        <source>HID 读取失败：%1</source>
        <translation>HID read failed: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="205" />
        <location filename="../src/iapworker.cpp" line="231" />
        <location filename="../src/iapworker.cpp" line="288" />
        <location filename="../src/iapworker.cpp" line="355" />
        <source>已取消升级</source>
        <translation>Upgrade cancelled</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="210" />
        <source>设备已处于 IAP 模式，跳过模式切换</source>
        <translation>Device already in IAP mode, skipping mode switch</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="215" />
        <source>没有可用的 CH375 设备索引，无法发送切换命令</source>
        <translation>No usable CH375 device index, cannot send the switch command</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="219" />
        <source>向设备 (CH375 索引 %1) 发送进入 IAP 模式命令 ...</source>
        <translation>Sending enter-IAP-mode command to device (CH375 index %1) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="223" />
        <source>进入 IAP 模式失败：%1</source>
        <translation>Failed to enter IAP mode: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="227" />
        <source>命令已发送，等待设备复位并切换为 HID IAP 设备 ...</source>
        <translation>Command sent, waiting for the device to reset and re-enumerate as an HID IAP device ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="245" />
        <source>擦除 FLASH，起始地址 0x%1</source>
        <translation>Erasing FLASH from address 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="246" />
        <source>擦除 FLASH ...</source>
        <translation>Erasing FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="258" />
        <source>发送擦除命令失败</source>
        <translation>Failed to send the erase command</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="265" />
        <source>擦除响应超时</source>
        <translation>Erase response timed out</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="270" />
        <source>擦除失败，错误码：%1</source>
        <translation>Erase failed, error code: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="274" />
        <source>擦除完成</source>
        <translation>Erase completed</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="280" />
        <source>编程 FLASH，共 %1 字节</source>
        <translation>Programming FLASH, %1 bytes in total</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="281" />
        <source>编程 FLASH ...</source>
        <translation>Programming FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="301" />
        <source>写入数据失败，偏移 %1</source>
        <translation>Failed to write data at offset %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="311" />
        <source>编程响应超时，偏移 %1</source>
        <translation>Programming response timed out at offset %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="319" />
        <source>编程失败，错误码 %1，偏移 %2</source>
        <translation>Programming failed, error code %1, offset %2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="330" />
        <source>编程 FLASH ... %1%</source>
        <translation>Programming FLASH ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="340" />
        <source>编程完成</source>
        <translation>Programming completed</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="346" />
        <location filename="../src/iapworker.cpp" line="347" />
        <source>校验 FLASH ...</source>
        <translation>Verifying FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="372" />
        <source>发送校验命令失败，偏移 %1</source>
        <translation>Failed to send verify command at offset %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="382" />
        <source>校验响应超时，偏移 %1</source>
        <translation>Verify response timed out at offset %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="390" />
        <source>校验失败，错误码 %1，地址 0x%2</source>
        <translation>Verification failed, error code %1, address 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="404" />
        <source>校验 FLASH ... %1%</source>
        <translation>Verifying FLASH ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="407" />
        <source>校验成功</source>
        <translation>Verification succeeded</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="413" />
        <source>发送升级结束命令 ...</source>
        <translation>Sending finish-upgrade command ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="414" />
        <source>结束升级 ...</source>
        <translation>Finishing upgrade ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="422" />
        <source>发送结束命令失败</source>
        <translation>Failed to send the finish command</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="431" />
        <source>设备确认升级完成</source>
        <translation>Device confirmed the upgrade</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="433" />
        <source>设备已复位（无应答属正常现象）</source>
        <translation>Device has reset (no response is normal)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="448" />
        <source>读取固件文件 ...</source>
        <translation>Reading firmware file ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="451" />
        <source>固件加载失败：%1</source>
        <translation>Failed to load firmware: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="455" />
        <source>已加载固件：%1</source>
        <translation>Firmware loaded: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="456" />
        <source>  格式：%1，大小：%2 字节</source>
        <translation>  Format: %1, size: %2 bytes</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="457" />
        <source>Intel HEX</source>
        <translation>Intel HEX</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="457" />
        <source>BIN</source>
        <translation>BIN</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="459" />
        <source>  地址范围：0x%1 - 0x%2</source>
        <translation>  Address range: 0x%1 - 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="462" />
        <source>  校验和：0x%1</source>
        <translation>  Checksum: 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="465" />
        <source>固件数据为空</source>
        <translation>Firmware data is empty</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="478" />
        <source>开始升级 ...</source>
        <translation>Starting upgrade ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="479" />
        <source>========== 开始固件升级 %1 ==========</source>
        <translation>========== Starting firmware upgrade %1 ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="486" />
        <source>固件文件加载失败</source>
        <translation>Failed to load the firmware file</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="491" />
        <source>进入 IAP 模式 ...</source>
        <translation>Entering IAP mode ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="493" />
        <source>无法进入 IAP 模式</source>
        <translation>Unable to enter IAP mode</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="498" />
        <source>查找 IAP 设备 ...</source>
        <translation>Searching for IAP device ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="500" />
        <source>未找到 IAP 模式的设备</source>
        <translation>No device in IAP mode was found</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="503" />
        <source>已连接 IAP 设备</source>
        <translation>Connected to IAP device</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="508" />
        <source>擦除 FLASH 失败</source>
        <translation>Failed to erase FLASH</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="516" />
        <source>编程 FLASH 失败</source>
        <translation>Failed to program FLASH</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="525" />
        <source>校验 FLASH 失败</source>
        <translation>Failed to verify FLASH</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="532" />
        <source>结束升级失败</source>
        <translation>Failed to finish the upgrade</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="538" />
        <source>升级完成</source>
        <translation>Upgrade completed</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="539" />
        <source>========== 固件升级成功 ==========</source>
        <translation>========== Firmware upgrade succeeded ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="540" />
        <source>固件升级成功，设备将重新启动</source>
        <translation>Firmware upgrade succeeded, the device will restart</translation>
    </message>
</context>
<context>
    <name>LanguageManager</name>
    <message>
        <location filename="../src/languagemanager.cpp" line="93" />
        <source>跟随系统(&amp;A)</source>
        <translation>Follow System(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="94" />
        <source>English(&amp;E)</source>
        <translation>English(&amp;E)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="95" />
        <source>简体中文(&amp;C)</source>
        <translation>Simplified Chinese(&amp;C)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="123" />
        <source>简体中文</source>
        <translation>Simplified Chinese</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="126" />
        <source>English</source>
        <translation>English</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../src/mainwindow.cpp" line="416" />
        <source>CH32H417 逻辑分析仪固件升级工具</source>
        <translation>CH32H417 Logic Analyzer Firmware Upgrade Tool</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="419" />
        <source>设备</source>
        <translation>Device</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="420" />
        <source>固件文件</source>
        <translation>Firmware File</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="421" />
        <source>IAP 参数</source>
        <translation>IAP Parameters</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="424" />
        <source>设备列表：</source>
        <translation>Device list:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="425" />
        <source>设备状态：</source>
        <translation>Device status:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="426" />
        <source>固件版本：</source>
        <translation>Firmware version:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="427" />
        <source>文件路径：</source>
        <translation>File path:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="428" />
        <source>固件信息：</source>
        <translation>Firmware info:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="432" />
        <source>VID：0x</source>
        <translation>VID: 0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="433" />
        <source>PID：0x</source>
        <translation>PID: 0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="434" />
        <source>默认值 VID=0x1A86 PID=0xFE17</source>
        <translation>Default VID=0x1A86 PID=0xFE17</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="437" />
        <source>刷新(&amp;R)</source>
        <translation>&amp;Refresh</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="438" />
        <source>浏览(&amp;B)...</source>
        <translation>&amp;Browse...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="440" />
        <source>选择或直接拖入 .hex / .bin 固件文件</source>
        <translation>Select or drag and drop a .hex / .bin firmware file</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="442" />
        <source>升级日志：</source>
        <translation>Upgrade log:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="443" />
        <source>开始升级(&amp;S)</source>
        <translation>&amp;Start Upgrade</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="444" />
        <source>取消(&amp;C)</source>
        <translation>&amp;Cancel</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="445" />
        <location filename="../src/mainwindow.cpp" line="453" />
        <source>退出(&amp;X)</source>
        <translation>E&amp;xit</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="451" />
        <source>文件(&amp;F)</source>
        <translation>&amp;File</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="452" />
        <source>打开固件(&amp;O)...</source>
        <translation>&amp;Open Firmware...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="454" />
        <source>工具(&amp;T)</source>
        <translation>&amp;Tools</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="455" />
        <source>刷新设备(&amp;R)</source>
        <translation>&amp;Refresh Devices</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="456" />
        <source>清空日志(&amp;L)</source>
        <translation>Clear &amp;Log</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="458" />
        <source>语言(&amp;L)</source>
        <translation>&amp;Language</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="459" />
        <source>帮助(&amp;H)</source>
        <translation>&amp;Help</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="460" />
        <source>关于(&amp;A)</source>
        <translation>&amp;About</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="584" />
        <source>十六进制，例如 08006000</source>
        <translation>Hexadecimal, e.g. 08006000</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="632" />
        <source>(未发现设备)</source>
        <translation>(No device found)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="710" />
        <source>读取失败</source>
        <translation>Failed to read</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="720" />
        <location filename="../src/mainwindow.cpp" line="727" />
        <source>-</source>
        <translation>-</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="791" />
        <source>选择固件文件</source>
        <translation>Select Firmware File</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="793" />
        <source>固件文件 (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;二进制文件 (*.bin);;所有文件 (*.*)</source>
        <translation>Firmware Files (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binary Files (*.bin);;All Files (*.*)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="825" />
        <source>%1　大小：%2　地址：0x%3 - 0x%4　校验和：0x%5</source>
        <translation>%1  Size: %2  Address: 0x%3 - 0x%4  Checksum: 0x%5</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="826" />
        <source>Intel HEX</source>
        <translation>Intel HEX</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="826" />
        <source>BIN</source>
        <translation>BIN</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="859" />
        <source>提示</source>
        <translation>Notice</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="859" />
        <source>请先选择一个有效的固件文件。</source>
        <translation>Please select a valid firmware file first.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="634" />
        <location filename="../src/mainwindow.cpp" line="865" />
        <source>未发现设备</source>
        <translation>No Device Found</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="430" />
        <source>BIN 基地址：0x</source>
        <translation>BIN base address: 0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="439" />
        <source>.bin 文件的烧录起始地址（十六进制，例如 08006000）</source>
        <translation>Programming start address for .bin files (hexadecimal, e.g. 08006000)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="705" />
        <source>&lt;font color='%1'&gt;已连接（运行模式，CH375 通道）&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Connected (run mode, CH375 channel)&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="713" />
        <source>软件版本：v%1　硬件版本：v%2</source>
        <translation>Software version: v%1    Hardware version: v%2</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="719" />
        <source>&lt;font color='%1'&gt;已连接（IAP 升级模式，HID 通道）&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Connected (IAP upgrade mode, HID channel)&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="726" />
        <source>&lt;font color='%1'&gt;未发现设备&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;No device found&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="811" />
        <source>&lt;font color='%1'&gt;尚未选择有效的固件文件&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;No valid firmware file selected&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="820" />
        <source>&lt;font color='%1'&gt;%2&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;%2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="866" />
        <source>当前没有检测到 CH32H417 设备。

如果设备已经处于 IAP 模式（例如按住按键上电），可以继续升级；
否则请先连接设备。

是否继续？</source>
        <translation>No CH32H417 device was detected.

If the device is already in IAP mode (for example, powered on with the button held), you can continue;
otherwise please connect the device first.

Continue?</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="877" />
        <source>固件错误</source>
        <translation>Firmware Error</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="893" />
        <source>准备中 ...</source>
        <translation>Preparing ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="896" />
        <source>目标设备：%1</source>
        <translation>Target device: %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="922" />
        <source>正在请求取消 ...</source>
        <translation>Requesting cancellation ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="947" />
        <location filename="../src/mainwindow.cpp" line="969" />
        <source>升级完成</source>
        <translation>Upgrade completed</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="949" />
        <source>完成</source>
        <translation>Completed</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="950" />
        <source>固件升级成功！
设备将重启并运行新固件。</source>
        <translation>Firmware upgrade succeeded!
The device will restart and run the new firmware.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="953" />
        <location filename="../src/mainwindow.cpp" line="972" />
        <source>升级失败</source>
        <translation>Upgrade failed</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="955" />
        <source>失败</source>
        <translation>Failed</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="976" />
        <source>就绪</source>
        <translation>Ready</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1038" />
        <source>关于</source>
        <translation>About</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1041" />
        <source>&lt;h3&gt;CH32H417 逻辑分析仪固件升级工具&lt;/h3&gt;&lt;p&gt;版本：%1&lt;/p&gt;&lt;p&gt;基于 Qt 6 开发，使用 MSYS2 (MINGW64) 静态编译。&lt;/p&gt;&lt;p&gt;升级流程：CH375 通道发送进入 IAP 命令 → 设备复位为 HID IAP 设备 → 擦除 / 编程 / 校验 / 结束。&lt;/p&gt;&lt;p&gt;需要安装 CH375 驱动。&lt;/p&gt;</source>
        <translation>&lt;h3&gt;CH32H417 Logic Analyzer Firmware Upgrade Tool&lt;/h3&gt;&lt;p&gt;Version: %1&lt;/p&gt;&lt;p&gt;Built with Qt 6, statically compiled with MSYS2 (MINGW64).&lt;/p&gt;&lt;p&gt;Upgrade flow: send the enter-IAP command over the CH375 channel → the device resets and re-enumerates as an HID IAP device → erase / program / verify / finish.&lt;/p&gt;&lt;p&gt;The CH375 driver must be installed.&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1079" />
        <source>正在升级</source>
        <translation>Upgrading</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1080" />
        <source>升级正在进行中，现在退出可能导致设备固件损坏。
确定要退出吗？</source>
        <translation>An upgrade is in progress. Exiting now may corrupt the device firmware.
Are you sure you want to quit?</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="457" />
        <source>视图(&amp;V)</source>
        <translation>View(&amp;V)</translation>
    </message>
</context>
<context>
    <name>ThemeManager</name>
    <message>
        <location filename="../src/thememanager.cpp" line="165" />
        <source>跟随系统(&amp;S)</source>
        <translation>Follow System(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/thememanager.cpp" line="167" />
        <source>浅色(&amp;L)</source>
        <translation>Light(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/thememanager.cpp" line="170" />
        <source>深色(&amp;D)</source>
        <translation>Dark(&amp;D)</translation>
    </message>
</context>
</TS>