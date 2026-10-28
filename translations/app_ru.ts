<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ru_RU">
<context>
    <name>Ch375Dev</name>
    <message>
        <location filename="../src/ch375dev.cpp" line="80" />
        <source>The device is in use by another program.
Close the program that currently uses the board (for example the logic analyzer software) and refresh.</source>
        <translation>Устройство занято другой программой.
Закройте программу, использующую плату (например, программу логического анализатора), и обновите список.</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="102" />
        <source>Unable to load CH375DLL64.DLL / CH375DLL.DLL.
Make sure the CH375 driver is installed and that the driver DLL is placed next to this program or in a directory on the system search path.</source>
        <translation>Не удалось загрузить CH375DLL64.DLL / CH375DLL.DLL.
Убедитесь, что драйвер CH375 установлен, а DLL драйвера находится рядом с программой или в каталоге системного пути поиска.</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="211" />
        <location filename="../src/ch375dev.cpp" line="268" />
        <source>Invalid device index</source>
        <translation>Недопустимый индекс устройства</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="222" />
        <location filename="../src/ch375dev.cpp" line="279" />
        <source>Cannot open CH375 device (index %1)</source>
        <translation>Не удалось открыть устройство CH375 (индекс %1)</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="248" />
        <source>Failed to read firmware version (device did not respond)</source>
        <translation>Не удалось прочитать версию прошивки (устройство не отвечает)</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="255" />
        <source>Unexpected version response: 0x%1</source>
        <translation>Неожиданный ответ о версии: 0x%1</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="297" />
        <source>Failed to send the enter-IAP-mode command</source>
        <translation>Не удалось отправить команду перехода в режим IAP</translation>
    </message>
    <message>
        <location filename="../src/ch375dev.cpp" line="332" />
        <source>The firmware version cannot be read on the USB-UART (serial) channel</source>
        <translation>Версию прошивки нельзя прочитать через канал USB-UART (последовательный)</translation>
    </message>
</context>
<context>
    <name>FirmwareImage</name>
    <message>
        <location filename="../src/firmwareimage.cpp" line="87" />
        <source>Invalid HEX file: cannot parse line %1</source>
        <translation>Некорректный HEX-файл: не удалось разобрать строку %1</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="92" />
        <source>Invalid HEX file: line %1 is too short</source>
        <translation>Некорректный HEX-файл: строка %1 слишком коротка</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="101" />
        <source>HEX checksum error on line %1 (0x%2)</source>
        <translation>Ошибка контрольной суммы HEX в строке %1 (0x%2)</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="109" />
        <source>Invalid HEX file: data length mismatch on line %1</source>
        <translation>Некорректный HEX-файл: несоответствие длины данных в строке %1</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="163" />
        <source>HEX file contains no valid data record</source>
        <translation>HEX-файл не содержит ни одной записи данных</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="183" />
        <source>HEX address range out of bounds: 0x%1 - 0x%2</source>
        <translation>Диапазон адресов HEX вне допустимых пределов: 0x%1 - 0x%2</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="222" />
        <source>Cannot open firmware file: %1</source>
        <translation>Не удалось открыть файл прошивки: %1</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="230" />
        <source>Firmware file is empty</source>
        <translation>Файл прошивки пуст</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="265" />
        <source>%1 B</source>
        <translation>%1 Б</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="267" />
        <source>%1 KB (%2 bytes)</source>
        <translation>%1 КБ (%2 байт)</translation>
    </message>
    <message>
        <location filename="../src/firmwareimage.cpp" line="270" />
        <source>%1 MB (%2 bytes)</source>
        <translation>%1 МБ (%2 байт)</translation>
    </message>
</context>
<context>
    <name>IapCtl</name>
    <message>
        <location filename="../src/iapctl.cpp" line="53" />
        <source>Unexpected answer from the bootloader: 0x%1</source>
        <translation>Неожиданный ответ загрузчика: 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="64" />
        <source>The bootloader did not answer (timeout)</source>
        <translation>Загрузчик не ответил (тайм-аут)</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="78" />
        <source>Failed to initialize hidapi</source>
        <translation>Не удалось инициализировать hidapi</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="84" />
        <source>No IAP device found (VID:0x%1 PID:0x%2).
These commands only work while the board sits in the bootloader.</source>
        <translation>Устройство IAP не найдено (VID:0x%1 PID:0x%2).
Эти команды работают только когда плата находится в загрузчике.</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="115" />
        <source>Failed to send command 0x%1 to the bootloader</source>
        <translation>Не удалось отправить команду 0x%1 загрузчику</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="129" />
        <source>The bootloader refused the request (error code %1)</source>
        <translation>Загрузчик отклонил запрос (код ошибки %1)</translation>
    </message>
    <message>
        <location filename="../src/iapctl.cpp" line="163" />
        <source>Slot number out of range (0..%1)</source>
        <translation>Номер слота вне диапазона (0..%1)</translation>
    </message>
</context>
<context>
    <name>IapWorker</name>
    <message>
        <location filename="../src/iapworker.cpp" line="32" />
        <source>Unknown error</source>
        <translation>Неизвестная ошибка</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="82" />
        <source>Failed to initialize hidapi</source>
        <translation>Не удалось инициализировать hidapi</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="92" />
        <source>Cancelled while waiting for the IAP device</source>
        <translation>Отменено во время ожидания устройства IAP</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="99" />
        <source>Connected to IAP device (VID:0x%1 PID:0x%2)</source>
        <translation>Подключено к устройству IAP (VID:0x%1 PID:0x%2)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="106" />
        <source>Waiting for the IAP device (VID:0x%1 PID:0x%2) ...</source>
        <translation>Ожидание устройства IAP (VID:0x%1 PID:0x%2) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="113" />
        <source>IAP device not found after waiting %1 seconds</source>
        <translation>Устройство IAP не найдено после ожидания %1 с</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="141" />
        <source>Write cancelled</source>
        <translation>Запись отменена</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="155" />
        <source>HID write failed: %1</source>
        <translation>Ошибка записи HID: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="160" />
        <source>HID write timed out (%1 ms)</source>
        <translation>Тайм-аут записи HID (%1 мс)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="175" />
        <source>Read cancelled</source>
        <translation>Чтение отменено</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="195" />
        <source>HID read failed: %1</source>
        <translation>Ошибка чтения HID: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="211" />
        <location filename="../src/iapworker.cpp" line="267" />
        <location filename="../src/iapworker.cpp" line="324" />
        <location filename="../src/iapworker.cpp" line="397" />
        <source>Upgrade cancelled</source>
        <translation>Обновление отменено</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="216" />
        <source>The device is in use by another program.
Close the program that currently uses the board (for example the logic analyzer software) and refresh.</source>
        <translation>Устройство занято другой программой.
Закройте программу, использующую плату (например, программу логического анализатора), и обновите список.</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="223" />
        <source>Device is already in IAP mode, skipping the mode switch</source>
        <translation>Устройство уже в режиме IAP, переключение режима пропущено</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="233" />
        <source>No usable CH375 device index, cannot send the switch command</source>
        <translation>Нет доступного индекса устройства CH375, команду переключения отправить нельзя</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="247" />
        <source>Opening %1 at the IAP baud rate %2 ...</source>
        <translation>Открытие %1 со скоростью IAP %2 ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="251" />
        <source>Sending enter-IAP-mode command over libusb (bus %1, address %2) ...</source>
        <translation>Отправка команды перехода в режим IAP через libusb (шина %1, адрес %2) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="255" />
        <source>Sending enter-IAP-mode command to device (CH375 index %1) ...</source>
        <translation>Отправка устройству команды перехода в режим IAP (индекс CH375 %1) ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="259" />
        <source>Failed to enter IAP mode: %1</source>
        <translation>Не удалось перейти в режим IAP: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="263" />
        <source>Command sent, waiting for the device to reset into a HID IAP device ...</source>
        <translation>Команда отправлена, ожидание перезагрузки устройства в HID-устройство IAP ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="281" />
        <source>Erasing FLASH, start address 0x%1</source>
        <translation>Стирание FLASH, начальный адрес 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="282" />
        <source>Erasing FLASH ...</source>
        <translation>Стирание FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="294" />
        <source>Failed to send the erase command</source>
        <translation>Не удалось отправить команду стирания</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="301" />
        <source>Erase response timed out</source>
        <translation>Тайм-аут ответа на стирание</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="306" />
        <source>Erase failed, error code: %1</source>
        <translation>Ошибка стирания, код ошибки: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="310" />
        <source>Erase complete</source>
        <translation>Стирание завершено</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="316" />
        <source>Programming FLASH, %1 bytes in total</source>
        <translation>Программирование FLASH, всего %1 байт</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="317" />
        <location filename="../src/iapworker.cpp" line="372" />
        <source>Programming FLASH ... %1%</source>
        <translation>Программирование FLASH ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="337" />
        <source>Failed to write data, offset %1</source>
        <translation>Не удалось записать данные, смещение %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="347" />
        <source>Programming response timed out, offset %1</source>
        <translation>Тайм-аут ответа при программировании, смещение %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="355" />
        <source>Programming failed, error code %1, offset %2</source>
        <translation>Ошибка программирования, код %1, смещение %2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="382" />
        <source>Programming complete</source>
        <translation>Программирование завершено</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="388" />
        <source>Verifying FLASH ...</source>
        <translation>Проверка FLASH ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="389" />
        <location filename="../src/iapworker.cpp" line="448" />
        <source>Verifying FLASH ... %1%</source>
        <translation>Проверка FLASH ... %1%</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="414" />
        <source>Failed to send the verify command, offset %1</source>
        <translation>Не удалось отправить команду проверки, смещение %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="424" />
        <source>Verify response timed out, offset %1</source>
        <translation>Тайм-аут ответа проверки, смещение %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="432" />
        <source>Verification failed, error code %1, address 0x%2</source>
        <translation>Проверка не пройдена, код ошибки %1, адрес 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="451" />
        <source>Verification succeeded</source>
        <translation>Проверка успешна</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="457" />
        <source>Sending the upgrade-finish command ...</source>
        <translation>Отправка команды завершения обновления ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="458" />
        <source>Finishing upgrade ...</source>
        <translation>Завершение обновления ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="466" />
        <source>Failed to send the finish command</source>
        <translation>Не удалось отправить команду завершения</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="475" />
        <source>Device confirmed the upgrade</source>
        <translation>Устройство подтвердило обновление</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="477" />
        <source>Device has reset (no response is normal)</source>
        <translation>Устройство перезагрузилось (отсутствие ответа — норма)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="492" />
        <source>Reading firmware file ...</source>
        <translation>Чтение файла прошивки ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="495" />
        <source>Failed to load firmware: %1</source>
        <translation>Не удалось загрузить прошивку: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="499" />
        <source>Firmware loaded: %1</source>
        <translation>Прошивка загружена: %1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="500" />
        <source>  Format: %1, size: %2 bytes</source>
        <translation>  Формат: %1, размер: %2 байт</translation>
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
        <translation>  Диапазон адресов: 0x%1 - 0x%2</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="506" />
        <source>  Checksum: 0x%1</source>
        <translation>  Контрольная сумма: 0x%1</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="509" />
        <source>Firmware data is empty</source>
        <translation>Данные прошивки пусты</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="522" />
        <source>Padded the image with %1 bytes of 0xFF (flash page alignment)</source>
        <translation>Образ дополнен %1 байтами 0xFF (выравнивание по странице flash)</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="533" />
        <source>Starting upgrade ...</source>
        <translation>Начало обновления ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="534" />
        <source>========== Firmware upgrade started %1 ==========</source>
        <translation>========== Начало обновления прошивки %1 ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="544" />
        <source>Failed to load the firmware file</source>
        <translation>Не удалось загрузить файл прошивки</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="549" />
        <source>Entering IAP mode ...</source>
        <translation>Переход в режим IAP ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="551" />
        <source>Unable to enter IAP mode</source>
        <translation>Не удалось перейти в режим IAP</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="557" />
        <source>Device is now in IAP mode</source>
        <translation>Устройство теперь в режиме IAP</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="558" />
        <source>The device rebooted into IAP mode</source>
        <translation>Устройство перезагрузилось в режим IAP</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="563" />
        <source>Looking for the IAP device ...</source>
        <translation>Поиск устройства IAP ...</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="565" />
        <source>No device in IAP mode found</source>
        <translation>Устройство в режиме IAP не найдено</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="568" />
        <source>Connected to the IAP device</source>
        <translation>Подключено к устройству IAP</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="573" />
        <source>Failed to erase FLASH</source>
        <translation>Не удалось стереть FLASH</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="581" />
        <source>Failed to program FLASH</source>
        <translation>Не удалось запрограммировать FLASH</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="590" />
        <source>Failed to verify FLASH</source>
        <translation>Не удалось проверить FLASH</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="599" />
        <location filename="../src/iapworker.cpp" line="601" />
        <source>Slot programmed</source>
        <translation>Слот запрограммирован</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="600" />
        <source>Slot programmed, the board stays in the bootloader</source>
        <translation>Слот запрограммирован, плата остаётся в загрузчике</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="607" />
        <source>Failed to finish the upgrade</source>
        <translation>Не удалось завершить обновление</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="613" />
        <source>Upgrade complete</source>
        <translation>Обновление завершено</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="614" />
        <source>========== Firmware upgrade succeeded ==========</source>
        <translation>========== Обновление прошивки успешно ==========</translation>
    </message>
    <message>
        <location filename="../src/iapworker.cpp" line="615" />
        <source>Firmware upgrade succeeded, the device will restart</source>
        <translation>Прошивка обновлена, устройство перезапустится</translation>
    </message>
</context>
<context>
    <name>LanguageManager</name>
    <message>
        <location filename="../src/languagemanager.cpp" line="125" />
        <source>Follow System(&amp;A)</source>
        <translation>Как в системе(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="126" />
        <source>English(&amp;E)</source>
        <translation>Английский(&amp;E)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="127" />
        <source>Simplified Chinese(&amp;C)</source>
        <translation>Китайский (упрощённый)(&amp;C)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="128" />
        <source>Russian(&amp;R)</source>
        <translation>Русский(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="129" />
        <source>German(&amp;G)</source>
        <translation>Немецкий(&amp;G)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="130" />
        <source>Spanish(&amp;S)</source>
        <translation>Испанский(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="152" />
        <source>Simplified Chinese</source>
        <translation>Китайский (упрощённый)</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="154" />
        <source>Russian</source>
        <translation>Русский</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="156" />
        <source>German</source>
        <translation>Немецкий</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="158" />
        <source>Spanish</source>
        <translation>Испанский</translation>
    </message>
    <message>
        <location filename="../src/languagemanager.cpp" line="161" />
        <source>English</source>
        <translation>Английский</translation>
    </message>
</context>
<context>
    <name>LibusbDev</name>
    <message>
        <location filename="../src/libusbdev.cpp" line="83" />
        <source>Cannot open the USB device (libusb error %1). The board must be bound to a generic USB driver (WinUSB on Windows) and must not be in use by another program.</source>
        <translation>Не удалось открыть USB-устройство (ошибка libusb %1). Плата должна быть привязана к универсальному USB-драйверу (WinUSB в Windows) и не должна использоваться другой программой.</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="98" />
        <source>Cannot claim the USB interface (libusb error %1). Close other programs that use the device and try again.</source>
        <translation>Не удалось занять USB-интерфейс (ошибка libusb %1). Закройте другие программы, использующие устройство, и повторите попытку.</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="124" />
        <source>Failed to send command 0x%1 (libusb error %2)</source>
        <translation>Не удалось отправить команду 0x%1 (ошибка libusb %2)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="140" />
        <source>The device did not answer command 0x%1 (libusb error %2)</source>
        <translation>Устройство не ответило на команду 0x%1 (ошибка libusb %2)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="158" />
        <source>libusb is not available</source>
        <translation>libusb недоступен</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="166" />
        <source>Unable to initialise libusb (error %1)</source>
        <translation>Не удалось инициализировать libusb (ошибка %1)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="198" />
        <source>Failed to enumerate the USB devices (libusb error %1)</source>
        <translation>Не удалось перечислить USB-устройства (ошибка libusb %1)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="281" />
        <location filename="../src/libusbdev.cpp" line="323" />
        <source>The device is no longer present (bus %1, address %2)</source>
        <translation>Устройство больше не найдено (шина %1, адрес %2)</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="305" />
        <source>Failed to send the enter-IAP-mode command</source>
        <translation>Не удалось отправить команду перехода в режим IAP</translation>
    </message>
    <message>
        <location filename="../src/libusbdev.cpp" line="346" />
        <source>Unexpected version response: 0x%1</source>
        <translation>Неожиданный ответ о версии: 0x%1</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../src/mainwindow.cpp" line="85" />
        <source> (in use)</source>
        <translation> (занято)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="492" />
        <source>CH32H417 Logic Analyzer Firmware Upgrade Tool</source>
        <translation>CH32H417 — обновление прошивки логического анализатора</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="495" />
        <source>Device</source>
        <translation>Устройство</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="496" />
        <source>Firmware File</source>
        <translation>Файл прошивки</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="497" />
        <source>IAP Settings</source>
        <translation>Параметры IAP</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="500" />
        <source>Device List:</source>
        <translation>Список устройств:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="501" />
        <source>Device Status:</source>
        <translation>Состояние устройства:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="502" />
        <source>Firmware Version:</source>
        <translation>Версия прошивки:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="503" />
        <source>File Path:</source>
        <translation>Путь к файлу:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="504" />
        <source>Firmware Info:</source>
        <translation>Прошивка:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="507" />
        <source>BIN Base Address: 0x</source>
        <translation>Адрес BIN: 0x</translation>
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
        <translation>По умолчанию: VID=0x1A86 PID=0xFE17</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="514" />
        <source>Refresh(&amp;R)</source>
        <translation>Обновить(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="515" />
        <source>Browse(&amp;B)...</source>
        <translation>Обзор(&amp;B)...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="520" />
        <source>Programming start address for .bin files (hexadecimal, e.g. 08006000). On the WeAct Studio Logic Analyzer V2 pick one of the three APP slots: slot 0 = logic analyzer, slot 1 = USB to UART + DAP, slot 2 = example.</source>
        <translation>Начальный адрес программирования для файлов .bin (шестнадцатеричный, например 08006000).
На WeAct Studio Logic Analyzer V2 выберите один из трёх слотов APP: слот 0 = логический анализатор, слот 1 = USB-UART + DAP, слот 2 = пример.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="523" />
        <source>Select or drop a .hex / .bin firmware file</source>
        <translation>Выберите или перетащите файл прошивки .hex / .bin</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="525" />
        <source>Upgrade Log</source>
        <translation>Журнал обновления</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="526" />
        <source>Reboot into:</source>
        <translation>Перезагрузить в:</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="528" />
        <source>Slot %1</source>
        <translation>Слот %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="530" />
        <source>Make slot %1 (0x%2) the active one and boot it</source>
        <translation>Сделать слот %1 (0x%2) активным и загрузить его</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="533" />
        <source>Start Upgrade(&amp;S)</source>
        <translation>Начать обновление(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="534" />
        <location filename="../src/mainwindow.cpp" line="543" />
        <source>Exit(&amp;X)</source>
        <translation>Выход(&amp;X)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="541" />
        <source>File(&amp;F)</source>
        <translation>Файл(&amp;F)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="542" />
        <source>Open Firmware(&amp;O)...</source>
        <translation>Открыть прошивку(&amp;O)...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="544" />
        <source>Tools(&amp;T)</source>
        <translation>Инструменты(&amp;T)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="545" />
        <source>Refresh Devices(&amp;R)</source>
        <translation>Обновить устройства(&amp;R)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="546" />
        <source>Reboot into Active Slot(&amp;B)</source>
        <translation>Перезагрузить в активный слот(&amp;B)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="547" />
        <source>Switch APP Slot(&amp;S)</source>
        <translation>Переключить слот APP(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="549" />
        <location filename="../src/mainwindow.cpp" line="751" />
        <source>Slot %1: 0x%2</source>
        <translation>Слот %1: 0x%2</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="553" />
        <source>Clear Log(&amp;L)</source>
        <translation>Очистить журнал(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="554" />
        <source>View(&amp;V)</source>
        <translation>Вид(&amp;V)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="555" />
        <source>Language(&amp;L)</source>
        <translation>Язык(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="556" />
        <source>Help(&amp;H)</source>
        <translation>Справка(&amp;H)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="557" />
        <source>About(&amp;A)</source>
        <translation>О программе(&amp;A)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="717" />
        <source>Hexadecimal, e.g. 08006000</source>
        <translation>Шестнадцатеричное, например 08006000</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="834" />
        <source>(No device found)</source>
        <translation>(Устройство не найдено)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="836" />
        <source>No device found</source>
        <translation>Устройство не найдено</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="952" />
        <source>&lt;font color='%1'&gt;Connected (application mode, %2 channel)&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Подключено (режим приложения, канал %2)&lt;/font&gt;</translation>
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
        <translation>Версию прошивки нельзя прочитать через канал USB-UART (последовательный)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="965" />
        <source>Read failed</source>
        <translation>Ошибка чтения</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="968" />
        <source>Software version: v%1  Hardware version: v%2</source>
        <translation>Версия ПО: v%1  Версия оборудования: v%2</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="975" />
        <source>&lt;font color='%1'&gt;Connected (IAP upgrade mode)&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Подключено (режим обновления IAP)&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="982" />
        <source>&lt;font color='%1'&gt;Device in use by another program&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Устройство занято другой программой&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="989" />
        <source>&lt;font color='%1'&gt;No device found&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Устройство не найдено&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1028" />
        <source>Leave &amp;IAP</source>
        <translation>Выйти из &amp;IAP</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1029" />
        <source>Reboot into &amp;IAP</source>
        <translation>Перезагрузить в &amp;IAP</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1033" />
        <source>Reboot the board and run the active APP slot again</source>
        <translation>Перезагрузить плату и снова запустить активный слот APP</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1034" />
        <source>Reboot the board into its bootloader (IAP mode)</source>
        <translation>Перезагрузить плату в загрузчик (режим IAP)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1044" />
        <source>Rebooting the device out of IAP mode ...</source>
        <translation>Вывод устройства из режима IAP ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1052" />
        <source>Leaving IAP failed: %1</source>
        <translation>Не удалось выйти из IAP: %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1053" />
        <location filename="../src/mainwindow.cpp" line="1145" />
        <location filename="../src/mainwindow.cpp" line="1188" />
        <location filename="../src/mainwindow.cpp" line="1445" />
        <location filename="../src/mainwindow.cpp" line="1450" />
        <location filename="../src/mainwindow.cpp" line="1470" />
        <source>Failed</source>
        <translation>Ошибка</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1057" />
        <location filename="../src/mainwindow.cpp" line="1149" />
        <source>Reboot request accepted, the device restarts ...</source>
        <translation>Запрос на перезагрузку принят, устройство перезапускается ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1102" />
        <source>Not available while an upgrade is running</source>
        <translation>Недоступно во время обновления</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1105" />
        <source>Needs a board that sits in the IAP bootloader</source>
        <translation>Требуется плата, находящаяся в загрузчике IAP</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1115" />
        <location filename="../src/mainwindow.cpp" line="1123" />
        <source>Not Available</source>
        <translation>Недоступно</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1116" />
        <source>Wait for the running upgrade to finish.</source>
        <translation>Дождитесь завершения текущего обновления.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1120" />
        <source>This command needs a board that sits in the IAP bootloader, the current device is in application mode.</source>
        <translation>Эта команда требует плату в загрузчике IAP, текущее устройство находится в режиме приложения.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1124" />
        <source>No CH32H417 device in IAP mode found.
These commands need a board that sits in the bootloader (power-cycle it with the button held).</source>
        <translation>Устройство CH32H417 в режиме IAP не найдено.
Эти команды требуют плату в загрузчике (переподключите питание, удерживая кнопку).</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1136" />
        <source>Rebooting the device into its active slot ...</source>
        <translation>Перезагрузка устройства в активный слот ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1144" />
        <source>Reboot failed: %1</source>
        <translation>Ошибка перезагрузки: %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1178" />
        <source>Switching to APP slot %1 (0x%2) ...</source>
        <translation>Переключение на слот APP %1 (0x%2) ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1187" />
        <source>Slot switch failed: %1</source>
        <translation>Ошибка переключения слота: %1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1192" />
        <source>Slot %1 is now active, the device reboots into it ...</source>
        <translation>Слот %1 теперь активен, устройство перезагружается в него ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1261" />
        <source>Select Firmware File</source>
        <translation>Выбор файла прошивки</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1263" />
        <source>Firmware Files (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binary Files (*.bin);;All Files (*.*)</source>
        <translation>Файлы прошивки (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Двоичные файлы (*.bin);;Все файлы (*.*)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1281" />
        <source>&lt;font color='%1'&gt;No valid firmware file selected&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;Не выбран корректный файл прошивки&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1290" />
        <source>&lt;font color='%1'&gt;%2&lt;/font&gt;</source>
        <translation>&lt;font color='%1'&gt;%2&lt;/font&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1295" />
        <source>%1  Size: %2  Address: 0x%3 - 0x%4  Checksum: 0x%5</source>
        <translation>%1  Размер: %2  Адрес: 0x%3 - 0x%4  КС: 0x%5</translation>
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
        <translation>Подсказка</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1331" />
        <source>Please select a valid firmware file first.</source>
        <translation>Сначала выберите корректный файл прошивки.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1337" />
        <source>No Device Found</source>
        <translation>Устройство не найдено</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1338" />
        <source>No CH32H417 device was detected.

If the device is already in IAP mode (for example powered up with the button held down), you can continue;
otherwise please connect the device first.

Continue?</source>
        <translation>Устройство CH32H417 не обнаружено.

Если устройство уже в режиме IAP (например, включено с зажатой кнопкой), можно продолжить;
иначе сначала подключите устройство.

Продолжить?</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1350" />
        <source>Firmware Error</source>
        <translation>Ошибка прошивки</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1383" />
        <source>Preparing ...</source>
        <translation>Подготовка ...</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1388" />
        <source>Target device: IAP HID (VID:0x%1 PID:0x%2)</source>
        <translation>Целевое устройство: IAP HID (VID:0x%1 PID:0x%2)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1392" />
        <source>Target device: serial (COM port %1)</source>
        <translation>Целевое устройство: последовательный порт (COM %1)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1394" />
        <source>Target device: libusb (bus %1, address %2)</source>
        <translation>Целевое устройство: libusb (шина %1, адрес %2)</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1397" />
        <source>Target device: CH375 #%1</source>
        <translation>Целевое устройство: CH375 #%1</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1440" />
        <source>Device is in IAP Mode</source>
        <translation>Устройство в режиме IAP</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1447" />
        <location filename="../src/mainwindow.cpp" line="1467" />
        <location filename="../src/mainwindow.cpp" line="1472" />
        <source>Please power-cycle the device (disconnect and reconnect the USB cable or the power supply) and run the upgrade again.</source>
        <translation>Переподключите питание устройства (отсоедините и снова подключите USB-кабель или блок питания) и повторите обновление.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1458" />
        <location filename="../src/mainwindow.cpp" line="1489" />
        <source>Upgrade Complete</source>
        <translation>Обновление завершено</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1460" />
        <source>Complete</source>
        <translation>Готово</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1461" />
        <source>Firmware upgrade succeeded!
The device will restart and run the new firmware.</source>
        <translation>Прошивка успешно обновлена!
Устройство перезапустится и запустит новую прошивку.</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1465" />
        <location filename="../src/mainwindow.cpp" line="1492" />
        <source>Upgrade Failed</source>
        <translation>Обновление не удалось</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1496" />
        <source>Ready</source>
        <translation>Готово</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1558" />
        <source>About</source>
        <translation>О программе</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1562" />
        <source>&lt;h3&gt;CH32H417 Logic Analyzer&lt;br&gt;Firmware Upgrade Tool&lt;/h3&gt;&lt;p&gt;Version: %1&lt;/p&gt;&lt;p&gt;&lt;b&gt;WeAct Studio&lt;/b&gt;&lt;br&gt;Copyright (C) 2026 WeAct Studio. All rights reserved.&lt;/p&gt;&lt;p&gt;This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.&lt;/p&gt;&lt;p&gt;License: GPL-3.0-or-later&lt;br&gt;&lt;a href='https://www.gnu.org/licenses/gpl-3.0.html'&gt;https://www.gnu.org/licenses/gpl-3.0.html&lt;/a&gt;&lt;/p&gt;&lt;p&gt;Built with Qt %2, statically compiled with MSYS2 (MINGW64).&lt;/p&gt;&lt;p&gt;Upgrade sequence: the enter-IAP command goes out over whichever USB channel the board is on - CH375, libusb / WinUSB, or the COM port of the USB-to-UART firmware. The board then resets into a HID IAP device, followed by erase / program / verify / finish.&lt;/p&gt;&lt;p&gt;A board that already sits in IAP mode can also be rebooted into its active slot, or switched to another APP slot, without downloading anything.&lt;/p&gt;&lt;p&gt;Windows needs one driver for the board: the WCH CH375 driver, or WinUSB when the board is bound to libusb.&lt;/p&gt;</source>
        <translation>&lt;h3&gt;CH32H417 логический анализатор&lt;br&gt;Средство обновления прошивки&lt;/h3&gt;&lt;p&gt;Версия: %1&lt;/p&gt;&lt;p&gt;&lt;b&gt;WeAct Studio&lt;/b&gt;&lt;br&gt;Copyright (C) 2026 WeAct Studio. Все права защищены.&lt;/p&gt;&lt;p&gt;Эта программа является свободным программным обеспечением: вы можете распространять и/или изменять её на условиях GNU General Public License, опубликованной Free Software Foundation, версии 3 либо (по вашему выбору) любой более поздней версии. Программа распространяется в надежде, что она будет полезна, но БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ, в том числе без подразумеваемых гарантий ТОВАРНОЙ ПРИГОДНОСТИ или ПРИГОДНОСТИ ДЛЯ КОНКРЕТНОЙ ЦЕЛИ. Подробности см. в GNU General Public License.&lt;/p&gt;&lt;p&gt;Лицензия: GPL-3.0-or-later&lt;br&gt;&lt;a href='https://www.gnu.org/licenses/gpl-3.0.html'&gt;https://www.gnu.org/licenses/gpl-3.0.html&lt;/a&gt;&lt;/p&gt;&lt;p&gt;Собрано с Qt %2, статически скомпоновано в MSYS2 (MINGW64).&lt;/p&gt;&lt;p&gt;Порядок обновления: команда входа в IAP отправляется по тому USB-каналу, на котором находится плата — CH375, libusb / WinUSB или COM-порт прошивки USB-UART. Затем плата перезагружается как HID-устройство IAP, после чего выполняются стирание / программирование / проверка / завершение.&lt;/p&gt;&lt;p&gt;Плату, уже находящуюся в режиме IAP, можно также перезагрузить в её активный слот или переключить в другой слот APP без загрузки прошивки.&lt;/p&gt;&lt;p&gt;В Windows для платы нужен один драйвер: драйвер WCH CH375 либо WinUSB, если плата привязана к libusb.&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1620" />
        <source>Upgrade in Progress</source>
        <translation>Идёт обновление</translation>
    </message>
    <message>
        <location filename="../src/mainwindow.cpp" line="1621" />
        <source>An upgrade is running; exiting now may corrupt the device firmware.
Are you sure you want to exit?</source>
        <translation>Идёт обновление; выход сейчас может повредить прошивку устройства.
Вы уверены, что хотите выйти?</translation>
    </message>
</context>
<context>
    <name>SerialDev</name>
    <message>
        <location filename="../src/serialdev.cpp" line="104" />
        <source>Serial port enumeration is only supported on Windows</source>
        <translation>Перечисление последовательных портов поддерживается только в Windows</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="111" />
        <source>Cannot enumerate the COM ports (error %1)</source>
        <translation>Не удалось перечислить COM-порты (ошибка %1)</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="233" />
        <source>Serial port access is only supported on Windows</source>
        <translation>Доступ к последовательному порту поддерживается только в Windows</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="245" />
        <source>%1 is open in another program.
Close the program (for example a serial terminal) and retry.</source>
        <translation>%1 открыт в другой программе.
Закройте эту программу (например, терминал) и повторите попытку.</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="251" />
        <source>Cannot open %1 (error %2)</source>
        <translation>Не удалось открыть %1 (ошибка %2)</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="262" />
        <source>Cannot query the settings of %1 (error %2)</source>
        <translation>Не удалось получить настройки %1 (ошибка %2)</translation>
    </message>
    <message>
        <location filename="../src/serialdev.cpp" line="305" />
        <source>Cannot set the IAP baud rate on %1 (error %2)</source>
        <translation>Не удалось задать скорость IAP на %1 (ошибка %2)</translation>
    </message>
</context>
<context>
    <name>ThemeManager</name>
    <message>
        <location filename="../src/thememanager.cpp" line="166" />
        <source>Follow System(&amp;S)</source>
        <translation>Как в системе(&amp;S)</translation>
    </message>
    <message>
        <location filename="../src/thememanager.cpp" line="168" />
        <source>Light(&amp;L)</source>
        <translation>Светлая(&amp;L)</translation>
    </message>
    <message>
        <location filename="../src/thememanager.cpp" line="171" />
        <source>Dark(&amp;D)</source>
        <translation>Тёмная(&amp;D)</translation>
    </message>
</context>
</TS>