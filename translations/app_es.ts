<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="es_ES">
<context>
    <name>Ch375Dev</name>
    <message>
        <location filename="../src/ch375dev.cpp" line="80" />
        <source>The device is in use by another program.
Close the program that currently uses the board (for example the logic analyzer software) and refresh.</source>
        <translation>El dispositivo está siendo usado por otro programa.
Cierre el programa que utiliza la placa (por ejemplo, el software del analizador lógico) y actualice la lista.</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="102" />
        <source>Unable to load CH375DLL64.DLL / CH375DLL.DLL.
Make sure the CH375 driver is installed and that the driver DLL is placed next to this program or in a directory on the system search path.</source>
        <translation>No se puede cargar CH375DLL64.DLL / CH375DLL.DLL.
Asegúrese de que el controlador CH375 esté instalado y de que la DLL del controlador se encuentre junto a este programa o en un directorio de la ruta de búsqueda del sistema.</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="211" />
        <location filename="../src/ch375dev.cpp" line="268" />
        <source>Invalid device index</source>
        <translation>Índice de dispositivo no válido</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="222" />
        <location filename="../src/ch375dev.cpp" line="279" />
        <source>Cannot open CH375 device (index %1)</source>
        <translation>No se puede abrir el dispositivo CH375 (índice %1)</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="248" />
        <source>Failed to read firmware version (device did not respond)</source>
        <translation>No se pudo leer la versión del firmware (el dispositivo no responde)</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="255" />
        <source>Unexpected version response: 0x%1</source>
        <translation>Respuesta de versión inesperada: 0x%1</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="297" />
        <source>Failed to send the enter-IAP-mode command</source>
        <translation>No se pudo enviar el comando de entrada al modo IAP</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="332" />
        <source>The firmware version cannot be read on the USB-UART (serial) channel</source>
        <translation>La versión del firmware no se puede leer en el canal USB-UART (serie)</translation>
    </message>
</context>
<context>
    <name>FirmwareImage</name>
    <message>
        <location filename="../src/firmwareimage.cpp" line="87" />
        <source>Invalid HEX file: cannot parse line %1</source>
        <translation>Archivo HEX no válido: no se puede analizar la línea %1</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="92" />
        <source>Invalid HEX file: line %1 is too short</source>
        <translation>Archivo HEX no válido: la línea %1 es demasiado corta</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="101" />
        <source>HEX checksum error on line %1 (0x%2)</source>
        <translation>Error de suma de comprobación HEX en la línea %1 (0x%2)</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="109" />
        <source>Invalid HEX file: data length mismatch on line %1</source>
        <translation>Archivo HEX no válido: la longitud de datos no coincide en la línea %1</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="163" />
        <source>HEX file contains no valid data record</source>
        <translation>El archivo HEX no contiene ningún registro de datos válido</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="183" />
        <source>HEX address range out of bounds: 0x%1 - 0x%2</source>
        <translation>Rango de direcciones HEX fuera de los límites: 0x%1 - 0x%2</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="222" />
        <source>Cannot open firmware file: %1</source>
        <translation>No se puede abrir el archivo de firmware: %1</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="230" />
        <source>Firmware file is empty</source>
        <translation>El archivo de firmware está vacío</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="265" />
        <source>%1 B</source>
        <translation>%1 B</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="267" />
        <source>%1 KB (%2 bytes)</source>
        <translation>%1 KB (%2 bytes)</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="270" />
        <source>%1 MB (%2 bytes)</source>
        <translation>%1 MB (%2 bytes)</translation>
    </message>
</context>
<context>
    <name>IapCtl</name>
    <message>
        <location filename="../src/iapctl.cpp" line="53" />
        <source>Unexpected answer from the bootloader: 0x%1</source>
        <translation>Respuesta inesperada del gestor de arranque: 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="64" />
        <source>The bootloader did not answer (timeout)</source>
        <translation>El gestor de arranque no respondió (tiempo de espera agotado)</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="78" />
        <source>Failed to initialize hidapi</source>
        <translation>No se pudo inicializar hidapi</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="84" />
        <source>No IAP device found (VID:0x%1 PID:0x%2).
These commands only work while the board sits in the bootloader.</source>
        <translation>No se encontró ningún dispositivo IAP (VID:0x%1 PID:0x%2).
Estos comandos solo funcionan mientras la placa está en el gestor de arranque.</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="115" />
        <source>Failed to send command 0x%1 to the bootloader</source>
        <translation>No se pudo enviar el comando 0x%1 al gestor de arranque</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="129" />
        <source>The bootloader refused the request (error code %1)</source>
        <translation>El gestor de arranque rechazó la solicitud (código de error %1)</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="163" />
        <source>Slot number out of range (0..%1)</source>
        <translation>Número de ranura fuera de rango (0..%1)</translation>
    </message>
</context>
<context>
    <name>IapWorker</name>
    <message>
        <location filename="../src/iapworker.cpp" line="32" />
        <source>Unknown error</source>
        <translation>Error desconocido</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="82" />
        <source>Failed to initialize hidapi</source>
        <translation>No se pudo inicializar hidapi</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="92" />
        <source>Cancelled while waiting for the IAP device</source>
        <translation>Cancelado mientras se esperaba el dispositivo IAP</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="99" />
        <source>Connected to IAP device (VID:0x%1 PID:0x%2)</source>
        <translation>Conectado al dispositivo IAP (VID:0x%1 PID:0x%2)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="106" />
        <source>Waiting for the IAP device (VID:0x%1 PID:0x%2) ...</source>
        <translation>Esperando el dispositivo IAP (VID:0x%1 PID:0x%2) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="113" />
        <source>IAP device not found after waiting %1 seconds</source>
        <translation>No se encontró el dispositivo IAP tras esperar %1 segundos</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="141" />
        <source>Write cancelled</source>
        <translation>Escritura cancelada</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="155" />
        <source>HID write failed: %1</source>
        <translation>Error de escritura HID: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="160" />
        <source>HID write timed out (%1 ms)</source>
        <translation>Tiempo de espera agotado al escribir HID (%1 ms)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="175" />
        <source>Read cancelled</source>
        <translation>Lectura cancelada</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="195" />
        <source>HID read failed: %1</source>
        <translation>Error de lectura HID: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="211" />
        <location filename="../src/iapworker.cpp" line="267" />
        <location filename="../src/iapworker.cpp" line="324" />
        <location filename="../src/iapworker.cpp" line="397" />
        <source>Upgrade cancelled</source>
        <translation>Actualización cancelada</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="216" />
        <source>The device is in use by another program.
Close the program that currently uses the board (for example the logic analyzer software) and refresh.</source>
        <translation>El dispositivo está siendo usado por otro programa.
Cierre el programa que utiliza la placa (por ejemplo, el software del analizador lógico) y actualice la lista.</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="223" />
        <source>Device is already in IAP mode, skipping the mode switch</source>
        <translation>El dispositivo ya está en modo IAP, se omite el cambio de modo</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="233" />
        <source>No usable CH375 device index, cannot send the switch command</source>
        <translation>No hay un índice de dispositivo CH375 utilizable, no se puede enviar el comando de cambio</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="247" />
        <source>Opening %1 at the IAP baud rate %2 ...</source>
        <translation>Abriendo %1 con la velocidad IAP %2 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="251" />
        <source>Sending enter-IAP-mode command over libusb (bus %1, address %2) ...</source>
        <translation>Enviando el comando de entrada al modo IAP por libusb (bus %1, dirección %2) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="255" />
        <source>Sending enter-IAP-mode command to device (CH375 index %1) ...</source>
        <translation>Enviando el comando de entrada al modo IAP al dispositivo (índice CH375 %1) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="259" />
        <source>Failed to enter IAP mode: %1</source>
        <translation>No se pudo entrar en el modo IAP: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="263" />
        <source>Command sent, waiting for the device to reset into a HID IAP device ...</source>
        <translation>Comando enviado, esperando a que el dispositivo se reinicie como dispositivo HID IAP ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="281" />
        <source>Erasing FLASH, start address 0x%1</source>
        <translation>Borrando FLASH, dirección inicial 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="282" />
        <source>Erasing FLASH ...</source>
        <translation>Borrando FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="294" />
        <source>Failed to send the erase command</source>
        <translation>No se pudo enviar el comando de borrado</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="301" />
        <source>Erase response timed out</source>
        <translation>Tiempo de espera agotado en la respuesta de borrado</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="306" />
        <source>Erase failed, error code: %1</source>
        <translation>Error al borrar, código de error: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="310" />
        <source>Erase complete</source>
        <translation>Borrado completado</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="316" />
        <source>Programming FLASH, %1 bytes in total</source>
        <translation>Programando FLASH, %1 bytes en total</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="317" />
        <location filename="../src/iapworker.cpp" line="372" />
        <source>Programming FLASH ... %1%</source>
        <translation>Programando FLASH ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="337" />
        <source>Failed to write data, offset %1</source>
        <translation>No se pudieron escribir los datos, desplazamiento %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="347" />
        <source>Programming response timed out, offset %1</source>
        <translation>Tiempo de espera agotado en la respuesta de programación, desplazamiento %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="355" />
        <source>Programming failed, error code %1, offset %2</source>
        <translation>Error de programación, código %1, desplazamiento %2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="382" />
        <source>Programming complete</source>
        <translation>Programación completada</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="388" />
        <source>Verifying FLASH ...</source>
        <translation>Verificando FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="389" />
        <location filename="../src/iapworker.cpp" line="448" />
        <source>Verifying FLASH ... %1%</source>
        <translation>Verificando FLASH ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="414" />
        <source>Failed to send the verify command, offset %1</source>
        <translation>No se pudo enviar el comando de verificación, desplazamiento %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="424" />
        <source>Verify response timed out, offset %1</source>
        <translation>Tiempo de espera agotado en la respuesta de verificación, desplazamiento %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="432" />
        <source>Verification failed, error code %1, address 0x%2</source>
        <translation>Verificación fallida, código de error %1, dirección 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="451" />
        <source>Verification succeeded</source>
        <translation>Verificación correcta</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="457" />
        <source>Sending the upgrade-finish command ...</source>
        <translation>Enviando el comando de finalización de la actualización ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="458" />
        <source>Finishing upgrade ...</source>
        <translation>Finalizando la actualización ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="466" />
        <source>Failed to send the finish command</source>
        <translation>No se pudo enviar el comando de finalización</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="475" />
        <source>Device confirmed the upgrade</source>
        <translation>El dispositivo confirmó la actualización</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="477" />
        <source>Device has reset (no response is normal)</source>
        <translation>El dispositivo se ha reiniciado (la ausencia de respuesta es normal)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="492" />
        <source>Reading firmware file ...</source>
        <translation>Leyendo el archivo de firmware ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="495" />
        <source>Failed to load firmware: %1</source>
        <translation>No se pudo cargar el firmware: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="499" />
        <source>Firmware loaded: %1</source>
        <translation>Firmware cargado: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="500" />
        <source>  Format: %1, size: %2 bytes</source>
        <translation>  Formato: %1, tamaño: %2 bytes</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="501" />
        <source>Intel HEX</source>
        <translation>Intel HEX</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="501" />
        <source>BIN</source>
        <translation>BIN</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="503" />
        <source>  Address range: 0x%1 - 0x%2</source>
        <translation>  Rango de direcciones: 0x%1 - 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="506" />
        <source>  Checksum: 0x%1</source>
        <translation>  Suma de comprobación: 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="509" />
        <source>Firmware data is empty</source>
        <translation>Los datos del firmware están vacíos</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="522" />
        <source>Starting upgrade ...</source>
        <translation>Iniciando la actualización ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="523" />
        <source>========== Firmware upgrade started %1 ==========</source>
        <translation>========== Actualización de firmware iniciada %1 ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="533" />
        <source>Failed to load the firmware file</source>
        <translation>No se pudo cargar el archivo de firmware</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="538" />
        <source>Entering IAP mode ...</source>
        <translation>Entrando en el modo IAP ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="540" />
        <source>Unable to enter IAP mode</source>
        <translation>No se puede entrar en el modo IAP</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="546" />
        <source>Device is now in IAP mode</source>
        <translation>El dispositivo está ahora en modo IAP</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="547" />
        <source>The device rebooted into IAP mode</source>
        <translation>El dispositivo se reinició en modo IAP</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="552" />
        <source>Looking for the IAP device ...</source>
        <translation>Buscando el dispositivo IAP ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="554" />
        <source>No device in IAP mode found</source>
        <translation>No se encontró ningún dispositivo en modo IAP</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="557" />
        <source>Connected to the IAP device</source>
        <translation>Conectado al dispositivo IAP</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="562" />
        <source>Failed to erase FLASH</source>
        <translation>No se pudo borrar la FLASH</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="570" />
        <source>Failed to program FLASH</source>
        <translation>No se pudo programar la FLASH</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="579" />
        <source>Failed to verify FLASH</source>
        <translation>No se pudo verificar la FLASH</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="586" />
        <source>Failed to finish the upgrade</source>
        <translation>No se pudo finalizar la actualización</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="592" />
        <source>Upgrade complete</source>
        <translation>Actualización completada</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="593" />
        <source>========== Firmware upgrade succeeded ==========</source>
        <translation>========== Actualización de firmware correcta ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="594" />
        <source>Firmware upgrade succeeded, the device will restart</source>
        <translation>Actualización de firmware correcta, el dispositivo se reiniciará</translation>
    </message>
</context>
<context>
    <name>LanguageManager</name>
    <message>
        <location filename="../src/languagemanager.cpp" line="125" />
        <source>Follow System(&amp;A)</source>
        <translation>Seguir al sistema(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="126" />
        <source>English(&amp;E)</source>
        <translation>Inglés(&amp;E)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="127" />
        <source>Simplified Chinese(&amp;C)</source>
        <translation>Chino simplificado(&amp;C)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="128" />
        <source>Russian(&amp;R)</source>
        <translation>Ruso(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="129" />
        <source>German(&amp;G)</source>
        <translation>Alemán(&amp;G)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="130" />
        <source>Spanish(&amp;S)</source>
        <translation>Español(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="152" />
        <source>Simplified Chinese</source>
        <translation>Chino simplificado</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="154" />
        <source>Russian</source>
        <translation>Ruso</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="156" />
        <source>German</source>
        <translation>Alemán</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="158" />
        <source>Spanish</source>
        <translation>Español</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="161" />
        <source>English</source>
        <translation>Inglés</translation>
    </message>
</context>
<context>
    <name>LibusbDev</name>
    <message>
        <location filename="../src/libusbdev.cpp" line="83" />
        <source>Cannot open the USB device (libusb error %1). The board must be bound to a generic USB driver (WinUSB on Windows) and must not be in use by another program.</source>
        <translation>No se puede abrir el dispositivo USB (error de libusb %1). La placa debe estar vinculada a un controlador USB genérico (WinUSB en Windows) y no debe estar en uso por otro programa.</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="98" />
        <source>Cannot claim the USB interface (libusb error %1). Close other programs that use the device and try again.</source>
        <translation>No se puede reclamar la interfaz USB (error de libusb %1). Cierre los programas que usan el dispositivo e inténtelo de nuevo.</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="124" />
        <source>Failed to send command 0x%1 (libusb error %2)</source>
        <translation>No se pudo enviar el comando 0x%1 (error de libusb %2)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="140" />
        <source>The device did not answer command 0x%1 (libusb error %2)</source>
        <translation>El dispositivo no respondió al comando 0x%1 (error de libusb %2)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="158" />
        <source>libusb is not available</source>
        <translation>libusb no está disponible</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="166" />
        <source>Unable to initialise libusb (error %1)</source>
        <translation>No se pudo inicializar libusb (error %1)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="198" />
        <source>Failed to enumerate the USB devices (libusb error %1)</source>
        <translation>No se pudieron enumerar los dispositivos USB (error de libusb %1)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="281" />
        <location filename="../src/libusbdev.cpp" line="323" />
        <source>The device is no longer present (bus %1, address %2)</source>
        <translation>El dispositivo ya no está presente (bus %1, dirección %2)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="305" />
        <source>Failed to send the enter-IAP-mode command</source>
        <translation>No se pudo enviar el comando de entrada al modo IAP</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="346" />
        <source>Unexpected version response: 0x%1</source>
        <translation>Respuesta de versión inesperada: 0x%1</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../src/mainwindow.cpp" line="85" />
        <source> (in use)</source>
        <translation> (en uso)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="492" />
        <source>CH32H417 Logic Analyzer Firmware Upgrade Tool</source>
        <translation>Herramienta de actualización de firmware del analizador lógico CH32H417</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="495" />
        <source>Device</source>
        <translation>Dispositivo</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="496" />
        <source>Firmware File</source>
        <translation>Archivo de firmware</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="497" />
        <source>IAP Settings</source>
        <translation>Ajustes de IAP</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="500" />
        <source>Device List:</source>
        <translation>Lista de dispositivos:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="501" />
        <source>Device Status:</source>
        <translation>Estado del dispositivo:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="502" />
        <source>Firmware Version:</source>
        <translation>Versión del firmware:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="503" />
        <source>File Path:</source>
        <translation>Ruta del archivo:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="504" />
        <source>Firmware Info:</source>
        <translation>Información del firmware:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="507" />
        <source>BIN Base Address: 0x</source>
        <translation>Dirección base del BIN: 0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="509" />
        <source>VID: 0x</source>
        <translation>VID: 0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="510" />
        <source>PID: 0x</source>
        <translation>PID: 0x</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="511" />
        <source>Defaults: VID=0x1A86 PID=0xFE17</source>
        <translation>Valores por defecto: VID=0x1A86 PID=0xFE17</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="514" />
        <source>Refresh(&amp;R)</source>
        <translation>Actualizar(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="515" />
        <source>Browse(&amp;B)...</source>
        <translation>Examinar(&amp;B)...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="520" />
        <source>Programming start address for .bin files (hexadecimal, e.g. 08006000). On the WeAct Studio Logic Analyzer V2 pick one of the three APP slots: slot 0 = logic analyzer, slot 1 = USB to UART, slot 2 = example.</source>
        <translation>Dirección de inicio de programación para archivos .bin (hexadecimal, p. ej. 08006000).
En el WeAct Studio Logic Analyzer V2 elija una de las tres ranuras APP: ranura 0 = analizador lógico, ranura 1 = USB a UART, ranura 2 = ejemplo.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="523" />
        <source>Select or drop a .hex / .bin firmware file</source>
        <translation>Seleccione o arrastre un archivo de firmware .hex / .bin</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="525" />
        <source>Upgrade Log</source>
        <translation>Registro de actualización</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="526" />
        <source>Reboot into:</source>
        <translation>Reiniciar en:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="528" />
        <source>Slot %1</source>
        <translation>Ranura %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="530" />
        <source>Make slot %1 (0x%2) the active one and boot it</source>
        <translation>Hacer activa la ranura %1 (0x%2) y arrancarla</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="533" />
        <source>Start Upgrade(&amp;S)</source>
        <translation>Iniciar actualización(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="534" />
        <location filename="../src/mainwindow.cpp" line="543" />
        <source>Exit(&amp;X)</source>
        <translation>Salir(&amp;X)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="541" />
        <source>File(&amp;F)</source>
        <translation>Archivo(&amp;F)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="542" />
        <source>Open Firmware(&amp;O)...</source>
        <translation>Abrir firmware(&amp;O)...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="544" />
        <source>Tools(&amp;T)</source>
        <translation>Herramientas(&amp;T)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="545" />
        <source>Refresh Devices(&amp;R)</source>
        <translation>Actualizar dispositivos(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="546" />
        <source>Reboot into Active Slot(&amp;B)</source>
        <translation>Reiniciar en la ranura activa(&amp;B)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="547" />
        <source>Switch APP Slot(&amp;S)</source>
        <translation>Cambiar ranura APP(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="549" />
        <location filename="../src/mainwindow.cpp" line="751" />
        <source>Slot %1: 0x%2</source>
        <translation>Ranura %1: 0x%2</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="553" />
        <source>Clear Log(&amp;L)</source>
        <translation>Borrar registro(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="554" />
        <source>View(&amp;V)</source>
        <translation>Ver(&amp;V)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="555" />
        <source>Language(&amp;L)</source>
        <translation>Idioma(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="556" />
        <source>Help(&amp;H)</source>
        <translation>Ayuda(&amp;H)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="557" />
        <source>About(&amp;A)</source>
        <translation>Acerca de(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="717" />
        <source>Hexadecimal, e.g. 08006000</source>
        <translation>Hexadecimal, p. ej. 08006000</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="834" />
        <source>(No device found)</source>
        <translation>(No se encontró ningún dispositivo)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="836" />
        <source>No device found</source>
        <translation>No se encontró ningún dispositivo</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="952" />
        <source>&lt;font color='%1'&gt;Connected (application mode, %2 channel)&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Conectado (modo aplicación, canal %2)&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="957" />
        <location filename="../src/mainwindow.cpp" line="976" />
        <location filename="../src/mainwindow.cpp" line="983" />
        <location filename="../src/mainwindow.cpp" line="990" />
        <source>-</source>
        <translation>-</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="959" />
        <source>The firmware version cannot be read on the USB-UART (serial) channel</source>
        <translation>La versión del firmware no se puede leer en el canal USB-UART (serie)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="965" />
        <source>Read failed</source>
        <translation>Error de lectura</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="968" />
        <source>Software version: v%1  Hardware version: v%2</source>
        <translation>Versión de software: v%1  Versión de hardware: v%2</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="975" />
        <source>&lt;font color='%1'&gt;Connected (IAP upgrade mode)&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Conectado (modo de actualización IAP)&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="982" />
        <source>&lt;font color='%1'&gt;Device in use by another program&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Dispositivo en uso por otro programa&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="989" />
        <source>&lt;font color='%1'&gt;No device found&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;No se encontró ningún dispositivo&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1028" />
        <source>Leave &amp;IAP</source>
        <translation>Salir de &amp;IAP</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1029" />
        <source>Reboot into &amp;IAP</source>
        <translation>Reiniciar en &amp;IAP</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1033" />
        <source>Reboot the board and run the active APP slot again</source>
        <translation>Reiniciar la placa y ejecutar de nuevo la ranura APP activa</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1034" />
        <source>Reboot the board into its bootloader (IAP mode)</source>
        <translation>Reiniciar la placa en su gestor de arranque (modo IAP)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1044" />
        <source>Rebooting the device out of IAP mode ...</source>
        <translation>Reiniciando el dispositivo fuera del modo IAP ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1052" />
        <source>Leaving IAP failed: %1</source>
        <translation>Error al salir del modo IAP: %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1053" />
        <location filename="../src/mainwindow.cpp" line="1145" />
        <location filename="../src/mainwindow.cpp" line="1188" />
        <location filename="../src/mainwindow.cpp" line="1445" />
        <location filename="../src/mainwindow.cpp" line="1450" />
        <location filename="../src/mainwindow.cpp" line="1470" />
        <source>Failed</source>
        <translation>Fallido</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1057" />
        <location filename="../src/mainwindow.cpp" line="1149" />
        <source>Reboot request accepted, the device restarts ...</source>
        <translation>Solicitud de reinicio aceptada, el dispositivo se reinicia ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1102" />
        <source>Not available while an upgrade is running</source>
        <translation>No disponible mientras hay una actualización en curso</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1105" />
        <source>Needs a board that sits in the IAP bootloader</source>
        <translation>Requiere una placa en el gestor de arranque IAP</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1115" />
        <location filename="../src/mainwindow.cpp" line="1123" />
        <source>Not Available</source>
        <translation>No disponible</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1116" />
        <source>Wait for the running upgrade to finish.</source>
        <translation>Espere a que finalice la actualización en curso.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1120" />
        <source>This command needs a board that sits in the IAP bootloader, the current device is in application mode.</source>
        <translation>Este comando requiere una placa en el gestor de arranque IAP; el dispositivo actual está en modo aplicación.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1124" />
        <source>No CH32H417 device in IAP mode found.
These commands need a board that sits in the bootloader (power-cycle it with the button held).</source>
        <translation>No se encontró ningún dispositivo CH32H417 en modo IAP.
Estos comandos requieren una placa en el gestor de arranque (corte y restablezca la alimentación con el botón pulsado).</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1136" />
        <source>Rebooting the device into its active slot ...</source>
        <translation>Reiniciando el dispositivo en su ranura activa ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1144" />
        <source>Reboot failed: %1</source>
        <translation>Error al reiniciar: %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1178" />
        <source>Switching to APP slot %1 (0x%2) ...</source>
        <translation>Cambiando a la ranura APP %1 (0x%2) ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1187" />
        <source>Slot switch failed: %1</source>
        <translation>Error al cambiar de ranura: %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1192" />
        <source>Slot %1 is now active, the device reboots into it ...</source>
        <translation>La ranura %1 está ahora activa, el dispositivo se reinicia en ella ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1261" />
        <source>Select Firmware File</source>
        <translation>Seleccionar archivo de firmware</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1263" />
        <source>Firmware Files (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binary Files (*.bin);;All Files (*.*)</source>
        <translation>Archivos de firmware (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Archivos binarios (*.bin);;Todos los archivos (*.*)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1281" />
        <source>&lt;font color='%1'&gt;No valid firmware file selected&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;No se ha seleccionado un archivo de firmware válido&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1290" />
        <source>&lt;font color='%1'&gt;%2&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;%2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1295" />
        <source>%1  Size: %2  Address: 0x%3 - 0x%4  Checksum: 0x%5</source>
        <translation>%1  Tamaño: %2  Dirección: 0x%3 - 0x%4  Suma: 0x%5</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1296" />
        <source>Intel HEX</source>
        <translation>Intel HEX</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1296" />
        <source>BIN</source>
        <translation>BIN</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1331" />
        <source>Hint</source>
        <translation>Sugerencia</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1331" />
        <source>Please select a valid firmware file first.</source>
        <translation>Seleccione primero un archivo de firmware válido.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1337" />
        <source>No Device Found</source>
        <translation>No se encontró ningún dispositivo</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1338" />
        <source>No CH32H417 device was detected.

If the device is already in IAP mode (for example powered up with the button held down), you can continue;
otherwise please connect the device first.

Continue?</source>
        <translation>No se detectó ningún dispositivo CH32H417.

Si el dispositivo ya está en modo IAP (por ejemplo, encendido con el botón pulsado), puede continuar;
de lo contrario, conecte primero el dispositivo.

¿Continuar?</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1350" />
        <source>Firmware Error</source>
        <translation>Error de firmware</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1383" />
        <source>Preparing ...</source>
        <translation>Preparando ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1388" />
        <source>Target device: IAP HID (VID:0x%1 PID:0x%2)</source>
        <translation>Dispositivo de destino: IAP HID (VID:0x%1 PID:0x%2)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1392" />
        <source>Target device: serial (COM port %1)</source>
        <translation>Dispositivo de destino: serie (puerto COM %1)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1394" />
        <source>Target device: libusb (bus %1, address %2)</source>
        <translation>Dispositivo de destino: libusb (bus %1, dirección %2)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1397" />
        <source>Target device: CH375 #%1</source>
        <translation>Dispositivo de destino: CH375 #%1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1440" />
        <source>Device is in IAP Mode</source>
        <translation>El dispositivo está en modo IAP</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1447" />
        <location filename="../src/mainwindow.cpp" line="1467" />
        <location filename="../src/mainwindow.cpp" line="1472" />
        <source>Please power-cycle the device (disconnect and reconnect the USB cable or the power supply) and run the upgrade again.</source>
        <translation>Corte y restablezca la alimentación del dispositivo (desconecte y vuelva a conectar el cable USB o la fuente de alimentación) y repita la actualización.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1458" />
        <location filename="../src/mainwindow.cpp" line="1489" />
        <source>Upgrade Complete</source>
        <translation>Actualización completada</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1460" />
        <source>Complete</source>
        <translation>Completado</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1461" />
        <source>Firmware upgrade succeeded!
The device will restart and run the new firmware.</source>
        <translation>¡Actualización de firmware correcta!
El dispositivo se reiniciará y ejecutará el nuevo firmware.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1465" />
        <location filename="../src/mainwindow.cpp" line="1492" />
        <source>Upgrade Failed</source>
        <translation>Actualización fallida</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1496" />
        <source>Ready</source>
        <translation>Listo</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1558" />
        <source>About</source>
        <translation>Acerca de</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1562" />
        <source>&lt;h3&gt;CH32H417 Logic Analyzer&lt;br&gt;Firmware Upgrade Tool&lt;/h3&gt;&lt;p&gt;Version: %1&lt;/p&gt;&lt;p&gt;&lt;b&gt;WeAct Studio&lt;/b&gt;&lt;br&gt;Copyright (C) 2026 WeAct Studio. All rights reserved.&lt;/p&gt;&lt;p&gt;This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.&lt;/p&gt;&lt;p&gt;License: GPL-3.0-or-later&lt;br&gt;&lt;a href='https://www.gnu.org/licenses/gpl-3.0.html'&gt;https://www.gnu.org/licenses/gpl-3.0.html&lt;/a&gt;&lt;/p&gt;&lt;p&gt;Built with Qt %2, statically compiled with MSYS2 (MINGW64).&lt;/p&gt;&lt;p&gt;Upgrade sequence: the enter-IAP command goes out over whichever USB channel the board is on - CH375, libusb / WinUSB, or the COM port of the USB-to-UART firmware. The board then resets into a HID IAP device, followed by erase / program / verify / finish.&lt;/p&gt;&lt;p&gt;A board that already sits in IAP mode can also be rebooted into its active slot, or switched to another APP slot, without downloading anything.&lt;/p&gt;&lt;p&gt;Windows needs one driver for the board: the WCH CH375 driver, or WinUSB when the board is bound to libusb.&lt;/p&gt;</source>
        <translation>&lt;h3&gt;Analizador lógico CH32H417&lt;br&gt;Herramienta de actualización de firmware&lt;/h3&gt;&lt;p&gt;Versión: %1&lt;/p&gt;&lt;p&gt;&lt;b&gt;WeAct Studio&lt;/b&gt;&lt;br&gt;Copyright (C) 2026 WeAct Studio. Todos los derechos reservados.&lt;/p&gt;&lt;p&gt;Este programa es software libre: puede redistribuirlo y/o modificarlo según los términos de la Licencia Pública General de GNU publicada por la Free Software Foundation, ya sea la versión 3 de la licencia o (a su elección) cualquier versión posterior. Se distribuye con la esperanza de que sea útil, pero SIN NINGUNA GARANTÍA, ni siquiera la garantía implícita de COMERCIABILIDAD o IDONEIDAD PARA UN PROPÓSITO PARTICULAR. Consulte la Licencia Pública General de GNU para más detalles.&lt;/p&gt;&lt;p&gt;Licencia: GPL-3.0-or-later&lt;br&gt;&lt;a href='https://www.gnu.org/licenses/gpl-3.0.html'&gt;https://www.gnu.org/licenses/gpl-3.0.html&lt;/a&gt;&lt;/p&gt;&lt;p&gt;Compilado con Qt %2, enlazado estáticamente con MSYS2 (MINGW64).&lt;/p&gt;&lt;p&gt;Secuencia de actualización: el comando de entrada al modo IAP se envía por el canal USB en el que esté la placa: CH375, libusb / WinUSB o el puerto COM del firmware USB a UART. Después la placa se reinicia como dispositivo HID IAP y se ejecutan borrado / programación / verificación / finalización.&lt;/p&gt;&lt;p&gt;Una placa que ya esté en modo IAP también puede reiniciarse en su ranura activa o cambiarse a otra ranura APP sin descargar nada.&lt;/p&gt;&lt;p&gt;Windows necesita un controlador para la placa: el controlador WCH CH375 o WinUSB si la placa está vinculada a libusb.&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1620" />
        <source>Upgrade in Progress</source>
        <translation>Actualización en curso</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1621" />
        <source>An upgrade is running; exiting now may corrupt the device firmware.
Are you sure you want to exit?</source>
        <translation>Hay una actualización en curso; salir ahora puede dañar el firmware del dispositivo.
¿Seguro que desea salir?</translation>
    </message>
</context>
<context>
    <name>SerialDev</name>
    <message>
        <location filename="../src/serialdev.cpp" line="104" />
        <source>Serial port enumeration is only supported on Windows</source>
        <translation>La enumeración de puertos serie solo se admite en Windows</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="111" />
        <source>Cannot enumerate the COM ports (error %1)</source>
        <translation>No se pueden enumerar los puertos COM (error %1)</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="233" />
        <source>Serial port access is only supported on Windows</source>
        <translation>El acceso al puerto serie solo se admite en Windows</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="245" />
        <source>%1 is open in another program.
Close the program (for example a serial terminal) and retry.</source>
        <translation>%1 está abierto en otro programa.
Cierre el programa (por ejemplo, un terminal serie) e inténtelo de nuevo.</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="251" />
        <source>Cannot open %1 (error %2)</source>
        <translation>No se puede abrir %1 (error %2)</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="262" />
        <source>Cannot query the settings of %1 (error %2)</source>
        <translation>No se puede consultar la configuración de %1 (error %2)</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="305" />
        <source>Cannot set the IAP baud rate on %1 (error %2)</source>
        <translation>No se puede establecer la velocidad IAP en %1 (error %2)</translation>
    </message>
</context>
<context>
    <name>ThemeManager</name>
    <message>
        <location filename="../src/thememanager.cpp" line="166" />
        <source>Follow System(&amp;S)</source>
        <translation>Seguir al sistema(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/thememanager.cpp" line="168" />
        <source>Light(&amp;L)</source>
        <translation>Claro(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/thememanager.cpp" line="171" />
        <source>Dark(&amp;D)</source>
        <translation>Oscuro(&amp;D)</translation>
    </message>
</context>
</TS>