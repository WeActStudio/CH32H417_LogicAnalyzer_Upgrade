<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="de_DE">
<context>
    <name>Ch375Dev</name>
    <message>
        <location filename="../src/ch375dev.cpp" line="80" />
        <source>The device is in use by another program.
Close the program that currently uses the board (for example the logic analyzer software) and refresh.</source>
        <translation>Das Gerät wird von einem anderen Programm verwendet.
Schließen Sie das Programm, das die Platine gerade nutzt (zum Beispiel die Logikanalysator-Software), und aktualisieren Sie die Liste.</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="102" />
        <source>Unable to load CH375DLL64.DLL / CH375DLL.DLL.
Make sure the CH375 driver is installed and that the driver DLL is placed next to this program or in a directory on the system search path.</source>
        <translation>CH375DLL64.DLL / CH375DLL.DLL konnte nicht geladen werden.
Stellen Sie sicher, dass der CH375-Treiber installiert ist und die Treiber-DLL neben diesem Programm oder in einem Verzeichnis des System-Suchpfads liegt.</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="211" />
        <location filename="../src/ch375dev.cpp" line="268" />
        <source>Invalid device index</source>
        <translation>Ungültiger Geräteindex</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="222" />
        <location filename="../src/ch375dev.cpp" line="279" />
        <source>Cannot open CH375 device (index %1)</source>
        <translation>CH375-Gerät kann nicht geöffnet werden (Index %1)</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="248" />
        <source>Failed to read firmware version (device did not respond)</source>
        <translation>Firmware-Version konnte nicht gelesen werden (Gerät antwortet nicht)</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="255" />
        <source>Unexpected version response: 0x%1</source>
        <translation>Unerwartete Versionsantwort: 0x%1</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="297" />
        <source>Failed to send the enter-IAP-mode command</source>
        <translation>Befehl zum Wechsel in den IAP-Modus konnte nicht gesendet werden</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="332" />
        <source>The firmware version cannot be read on the USB-UART (serial) channel</source>
        <translation>Die Firmware-Version kann über den USB-UART-Kanal (seriell) nicht gelesen werden</translation>
    </message>
</context>
<context>
    <name>FirmwareImage</name>
    <message>
        <location filename="../src/firmwareimage.cpp" line="87" />
        <source>Invalid HEX file: cannot parse line %1</source>
        <translation>Ungültige HEX-Datei: Zeile %1 kann nicht gelesen werden</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="92" />
        <source>Invalid HEX file: line %1 is too short</source>
        <translation>Ungültige HEX-Datei: Zeile %1 ist zu kurz</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="101" />
        <source>HEX checksum error on line %1 (0x%2)</source>
        <translation>HEX-Prüfsummenfehler in Zeile %1 (0x%2)</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="109" />
        <source>Invalid HEX file: data length mismatch on line %1</source>
        <translation>Ungültige HEX-Datei: Datenlänge stimmt in Zeile %1 nicht</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="163" />
        <source>HEX file contains no valid data record</source>
        <translation>Die HEX-Datei enthält keinen gültigen Datensatz</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="183" />
        <source>HEX address range out of bounds: 0x%1 - 0x%2</source>
        <translation>HEX-Adressbereich außerhalb der Grenzen: 0x%1 - 0x%2</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="222" />
        <source>Cannot open firmware file: %1</source>
        <translation>Firmware-Datei kann nicht geöffnet werden: %1</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="230" />
        <source>Firmware file is empty</source>
        <translation>Die Firmware-Datei ist leer</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="265" />
        <source>%1 B</source>
        <translation>%1 B</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="267" />
        <source>%1 KB (%2 bytes)</source>
        <translation>%1 KB (%2 Bytes)</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="270" />
        <source>%1 MB (%2 bytes)</source>
        <translation>%1 MB (%2 Bytes)</translation>
    </message>
</context>
<context>
    <name>IapCtl</name>
    <message>
        <location filename="../src/iapctl.cpp" line="53" />
        <source>Unexpected answer from the bootloader: 0x%1</source>
        <translation>Unerwartete Antwort vom Bootloader: 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="64" />
        <source>The bootloader did not answer (timeout)</source>
        <translation>Der Bootloader hat nicht geantwortet (Zeitüberschreitung)</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="78" />
        <source>Failed to initialize hidapi</source>
        <translation>hidapi konnte nicht initialisiert werden</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="84" />
        <source>No IAP device found (VID:0x%1 PID:0x%2).
These commands only work while the board sits in the bootloader.</source>
        <translation>Kein IAP-Gerät gefunden (VID:0x%1 PID:0x%2).
Diese Befehle funktionieren nur, solange sich die Platine im Bootloader befindet.</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="115" />
        <source>Failed to send command 0x%1 to the bootloader</source>
        <translation>Befehl 0x%1 konnte nicht an den Bootloader gesendet werden</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="129" />
        <source>The bootloader refused the request (error code %1)</source>
        <translation>Der Bootloader hat die Anfrage abgelehnt (Fehlercode %1)</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="163" />
        <source>Slot number out of range (0..%1)</source>
        <translation>Slot-Nummer außerhalb des Bereichs (0..%1)</translation>
    </message>
</context>
<context>
    <name>IapWorker</name>
    <message>
        <location filename="../src/iapworker.cpp" line="32" />
        <source>Unknown error</source>
        <translation>Unbekannter Fehler</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="82" />
        <source>Failed to initialize hidapi</source>
        <translation>hidapi konnte nicht initialisiert werden</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="92" />
        <source>Cancelled while waiting for the IAP device</source>
        <translation>Abgebrochen beim Warten auf das IAP-Gerät</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="99" />
        <source>Connected to IAP device (VID:0x%1 PID:0x%2)</source>
        <translation>Mit IAP-Gerät verbunden (VID:0x%1 PID:0x%2)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="106" />
        <source>Waiting for the IAP device (VID:0x%1 PID:0x%2) ...</source>
        <translation>Warten auf das IAP-Gerät (VID:0x%1 PID:0x%2) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="113" />
        <source>IAP device not found after waiting %1 seconds</source>
        <translation>IAP-Gerät nach %1 Sekunden nicht gefunden</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="141" />
        <source>Write cancelled</source>
        <translation>Schreiben abgebrochen</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="155" />
        <source>HID write failed: %1</source>
        <translation>HID-Schreiben fehlgeschlagen: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="160" />
        <source>HID write timed out (%1 ms)</source>
        <translation>Zeitüberschreitung beim HID-Schreiben (%1 ms)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="175" />
        <source>Read cancelled</source>
        <translation>Lesen abgebrochen</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="195" />
        <source>HID read failed: %1</source>
        <translation>HID-Lesen fehlgeschlagen: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="211" />
        <location filename="../src/iapworker.cpp" line="267" />
        <location filename="../src/iapworker.cpp" line="324" />
        <location filename="../src/iapworker.cpp" line="397" />
        <source>Upgrade cancelled</source>
        <translation>Aktualisierung abgebrochen</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="216" />
        <source>The device is in use by another program.
Close the program that currently uses the board (for example the logic analyzer software) and refresh.</source>
        <translation>Das Gerät wird von einem anderen Programm verwendet.
Schließen Sie das Programm, das die Platine gerade nutzt (zum Beispiel die Logikanalysator-Software), und aktualisieren Sie die Liste.</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="223" />
        <source>Device is already in IAP mode, skipping the mode switch</source>
        <translation>Gerät ist bereits im IAP-Modus, Moduswechsel wird übersprungen</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="233" />
        <source>No usable CH375 device index, cannot send the switch command</source>
        <translation>Kein nutzbarer CH375-Geräteindex, der Umschaltbefehl kann nicht gesendet werden</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="247" />
        <source>Opening %1 at the IAP baud rate %2 ...</source>
        <translation>Öffne %1 mit IAP-Baudrate %2 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="251" />
        <source>Sending enter-IAP-mode command over libusb (bus %1, address %2) ...</source>
        <translation>Sende Befehl zum Wechsel in den IAP-Modus über libusb (Bus %1, Adresse %2) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="255" />
        <source>Sending enter-IAP-mode command to device (CH375 index %1) ...</source>
        <translation>Sende Befehl zum Wechsel in den IAP-Modus an das Gerät (CH375-Index %1) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="259" />
        <source>Failed to enter IAP mode: %1</source>
        <translation>Wechsel in den IAP-Modus fehlgeschlagen: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="263" />
        <source>Command sent, waiting for the device to reset into a HID IAP device ...</source>
        <translation>Befehl gesendet, warte auf Neustart des Geräts als HID-IAP-Gerät ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="281" />
        <source>Erasing FLASH, start address 0x%1</source>
        <translation>FLASH wird gelöscht, Startadresse 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="282" />
        <source>Erasing FLASH ...</source>
        <translation>FLASH wird gelöscht ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="294" />
        <source>Failed to send the erase command</source>
        <translation>Löschbefehl konnte nicht gesendet werden</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="301" />
        <source>Erase response timed out</source>
        <translation>Zeitüberschreitung bei der Löschantwort</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="306" />
        <source>Erase failed, error code: %1</source>
        <translation>Löschen fehlgeschlagen, Fehlercode: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="310" />
        <source>Erase complete</source>
        <translation>Löschen abgeschlossen</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="316" />
        <source>Programming FLASH, %1 bytes in total</source>
        <translation>FLASH wird beschrieben, insgesamt %1 Bytes</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="317" />
        <location filename="../src/iapworker.cpp" line="372" />
        <source>Programming FLASH ... %1%</source>
        <translation>FLASH wird beschrieben ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="337" />
        <source>Failed to write data, offset %1</source>
        <translation>Daten konnten nicht geschrieben werden, Offset %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="347" />
        <source>Programming response timed out, offset %1</source>
        <translation>Zeitüberschreitung der Programmierantwort, Offset %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="355" />
        <source>Programming failed, error code %1, offset %2</source>
        <translation>Programmierung fehlgeschlagen, Fehlercode %1, Offset %2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="382" />
        <source>Programming complete</source>
        <translation>Programmierung abgeschlossen</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="388" />
        <source>Verifying FLASH ...</source>
        <translation>FLASH wird geprüft ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="389" />
        <location filename="../src/iapworker.cpp" line="448" />
        <source>Verifying FLASH ... %1%</source>
        <translation>FLASH wird geprüft ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="414" />
        <source>Failed to send the verify command, offset %1</source>
        <translation>Prüfbefehl konnte nicht gesendet werden, Offset %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="424" />
        <source>Verify response timed out, offset %1</source>
        <translation>Zeitüberschreitung der Prüfantwort, Offset %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="432" />
        <source>Verification failed, error code %1, address 0x%2</source>
        <translation>Prüfung fehlgeschlagen, Fehlercode %1, Adresse 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="451" />
        <source>Verification succeeded</source>
        <translation>Prüfung erfolgreich</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="457" />
        <source>Sending the upgrade-finish command ...</source>
        <translation>Sende Befehl zum Abschluss der Aktualisierung ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="458" />
        <source>Finishing upgrade ...</source>
        <translation>Aktualisierung wird abgeschlossen ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="466" />
        <source>Failed to send the finish command</source>
        <translation>Abschlussbefehl konnte nicht gesendet werden</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="475" />
        <source>Device confirmed the upgrade</source>
        <translation>Gerät hat die Aktualisierung bestätigt</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="477" />
        <source>Device has reset (no response is normal)</source>
        <translation>Gerät wurde neu gestartet (keine Antwort ist normal)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="492" />
        <source>Reading firmware file ...</source>
        <translation>Firmware-Datei wird gelesen ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="495" />
        <source>Failed to load firmware: %1</source>
        <translation>Firmware konnte nicht geladen werden: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="499" />
        <source>Firmware loaded: %1</source>
        <translation>Firmware geladen: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="500" />
        <source>  Format: %1, size: %2 bytes</source>
        <translation>  Format: %1, Größe: %2 Bytes</translation>
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
        <translation>  Adressbereich: 0x%1 - 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="506" />
        <source>  Checksum: 0x%1</source>
        <translation>  Prüfsumme: 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="509" />
        <source>Firmware data is empty</source>
        <translation>Die Firmware-Daten sind leer</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="522" />
        <source>Padded the image with %1 bytes of 0xFF (flash page alignment)</source>
        <translation>Abbild mit %1 Bytes 0xFF aufgefüllt (Ausrichtung auf die Flash-Seite)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="533" />
        <source>Starting upgrade ...</source>
        <translation>Aktualisierung wird gestartet ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="534" />
        <source>========== Firmware upgrade started %1 ==========</source>
        <translation>========== Firmware-Aktualisierung gestartet %1 ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="544" />
        <source>Failed to load the firmware file</source>
        <translation>Die Firmware-Datei konnte nicht geladen werden</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="549" />
        <source>Entering IAP mode ...</source>
        <translation>Wechsel in den IAP-Modus ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="551" />
        <source>Unable to enter IAP mode</source>
        <translation>Wechsel in den IAP-Modus nicht möglich</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="557" />
        <source>Device is now in IAP mode</source>
        <translation>Gerät ist jetzt im IAP-Modus</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="558" />
        <source>The device rebooted into IAP mode</source>
        <translation>Das Gerät wurde in den IAP-Modus neu gestartet</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="563" />
        <source>Looking for the IAP device ...</source>
        <translation>Suche nach dem IAP-Gerät ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="565" />
        <source>No device in IAP mode found</source>
        <translation>Kein Gerät im IAP-Modus gefunden</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="568" />
        <source>Connected to the IAP device</source>
        <translation>Mit dem IAP-Gerät verbunden</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="573" />
        <source>Failed to erase FLASH</source>
        <translation>FLASH konnte nicht gelöscht werden</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="581" />
        <source>Failed to program FLASH</source>
        <translation>FLASH konnte nicht beschrieben werden</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="590" />
        <source>Failed to verify FLASH</source>
        <translation>FLASH konnte nicht geprüft werden</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="599" />
        <location filename="../src/iapworker.cpp" line="601" />
        <source>Slot programmed</source>
        <translation>Slot programmiert</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="600" />
        <source>Slot programmed, the board stays in the bootloader</source>
        <translation>Slot programmiert, die Platine bleibt im Bootloader</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="607" />
        <source>Failed to finish the upgrade</source>
        <translation>Die Aktualisierung konnte nicht abgeschlossen werden</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="613" />
        <source>Upgrade complete</source>
        <translation>Aktualisierung abgeschlossen</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="614" />
        <source>========== Firmware upgrade succeeded ==========</source>
        <translation>========== Firmware-Aktualisierung erfolgreich ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="615" />
        <source>Firmware upgrade succeeded, the device will restart</source>
        <translation>Firmware-Aktualisierung erfolgreich, das Gerät wird neu gestartet</translation>
    </message>
</context>
<context>
    <name>LanguageManager</name>
    <message>
        <location filename="../src/languagemanager.cpp" line="125" />
        <source>Follow System(&amp;A)</source>
        <translation>Systemeinstellung folgen(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="126" />
        <source>English(&amp;E)</source>
        <translation>Englisch(&amp;E)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="127" />
        <source>Simplified Chinese(&amp;C)</source>
        <translation>Chinesisch (vereinfacht)(&amp;C)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="128" />
        <source>Russian(&amp;R)</source>
        <translation>Russisch(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="129" />
        <source>German(&amp;G)</source>
        <translation>Deutsch(&amp;G)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="130" />
        <source>Spanish(&amp;S)</source>
        <translation>Spanisch(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="152" />
        <source>Simplified Chinese</source>
        <translation>Chinesisch (vereinfacht)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="154" />
        <source>Russian</source>
        <translation>Russisch</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="156" />
        <source>German</source>
        <translation>Deutsch</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="158" />
        <source>Spanish</source>
        <translation>Spanisch</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="161" />
        <source>English</source>
        <translation>Englisch</translation>
    </message>
</context>
<context>
    <name>LibusbDev</name>
    <message>
        <location filename="../src/libusbdev.cpp" line="83" />
        <source>Cannot open the USB device (libusb error %1). The board must be bound to a generic USB driver (WinUSB on Windows) and must not be in use by another program.</source>
        <translation>Das USB-Gerät kann nicht geöffnet werden (libusb-Fehler %1). Die Platine muss an einen generischen USB-Treiber gebunden sein (WinUSB unter Windows) und darf nicht von einem anderen Programm verwendet werden.</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="98" />
        <source>Cannot claim the USB interface (libusb error %1). Close other programs that use the device and try again.</source>
        <translation>Die USB-Schnittstelle kann nicht belegt werden (libusb-Fehler %1). Schließen Sie andere Programme, die das Gerät nutzen, und versuchen Sie es erneut.</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="124" />
        <source>Failed to send command 0x%1 (libusb error %2)</source>
        <translation>Befehl 0x%1 konnte nicht gesendet werden (libusb-Fehler %2)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="140" />
        <source>The device did not answer command 0x%1 (libusb error %2)</source>
        <translation>Das Gerät hat nicht auf Befehl 0x%1 geantwortet (libusb-Fehler %2)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="158" />
        <source>libusb is not available</source>
        <translation>libusb ist nicht verfügbar</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="166" />
        <source>Unable to initialise libusb (error %1)</source>
        <translation>libusb konnte nicht initialisiert werden (Fehler %1)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="198" />
        <source>Failed to enumerate the USB devices (libusb error %1)</source>
        <translation>USB-Geräte konnten nicht aufgelistet werden (libusb-Fehler %1)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="281" />
        <location filename="../src/libusbdev.cpp" line="323" />
        <source>The device is no longer present (bus %1, address %2)</source>
        <translation>Das Gerät ist nicht mehr vorhanden (Bus %1, Adresse %2)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="305" />
        <source>Failed to send the enter-IAP-mode command</source>
        <translation>Befehl zum Wechsel in den IAP-Modus konnte nicht gesendet werden</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="346" />
        <source>Unexpected version response: 0x%1</source>
        <translation>Unerwartete Versionsantwort: 0x%1</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../src/mainwindow.cpp" line="85" />
        <source> (in use)</source>
        <translation> (belegt)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="492" />
        <source>CH32H417 Logic Analyzer Firmware Upgrade Tool</source>
        <translation>CH32H417 Logikanalysator – Firmware-Aktualisierung</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="495" />
        <source>Device</source>
        <translation>Gerät</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="496" />
        <source>Firmware File</source>
        <translation>Firmware-Datei</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="497" />
        <source>IAP Settings</source>
        <translation>IAP-Einstellungen</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="500" />
        <source>Device List:</source>
        <translation>Geräteliste:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="501" />
        <source>Device Status:</source>
        <translation>Gerätestatus:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="502" />
        <source>Firmware Version:</source>
        <translation>Firmware-Version:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="503" />
        <source>File Path:</source>
        <translation>Dateipfad:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="504" />
        <source>Firmware Info:</source>
        <translation>Firmware-Info:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="507" />
        <source>BIN Base Address: 0x</source>
        <translation>BIN-Basisadresse: 0x</translation>
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
        <translation>Standard: VID=0x1A86 PID=0xFE17</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="514" />
        <source>Refresh(&amp;R)</source>
        <translation>Aktualisieren(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="515" />
        <source>Browse(&amp;B)...</source>
        <translation>Durchsuchen(&amp;B)...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="520" />
        <source>Programming start address for .bin files (hexadecimal, e.g. 08006000). On the WeAct Studio Logic Analyzer V2 pick one of the three APP slots: slot 0 = logic analyzer, slot 1 = USB to UART + DAP, slot 2 = example.</source>
        <translation>Startadresse zum Beschreiben von .bin-Dateien (hexadezimal, z. B. 08006000).
Beim WeAct Studio Logic Analyzer V2 einen der drei APP-Slots wählen: Slot 0 = Logikanalysator, Slot 1 = USB zu UART + DAP, Slot 2 = Beispiel.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="523" />
        <source>Select or drop a .hex / .bin firmware file</source>
        <translation>.hex-/.bin-Firmware-Datei auswählen oder ablegen</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="525" />
        <source>Upgrade Log</source>
        <translation>Aktualisierungsprotokoll</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="526" />
        <source>Reboot into:</source>
        <translation>Neu starten in:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="528" />
        <source>Slot %1</source>
        <translation>Slot %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="530" />
        <source>Make slot %1 (0x%2) the active one and boot it</source>
        <translation>Slot %1 (0x%2) aktivieren und starten</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="533" />
        <source>Start Upgrade(&amp;S)</source>
        <translation>Aktualisierung starten(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="534" />
        <location filename="../src/mainwindow.cpp" line="543" />
        <source>Exit(&amp;X)</source>
        <translation>Beenden(&amp;X)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="541" />
        <source>File(&amp;F)</source>
        <translation>Datei(&amp;F)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="542" />
        <source>Open Firmware(&amp;O)...</source>
        <translation>Firmware öffnen(&amp;O)...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="544" />
        <source>Tools(&amp;T)</source>
        <translation>Werkzeuge(&amp;T)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="545" />
        <source>Refresh Devices(&amp;R)</source>
        <translation>Geräte aktualisieren(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="546" />
        <source>Reboot into Active Slot(&amp;B)</source>
        <translation>In aktiven Slot neu starten(&amp;B)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="547" />
        <source>Switch APP Slot(&amp;S)</source>
        <translation>APP-Slot wechseln(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="549" />
        <location filename="../src/mainwindow.cpp" line="751" />
        <source>Slot %1: 0x%2</source>
        <translation>Slot %1: 0x%2</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="553" />
        <source>Clear Log(&amp;L)</source>
        <translation>Protokoll leeren(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="554" />
        <source>View(&amp;V)</source>
        <translation>Ansicht(&amp;V)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="555" />
        <source>Language(&amp;L)</source>
        <translation>Sprache(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="556" />
        <source>Help(&amp;H)</source>
        <translation>Hilfe(&amp;H)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="557" />
        <source>About(&amp;A)</source>
        <translation>Über(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="717" />
        <source>Hexadecimal, e.g. 08006000</source>
        <translation>Hexadezimal, z. B. 08006000</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="834" />
        <source>(No device found)</source>
        <translation>(Kein Gerät gefunden)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="836" />
        <source>No device found</source>
        <translation>Kein Gerät gefunden</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="952" />
        <source>&lt;font color='%1'&gt;Connected (application mode, %2 channel)&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Verbunden (Anwendungsmodus, Kanal %2)&lt;/font&gt;</translation>
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
        <translation>Die Firmware-Version kann über den USB-UART-Kanal (seriell) nicht gelesen werden</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="965" />
        <source>Read failed</source>
        <translation>Lesen fehlgeschlagen</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="968" />
        <source>Software version: v%1  Hardware version: v%2</source>
        <translation>Softwareversion: v%1  Hardwareversion: v%2</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="975" />
        <source>&lt;font color='%1'&gt;Connected (IAP upgrade mode)&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Verbunden (IAP-Aktualisierungsmodus)&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="982" />
        <source>&lt;font color='%1'&gt;Device in use by another program&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Gerät wird von einem anderen Programm verwendet&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="989" />
        <source>&lt;font color='%1'&gt;No device found&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Kein Gerät gefunden&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1028" />
        <source>Leave &amp;IAP</source>
        <translation>&amp;IAP verlassen</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1029" />
        <source>Reboot into &amp;IAP</source>
        <translation>In &amp;IAP neu starten</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1033" />
        <source>Reboot the board and run the active APP slot again</source>
        <translation>Platine neu starten und den aktiven APP-Slot erneut ausführen</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1034" />
        <source>Reboot the board into its bootloader (IAP mode)</source>
        <translation>Platine in den Bootloader (IAP-Modus) neu starten</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1044" />
        <source>Rebooting the device out of IAP mode ...</source>
        <translation>Gerät wird aus dem IAP-Modus neu gestartet ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1052" />
        <source>Leaving IAP failed: %1</source>
        <translation>Verlassen des IAP-Modus fehlgeschlagen: %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1053" />
        <location filename="../src/mainwindow.cpp" line="1145" />
        <location filename="../src/mainwindow.cpp" line="1188" />
        <location filename="../src/mainwindow.cpp" line="1445" />
        <location filename="../src/mainwindow.cpp" line="1450" />
        <location filename="../src/mainwindow.cpp" line="1470" />
        <source>Failed</source>
        <translation>Fehlgeschlagen</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1057" />
        <location filename="../src/mainwindow.cpp" line="1149" />
        <source>Reboot request accepted, the device restarts ...</source>
        <translation>Neustartanforderung angenommen, das Gerät startet neu ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1102" />
        <source>Not available while an upgrade is running</source>
        <translation>Während einer Aktualisierung nicht verfügbar</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1105" />
        <source>Needs a board that sits in the IAP bootloader</source>
        <translation>Erfordert eine Platine im IAP-Bootloader</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1115" />
        <location filename="../src/mainwindow.cpp" line="1123" />
        <source>Not Available</source>
        <translation>Nicht verfügbar</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1116" />
        <source>Wait for the running upgrade to finish.</source>
        <translation>Warten Sie, bis die laufende Aktualisierung beendet ist.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1120" />
        <source>This command needs a board that sits in the IAP bootloader, the current device is in application mode.</source>
        <translation>Dieser Befehl erfordert eine Platine im IAP-Bootloader, das aktuelle Gerät ist im Anwendungsmodus.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1124" />
        <source>No CH32H417 device in IAP mode found.
These commands need a board that sits in the bootloader (power-cycle it with the button held).</source>
        <translation>Kein CH32H417-Gerät im IAP-Modus gefunden.
Diese Befehle erfordern eine Platine im Bootloader (schalten Sie die Stromversorgung bei gedrückter Taste aus und wieder ein).</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1136" />
        <source>Rebooting the device into its active slot ...</source>
        <translation>Gerät wird in den aktiven Slot neu gestartet ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1144" />
        <source>Reboot failed: %1</source>
        <translation>Neustart fehlgeschlagen: %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1178" />
        <source>Switching to APP slot %1 (0x%2) ...</source>
        <translation>Wechsle zu APP-Slot %1 (0x%2) ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1187" />
        <source>Slot switch failed: %1</source>
        <translation>Slot-Wechsel fehlgeschlagen: %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1192" />
        <source>Slot %1 is now active, the device reboots into it ...</source>
        <translation>Slot %1 ist jetzt aktiv, das Gerät startet darin neu ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1261" />
        <source>Select Firmware File</source>
        <translation>Firmware-Datei auswählen</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1263" />
        <source>Firmware Files (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binary Files (*.bin);;All Files (*.*)</source>
        <translation>Firmware-Dateien (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binärdateien (*.bin);;Alle Dateien (*.*)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1281" />
        <source>&lt;font color='%1'&gt;No valid firmware file selected&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Keine gültige Firmware-Datei ausgewählt&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1290" />
        <source>&lt;font color='%1'&gt;%2&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;%2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1295" />
        <source>%1  Size: %2  Address: 0x%3 - 0x%4  Checksum: 0x%5</source>
        <translation>%1  Größe: %2  Adresse: 0x%3 - 0x%4  Prüfsumme: 0x%5</translation>
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
        <translation>Hinweis</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1331" />
        <source>Please select a valid firmware file first.</source>
        <translation>Bitte wählen Sie zuerst eine gültige Firmware-Datei.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1337" />
        <source>No Device Found</source>
        <translation>Kein Gerät gefunden</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1338" />
        <source>No CH32H417 device was detected.

If the device is already in IAP mode (for example powered up with the button held down), you can continue;
otherwise please connect the device first.

Continue?</source>
        <translation>Es wurde kein CH32H417-Gerät erkannt.

Wenn das Gerät bereits im IAP-Modus ist (zum Beispiel mit gedrückter Taste eingeschaltet), können Sie fortfahren;
andernfalls schließen Sie das Gerät bitte zuerst an.

Fortfahren?</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1350" />
        <source>Firmware Error</source>
        <translation>Firmware-Fehler</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1383" />
        <source>Preparing ...</source>
        <translation>Vorbereitung ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1388" />
        <source>Target device: IAP HID (VID:0x%1 PID:0x%2)</source>
        <translation>Zielgerät: IAP HID (VID:0x%1 PID:0x%2)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1392" />
        <source>Target device: serial (COM port %1)</source>
        <translation>Zielgerät: seriell (COM-Port %1)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1394" />
        <source>Target device: libusb (bus %1, address %2)</source>
        <translation>Zielgerät: libusb (Bus %1, Adresse %2)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1397" />
        <source>Target device: CH375 #%1</source>
        <translation>Zielgerät: CH375 #%1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1440" />
        <source>Device is in IAP Mode</source>
        <translation>Gerät ist im IAP-Modus</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1447" />
        <location filename="../src/mainwindow.cpp" line="1467" />
        <location filename="../src/mainwindow.cpp" line="1472" />
        <source>Please power-cycle the device (disconnect and reconnect the USB cable or the power supply) and run the upgrade again.</source>
        <translation>Schalten Sie die Stromversorgung des Geräts aus und wieder ein (USB-Kabel oder Netzteil trennen und wieder verbinden) und führen Sie die Aktualisierung erneut aus.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1458" />
        <location filename="../src/mainwindow.cpp" line="1489" />
        <source>Upgrade Complete</source>
        <translation>Aktualisierung abgeschlossen</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1460" />
        <source>Complete</source>
        <translation>Fertig</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1461" />
        <source>Firmware upgrade succeeded!
The device will restart and run the new firmware.</source>
        <translation>Firmware-Aktualisierung erfolgreich!
Das Gerät wird neu gestartet und führt die neue Firmware aus.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1465" />
        <location filename="../src/mainwindow.cpp" line="1492" />
        <source>Upgrade Failed</source>
        <translation>Aktualisierung fehlgeschlagen</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1496" />
        <source>Ready</source>
        <translation>Bereit</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1558" />
        <source>About</source>
        <translation>Über</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1562" />
        <source>&lt;h3&gt;CH32H417 Logic Analyzer&lt;br&gt;Firmware Upgrade Tool&lt;/h3&gt;&lt;p&gt;Version: %1&lt;/p&gt;&lt;p&gt;&lt;b&gt;WeAct Studio&lt;/b&gt;&lt;br&gt;Copyright (C) 2026 WeAct Studio. All rights reserved.&lt;/p&gt;&lt;p&gt;This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.&lt;/p&gt;&lt;p&gt;License: GPL-3.0-or-later&lt;br&gt;&lt;a href='https://www.gnu.org/licenses/gpl-3.0.html'&gt;https://www.gnu.org/licenses/gpl-3.0.html&lt;/a&gt;&lt;/p&gt;&lt;p&gt;Built with Qt %2, statically compiled with MSYS2 (MINGW64).&lt;/p&gt;&lt;p&gt;Upgrade sequence: the enter-IAP command goes out over whichever USB channel the board is on - CH375, libusb / WinUSB, or the COM port of the USB-to-UART firmware. The board then resets into a HID IAP device, followed by erase / program / verify / finish.&lt;/p&gt;&lt;p&gt;A board that already sits in IAP mode can also be rebooted into its active slot, or switched to another APP slot, without downloading anything.&lt;/p&gt;&lt;p&gt;Windows needs one driver for the board: the WCH CH375 driver, or WinUSB when the board is bound to libusb.&lt;/p&gt;</source>
        <translation>&lt;h3&gt;CH32H417 Logikanalysator&lt;br&gt;Firmware-Aktualisierungswerkzeug&lt;/h3&gt;&lt;p&gt;Version: %1&lt;/p&gt;&lt;p&gt;&lt;b&gt;WeAct Studio&lt;/b&gt;&lt;br&gt;Copyright (C) 2026 WeAct Studio. Alle Rechte vorbehalten.&lt;/p&gt;&lt;p&gt;Dieses Programm ist freie Software: Sie können es unter den Bedingungen der GNU General Public License, wie von der Free Software Foundation veröffentlicht, weitergeben und/oder ändern, entweder gemäß Version 3 der Lizenz oder (nach Ihrer Wahl) jeder späteren Version. Die Veröffentlichung erfolgt in der Hoffnung, dass es nützlich ist, aber OHNE JEDE GEWÄHRLEISTUNG, sogar ohne die implizite Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK. Details finden Sie in der GNU General Public License.&lt;/p&gt;&lt;p&gt;Lizenz: GPL-3.0-or-later&lt;br&gt;&lt;a href='https://www.gnu.org/licenses/gpl-3.0.html'&gt;https://www.gnu.org/licenses/gpl-3.0.html&lt;/a&gt;&lt;/p&gt;&lt;p&gt;Erstellt mit Qt %2, statisch gelinkt mit MSYS2 (MINGW64).&lt;/p&gt;&lt;p&gt;Ablauf der Aktualisierung: Der Befehl zum Wechsel in den IAP-Modus geht über den USB-Kanal, an dem die Platine hängt – CH375, libusb / WinUSB oder der COM-Port der USB-UART-Firmware. Danach startet die Platine als HID-IAP-Gerät neu, gefolgt von Löschen / Beschreiben / Prüfen / Abschließen.&lt;/p&gt;&lt;p&gt;Eine Platine, die bereits im IAP-Modus ist, kann auch ohne Firmware-Download in ihren aktiven Slot neu gestartet oder in einen anderen APP-Slot umgeschaltet werden.&lt;/p&gt;&lt;p&gt;Windows benötigt einen Treiber für die Platine: den WCH CH375-Treiber oder WinUSB, wenn die Platine an libusb gebunden ist.&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1620" />
        <source>Upgrade in Progress</source>
        <translation>Aktualisierung läuft</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1621" />
        <source>An upgrade is running; exiting now may corrupt the device firmware.
Are you sure you want to exit?</source>
        <translation>Eine Aktualisierung läuft; ein Abbruch jetzt kann die Geräte-Firmware beschädigen.
Möchten Sie das Programm wirklich beenden?</translation>
    </message>
</context>
<context>
    <name>SerialDev</name>
    <message>
        <location filename="../src/serialdev.cpp" line="104" />
        <source>Serial port enumeration is only supported on Windows</source>
        <translation>Das Auflisten von COM-Ports wird nur unter Windows unterstützt</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="111" />
        <source>Cannot enumerate the COM ports (error %1)</source>
        <translation>COM-Ports können nicht aufgelistet werden (Fehler %1)</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="233" />
        <source>Serial port access is only supported on Windows</source>
        <translation>Der Zugriff auf COM-Ports wird nur unter Windows unterstützt</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="245" />
        <source>%1 is open in another program.
Close the program (for example a serial terminal) and retry.</source>
        <translation>%1 ist in einem anderen Programm geöffnet.
Schließen Sie das Programm (zum Beispiel ein serielles Terminal) und versuchen Sie es erneut.</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="251" />
        <source>Cannot open %1 (error %2)</source>
        <translation>%1 kann nicht geöffnet werden (Fehler %2)</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="262" />
        <source>Cannot query the settings of %1 (error %2)</source>
        <translation>Die Einstellungen von %1 können nicht abgefragt werden (Fehler %2)</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="305" />
        <source>Cannot set the IAP baud rate on %1 (error %2)</source>
        <translation>Die IAP-Baudrate kann auf %1 nicht gesetzt werden (Fehler %2)</translation>
    </message>
</context>
<context>
    <name>ThemeManager</name>
    <message>
        <location filename="../src/thememanager.cpp" line="166" />
        <source>Follow System(&amp;S)</source>
        <translation>Systemeinstellung folgen(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/thememanager.cpp" line="168" />
        <source>Light(&amp;L)</source>
        <translation>Hell(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/thememanager.cpp" line="171" />
        <source>Dark(&amp;D)</source>
        <translation>Dunkel(&amp;D)</translation>
    </message>
</context>
</TS>