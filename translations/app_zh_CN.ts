<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="zh_CN">
<context>
    <name>Ch375Dev</name>
    <message>
        <location filename="../src/ch375dev.cpp" line="72" />
        <source>无法加载 CH375DLL64.DLL / CH375DLL.DLL。
请确认已安装 CH375 驱动，且驱动 DLL 位于本程序目录或系统可搜索路径中。</source>
        <translation>无法加载 CH375DLL64.DLL / CH375DLL.DLL。
请确认已安装 CH375 驱动，且驱动 DLL 位于本程序目录或系统可搜索路径中。</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="168" />
        <location filename="../src/ch375dev.cpp" line="225" />
        <source>设备索引无效</source>
        <translation>设备索引无效</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="179" />
        <location filename="../src/ch375dev.cpp" line="236" />
        <source>无法打开 CH375 设备 (索引 %1)</source>
        <translation>无法打开 CH375 设备 (索引 %1)</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="205" />
        <source>读取固件版本失败（设备无响应）</source>
        <translation>读取固件版本失败（设备无响应）</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="212" />
        <source>版本响应异常：0x%1</source>
        <translation>版本响应异常：0x%1</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="254" />
        <source>发送进入 IAP 模式命令失败</source>
        <translation>发送进入 IAP 模式命令失败</translation>
    </message>
</context>
<context>
    <name>FirmwareImage</name>
    <message>
        <location filename="../src/firmwareimage.cpp" line="98" />
        <source>HEX 校验和错误：第 %1 行 (0x%2)</source>
        <translation>HEX 校验和错误：第 %1 行 (0x%2)</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="167" />
        <source>HEX 地址范围异常：0x%1 - 0x%2</source>
        <translation>HEX 地址范围异常：0x%1 - 0x%2</translation>
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
        <translation>未知错误</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="80" />
        <source>hidapi 初始化失败</source>
        <translation>hidapi 初始化失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="90" />
        <source>已取消：等待 IAP 设备</source>
        <translation>已取消：等待 IAP 设备</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="97" />
        <source>已连接 IAP 设备 (VID:0x%1 PID:0x%2)</source>
        <translation>已连接 IAP 设备 (VID:0x%1 PID:0x%2)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="104" />
        <source>等待 IAP 设备出现 (VID:0x%1 PID:0x%2) ...</source>
        <translation>等待 IAP 设备出现 (VID:0x%1 PID:0x%2) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="111" />
        <source>未找到 IAP 设备，已等待 %1 秒</source>
        <translation>未找到 IAP 设备，已等待 %1 秒</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="139" />
        <source>写入被取消</source>
        <translation>写入被取消</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="153" />
        <source>HID 写入失败：%1</source>
        <translation>HID 写入失败：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="158" />
        <source>HID 写入超时 (%1 ms)</source>
        <translation>HID 写入超时 (%1 ms)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="173" />
        <source>读取被取消</source>
        <translation>读取被取消</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="190" />
        <source>HID 读取失败：%1</source>
        <translation>HID 读取失败：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="205" />
        <location filename="../src/iapworker.cpp" line="231" />
        <location filename="../src/iapworker.cpp" line="288" />
        <location filename="../src/iapworker.cpp" line="355" />
        <source>已取消升级</source>
        <translation>已取消升级</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="210" />
        <source>设备已处于 IAP 模式，跳过模式切换</source>
        <translation>设备已处于 IAP 模式，跳过模式切换</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="215" />
        <source>没有可用的 CH375 设备索引，无法发送切换命令</source>
        <translation>没有可用的 CH375 设备索引，无法发送切换命令</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="219" />
        <source>向设备 (CH375 索引 %1) 发送进入 IAP 模式命令 ...</source>
        <translation>向设备 (CH375 索引 %1) 发送进入 IAP 模式命令 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="223" />
        <source>进入 IAP 模式失败：%1</source>
        <translation>进入 IAP 模式失败：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="227" />
        <source>命令已发送，等待设备复位并切换为 HID IAP 设备 ...</source>
        <translation>命令已发送，等待设备复位并切换为 HID IAP 设备 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="245" />
        <source>擦除 FLASH，起始地址 0x%1</source>
        <translation>擦除 FLASH，起始地址 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="246" />
        <source>擦除 FLASH ...</source>
        <translation>擦除 FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="258" />
        <source>发送擦除命令失败</source>
        <translation>发送擦除命令失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="265" />
        <source>擦除响应超时</source>
        <translation>擦除响应超时</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="270" />
        <source>擦除失败，错误码：%1</source>
        <translation>擦除失败，错误码：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="274" />
        <source>擦除完成</source>
        <translation>擦除完成</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="280" />
        <source>编程 FLASH，共 %1 字节</source>
        <translation>编程 FLASH，共 %1 字节</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="281" />
        <source>编程 FLASH ...</source>
        <translation>编程 FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="301" />
        <source>写入数据失败，偏移 %1</source>
        <translation>写入数据失败，偏移 %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="311" />
        <source>编程响应超时，偏移 %1</source>
        <translation>编程响应超时，偏移 %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="319" />
        <source>编程失败，错误码 %1，偏移 %2</source>
        <translation>编程失败，错误码 %1，偏移 %2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="330" />
        <source>编程 FLASH ... %1%</source>
        <translation>编程 FLASH ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="340" />
        <source>编程完成</source>
        <translation>编程完成</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="346" />
        <location filename="../src/iapworker.cpp" line="347" />
        <source>校验 FLASH ...</source>
        <translation>校验 FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="372" />
        <source>发送校验命令失败，偏移 %1</source>
        <translation>发送校验命令失败，偏移 %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="382" />
        <source>校验响应超时，偏移 %1</source>
        <translation>校验响应超时，偏移 %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="390" />
        <source>校验失败，错误码 %1，地址 0x%2</source>
        <translation>校验失败，错误码 %1，地址 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="404" />
        <source>校验 FLASH ... %1%</source>
        <translation>校验 FLASH ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="407" />
        <source>校验成功</source>
        <translation>校验成功</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="413" />
        <source>发送升级结束命令 ...</source>
        <translation>发送升级结束命令 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="414" />
        <source>结束升级 ...</source>
        <translation>结束升级 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="422" />
        <source>发送结束命令失败</source>
        <translation>发送结束命令失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="431" />
        <source>设备确认升级完成</source>
        <translation>设备确认升级完成</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="433" />
        <source>设备已复位（无应答属正常现象）</source>
        <translation>设备已复位（无应答属正常现象）</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="448" />
        <source>读取固件文件 ...</source>
        <translation>读取固件文件 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="451" />
        <source>固件加载失败：%1</source>
        <translation>固件加载失败：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="455" />
        <source>已加载固件：%1</source>
        <translation>已加载固件：%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="456" />
        <source>  格式：%1，大小：%2 字节</source>
        <translation>  格式：%1，大小：%2 字节</translation>
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
        <translation>  地址范围：0x%1 - 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="462" />
        <source>  校验和：0x%1</source>
        <translation>  校验和：0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="465" />
        <source>固件数据为空</source>
        <translation>固件数据为空</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="478" />
        <source>开始升级 ...</source>
        <translation>开始升级 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="479" />
        <source>========== 开始固件升级 %1 ==========</source>
        <translation>========== 开始固件升级 %1 ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="486" />
        <source>固件文件加载失败</source>
        <translation>固件文件加载失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="491" />
        <source>进入 IAP 模式 ...</source>
        <translation>进入 IAP 模式 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="493" />
        <source>无法进入 IAP 模式</source>
        <translation>无法进入 IAP 模式</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="498" />
        <source>查找 IAP 设备 ...</source>
        <translation>查找 IAP 设备 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="500" />
        <source>未找到 IAP 模式的设备</source>
        <translation>未找到 IAP 模式的设备</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="503" />
        <source>已连接 IAP 设备</source>
        <translation>已连接 IAP 设备</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="508" />
        <source>擦除 FLASH 失败</source>
        <translation>擦除 FLASH 失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="516" />
        <source>编程 FLASH 失败</source>
        <translation>编程 FLASH 失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="525" />
        <source>校验 FLASH 失败</source>
        <translation>校验 FLASH 失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="532" />
        <source>结束升级失败</source>
        <translation>结束升级失败</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="538" />
        <source>升级完成</source>
        <translation>升级完成</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="539" />
        <source>========== 固件升级成功 ==========</source>
        <translation>========== 固件升级成功 ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="540" />
        <source>固件升级成功，设备将重新启动</source>
        <translation>固件升级成功，设备将重新启动</translation>
    </message>
</context>
<context>
    <name>LanguageManager</name>
    <message>
        <location filename="../src/languagemanager.cpp" line="93" />
        <source>跟随系统(&amp;A)</source>
        <translation>跟随系统(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="94" />
        <source>English(&amp;E)</source>
        <translation>English(&amp;E)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="95" />
        <source>简体中文(&amp;C)</source>
        <translation>简体中文(&amp;C)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="123" />
        <source>简体中文</source>
        <translation>简体中文</translation>
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
        <translation>CH32H417 逻辑分析仪固件升级工具</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="419" />
        <source>设备</source>
        <translation>设备</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="420" />
        <source>固件文件</source>
        <translation>固件文件</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="421" />
        <source>IAP 参数</source>
        <translation>IAP 参数</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="424" />
        <source>设备列表：</source>
        <translation>设备列表：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="425" />
        <source>设备状态：</source>
        <translation>设备状态：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="426" />
        <source>固件版本：</source>
        <translation>固件版本：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="427" />
        <source>文件路径：</source>
        <translation>文件路径：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="428" />
        <source>固件信息：</source>
        <translation>固件信息：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="432" />
        <source>VID：0x</source>
        <translation>VID：0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="433" />
        <source>PID：0x</source>
        <translation>PID：0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="434" />
        <source>默认值 VID=0x1A86 PID=0xFE17</source>
        <translation>默认值 VID=0x1A86 PID=0xFE17</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="437" />
        <source>刷新(&amp;R)</source>
        <translation>刷新(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="438" />
        <source>浏览(&amp;B)...</source>
        <translation>浏览(&amp;B)...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="440" />
        <source>选择或直接拖入 .hex / .bin 固件文件</source>
        <translation>选择或直接拖入 .hex / .bin 固件文件</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="442" />
        <source>升级日志：</source>
        <translation>升级日志：</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="443" />
        <source>开始升级(&amp;S)</source>
        <translation>开始升级(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="444" />
        <source>取消(&amp;C)</source>
        <translation>取消(&amp;C)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="445" />
        <location filename="../src/mainwindow.cpp" line="453" />
        <source>退出(&amp;X)</source>
        <translation>退出(&amp;X)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="451" />
        <source>文件(&amp;F)</source>
        <translation>文件(&amp;F)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="452" />
        <source>打开固件(&amp;O)...</source>
        <translation>打开固件(&amp;O)...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="454" />
        <source>工具(&amp;T)</source>
        <translation>工具(&amp;T)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="455" />
        <source>刷新设备(&amp;R)</source>
        <translation>刷新设备(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="456" />
        <source>清空日志(&amp;L)</source>
        <translation>清空日志(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="458" />
        <source>语言(&amp;L)</source>
        <translation>语言(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="459" />
        <source>帮助(&amp;H)</source>
        <translation>帮助(&amp;H)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="460" />
        <source>关于(&amp;A)</source>
        <translation>关于(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="584" />
        <source>十六进制，例如 08006000</source>
        <translation>十六进制，例如 08006000</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="632" />
        <source>(未发现设备)</source>
        <translation>(未发现设备)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="710" />
        <source>读取失败</source>
        <translation>读取失败</translation>
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
        <translation>选择固件文件</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="793" />
        <source>固件文件 (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;二进制文件 (*.bin);;所有文件 (*.*)</source>
        <translation>固件文件 (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;二进制文件 (*.bin);;所有文件 (*.*)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="825" />
        <source>%1　大小：%2　地址：0x%3 - 0x%4　校验和：0x%5</source>
        <translation>%1　大小：%2　地址：0x%3 - 0x%4　校验和：0x%5</translation>
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
        <translation>提示</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="859" />
        <source>请先选择一个有效的固件文件。</source>
        <translation>请先选择一个有效的固件文件。</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="634" />
        <location filename="../src/mainwindow.cpp" line="865" />
        <source>未发现设备</source>
        <translation>未发现设备</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="430" />
        <source>BIN 基地址：0x</source>
        <translation>BIN 基地址：0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="439" />
        <source>.bin 文件的烧录起始地址（十六进制，例如 08006000）</source>
        <translation>.bin 文件的烧录起始地址（十六进制，例如 08006000）</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="705" />
        <source>&lt;font color='%1'&gt;已连接（运行模式，CH375 通道）&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;已连接（运行模式，CH375 通道）&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="713" />
        <source>软件版本：v%1　硬件版本：v%2</source>
        <translation>软件版本：v%1　硬件版本：v%2</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="719" />
        <source>&lt;font color='%1'&gt;已连接（IAP 升级模式，HID 通道）&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;已连接（IAP 升级模式，HID 通道）&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="726" />
        <source>&lt;font color='%1'&gt;未发现设备&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;未发现设备&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="811" />
        <source>&lt;font color='%1'&gt;尚未选择有效的固件文件&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;尚未选择有效的固件文件&lt;/font&gt;</translation>
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
        <translation>当前没有检测到 CH32H417 设备。

如果设备已经处于 IAP 模式（例如按住按键上电），可以继续升级；
否则请先连接设备。

是否继续？</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="877" />
        <source>固件错误</source>
        <translation>固件错误</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="893" />
        <source>准备中 ...</source>
        <translation>准备中 ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="896" />
        <source>目标设备：%1</source>
        <translation>目标设备：%1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="922" />
        <source>正在请求取消 ...</source>
        <translation>正在请求取消 ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="947" />
        <location filename="../src/mainwindow.cpp" line="969" />
        <source>升级完成</source>
        <translation>升级完成</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="949" />
        <source>完成</source>
        <translation>完成</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="950" />
        <source>固件升级成功！
设备将重启并运行新固件。</source>
        <translation>固件升级成功！
设备将重启并运行新固件。</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="953" />
        <location filename="../src/mainwindow.cpp" line="972" />
        <source>升级失败</source>
        <translation>升级失败</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="955" />
        <source>失败</source>
        <translation>失败</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="976" />
        <source>就绪</source>
        <translation>就绪</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1038" />
        <source>关于</source>
        <translation>关于</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1041" />
        <source>&lt;h3&gt;CH32H417 逻辑分析仪固件升级工具&lt;/h3&gt;&lt;p&gt;版本：%1&lt;/p&gt;&lt;p&gt;基于 Qt 6 开发，使用 MSYS2 (MINGW64) 静态编译。&lt;/p&gt;&lt;p&gt;升级流程：CH375 通道发送进入 IAP 命令 → 设备复位为 HID IAP 设备 → 擦除 / 编程 / 校验 / 结束。&lt;/p&gt;&lt;p&gt;需要安装 CH375 驱动。&lt;/p&gt;</source>
        <translation>&lt;h3&gt;CH32H417 逻辑分析仪固件升级工具&lt;/h3&gt;&lt;p&gt;版本：%1&lt;/p&gt;&lt;p&gt;基于 Qt 6 开发，使用 MSYS2 (MINGW64) 静态编译。&lt;/p&gt;&lt;p&gt;升级流程：CH375 通道发送进入 IAP 命令 → 设备复位为 HID IAP 设备 → 擦除 / 编程 / 校验 / 结束。&lt;/p&gt;&lt;p&gt;需要安装 CH375 驱动。&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1079" />
        <source>正在升级</source>
        <translation>正在升级</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1080" />
        <source>升级正在进行中，现在退出可能导致设备固件损坏。
确定要退出吗？</source>
        <translation>升级正在进行中，现在退出可能导致设备固件损坏。
确定要退出吗？</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="457" />
        <source>视图(&amp;V)</source>
        <translation>视图(&amp;V)</translation>
    </message>
</context>
<context>
    <name>ThemeManager</name>
    <message>
        <location filename="../src/thememanager.cpp" line="165" />
        <source>跟随系统(&amp;S)</source>
        <translation>跟随系统(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/thememanager.cpp" line="167" />
        <source>浅色(&amp;L)</source>
        <translation>浅色(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/thememanager.cpp" line="170" />
        <source>深色(&amp;D)</source>
        <translation>深色(&amp;D)</translation>
    </message>
</context>
</TS>