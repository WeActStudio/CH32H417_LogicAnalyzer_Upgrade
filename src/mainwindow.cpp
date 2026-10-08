/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * Main window implementation
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "mainwindow.h"
#include "languagemanager.h"
#include "thememanager.h"

#include "ch375_wrapper.h"
#include "firmwareimage.h"
#include "iapctl.h"

#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QProgressBar>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QSettings>
#include <QTimer>
#include <QThread>
#include <QDateTime>
#include <QFileInfo>
#include <QRegularExpression>
#include <QCloseEvent>
#include <QEvent>
#include <QMimeData>
#include <QUrl>
#include <QFont>
#include <QStyle>

namespace {

const char *kSettingsOrg = "WeActStudio";
const char *kSettingsApp = "CH32H417 Logic Analyzer Upgrade";

/* Maximum number of characters shown on one line of the device list; anything
 * longer is elided and the full text is offered as a tooltip */
const int kDeviceLabelMaxChars = 56;

/*
 * Elide in the middle: the head keeps the VID/PID and the tail keeps the model
 * name and serial number, the two most recognisable parts. The full text is
 * always available in the tooltip.
 */
QString elideMiddle(const QString &text, int maxChars)
{
    if (text.size() <= maxChars)
        return text;
    if (maxChars <= 4)
        return text.left(maxChars);

    const int tailChars = (maxChars - 3) / 3;
    return text.left(maxChars - 3 - tailChars) + QStringLiteral("...")
           + text.right(tailChars);
}

/*
 * One line of the device list: only the product name, e.g.
 * "WeAct Studio Logic Analyzer V2". The mode, VID/PID, CH375 index and serial
 * number are not shown here; the complete details stay in the tooltip.
 */
QString deviceListLabel(const Ch375DeviceInfo &info)
{
    QString label = elideMiddle(info.modelName(), kDeviceLabelMaxChars);
    if (info.busy)
        label += MainWindow::tr(" (in use)");
    return label;
}

/*
 * Identity of a board across refreshes: the channel and the index inside it.
 * The same board reached over libusb and over CH375 are two different keys,
 * which is what they are — only one of the two can claim the device.
 */
QString deviceKey(const Ch375DeviceInfo &info)
{
    /* A serial device has no index; its COM port is the unique part */
    if (info.viaSerial())
        return QStringLiteral("serial#%1").arg(info.comPort);
    return QStringLiteral("%1#%2").arg(info.channelName()).arg(info.index);
}

MainWindow *g_mainWindow = nullptr;

/* Bridge the internal CH375 DLL log onto the UI (may be called from a worker
 * thread) */
void ch375LogBridge(int level, const char *message)
{
    if (!g_mainWindow || !message)
        return;

    const QString text = QString::fromLocal8Bit(message);
    QMetaObject::invokeMethod(g_mainWindow,
                              [level, text]() {
                                  if (g_mainWindow)
                                      g_mainWindow->appendCh375Log(level, text);
                              },
                              Qt::QueuedConnection);
}

} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , deviceCombo_(nullptr)
    , refreshButton_(nullptr)
    , deviceStatusLabel_(nullptr)
    , deviceVersionLabel_(nullptr)
    , autoRefreshTimer_(nullptr)
    , fileEdit_(nullptr)
    , browseButton_(nullptr)
    , firmwareInfoLabel_(nullptr)
    , baseAddressCombo_(nullptr)
    , baseAddressHintLabel_(nullptr)
    , binBaseAddressLocked_(false)
    , binBaseAddressValue_(0x08006000u)
    , iapOnlyRun_(false)
    , iapVidEdit_(nullptr)
    , iapPidEdit_(nullptr)
    , progressBar_(nullptr)
    , progressLabel_(nullptr)
    , logView_(nullptr)
    , logTitleLabel_(nullptr)
    , iapSlotLabel_(nullptr)
    , iapButton_(nullptr)
    , startButton_(nullptr)
    , exitButton_(nullptr)
    , fileMenu_(nullptr)
    , toolMenu_(nullptr)
    , viewMenu_(nullptr)
    , langMenu_(nullptr)
    , helpMenu_(nullptr)
    , openAction_(nullptr)
    , exitAction_(nullptr)
    , refreshAction_(nullptr)
    , clearLogAction_(nullptr)
    , rebootAction_(nullptr)
    , slotMenu_(nullptr)
    , aboutAction_(nullptr)
    , langActionGroup_(nullptr)
    , themeActionGroup_(nullptr)
    , deviceGroup_(nullptr)
    , fwGroup_(nullptr)
    , optGroup_(nullptr)
    , deviceListLabel_(nullptr)
    , deviceStatusTitleLabel_(nullptr)
    , deviceVersionTitleLabel_(nullptr)
    , filePathLabel_(nullptr)
    , firmwareInfoTitleLabel_(nullptr)
    , baseAddressLabel_(nullptr)
    , iapVidLabel_(nullptr)
    , iapPidLabel_(nullptr)
    , iapHintLabel_(nullptr)
    , worker_(nullptr)
    , workerThread_(nullptr)
    , upgrading_(false)
    , appDeviceIndex_(-1)
    , deviceMode_(DeviceMode::NotFound)
    , versionQueriedKey_()
    , versionValid_(false)
    , swVersion_(0)
    , hwVersion_(0)
    , progressState_(ProgressState::Idle)
{
    g_mainWindow = this;
    ch375_set_log_func(ch375LogBridge);

    setupUi();
    createMenus();
    retranslateUi();
    loadSettings();

    setAcceptDrops(true);

    autoRefreshTimer_ = new QTimer(this);
    autoRefreshTimer_->setInterval(3000);
    connect(autoRefreshTimer_, &QTimer::timeout, this, &MainWindow::onAutoRefreshTimeout);
    autoRefreshTimer_->start();

    QTimer::singleShot(150, this, &MainWindow::onRefreshDevices);
}

MainWindow::~MainWindow()
{
    ch375_set_log_func(nullptr);
    g_mainWindow = nullptr;

    if (workerThread_ && workerThread_->isRunning()) {
        if (worker_)
            worker_->cancel();
        workerThread_->quit();
        if (!workerThread_->wait(3000)) {
            workerThread_->terminate();
            workerThread_->wait();
        }
    }

    ch375_cleanup();
}

/* ==========================================================================
 * UI construction
 * ========================================================================== */

void MainWindow::setupUi()
{
    setMinimumSize(680, 620);

    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setSpacing(10);

    /* ---------- Device section ---------- */
    deviceGroup_ = new QGroupBox(central);
    QFormLayout *deviceLayout = new QFormLayout(deviceGroup_);

    QHBoxLayout *deviceRow = new QHBoxLayout();
    deviceCombo_ = new QComboBox(deviceGroup_);
    deviceCombo_->setMinimumWidth(320);
    refreshButton_ = new QPushButton(deviceGroup_);
    deviceRow->addWidget(deviceCombo_, 1);
    deviceRow->addWidget(refreshButton_);

    deviceListLabel_ = new QLabel(deviceGroup_);
    deviceLayout->addRow(deviceListLabel_, deviceRow);

    deviceStatusLabel_ = new QLabel(deviceGroup_);
    deviceStatusTitleLabel_ = new QLabel(deviceGroup_);
    deviceLayout->addRow(deviceStatusTitleLabel_, deviceStatusLabel_);

    deviceVersionLabel_ = new QLabel(deviceGroup_);
    deviceVersionTitleLabel_ = new QLabel(deviceGroup_);
    deviceLayout->addRow(deviceVersionTitleLabel_, deviceVersionLabel_);

    mainLayout->addWidget(deviceGroup_);

    /* ---------- Firmware section ---------- */
    fwGroup_ = new QGroupBox(central);
    QFormLayout *fwLayout = new QFormLayout(fwGroup_);

    QHBoxLayout *fileRow = new QHBoxLayout();
    fileEdit_ = new QLineEdit(fwGroup_);
    browseButton_ = new QPushButton(fwGroup_);
    fileRow->addWidget(fileEdit_, 1);
    fileRow->addWidget(browseButton_);

    filePathLabel_ = new QLabel(fwGroup_);
    fwLayout->addRow(filePathLabel_, fileRow);

    firmwareInfoLabel_ = new QLabel(fwGroup_);
    firmwareInfoLabel_->setWordWrap(true);
    firmwareInfoTitleLabel_ = new QLabel(fwGroup_);
    fwLayout->addRow(firmwareInfoTitleLabel_, firmwareInfoLabel_);

    baseAddressCombo_ = new QComboBox(fwGroup_);
    baseAddressCombo_->setEditable(true);
    baseAddressCombo_->setInsertPolicy(QComboBox::NoInsert);
    baseAddressCombo_->setMaxVisibleItems(8);
    baseAddressCombo_->setMinimumContentsLength(30);
    baseAddressCombo_->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    baseAddressLabel_ = new QLabel(fwGroup_);
    baseAddressHintLabel_ = new QLabel(fwGroup_);
    baseAddressHintLabel_->setStyleSheet(QStringLiteral("color: gray;"));

    QHBoxLayout *baseRow = new QHBoxLayout();
    baseRow->addWidget(baseAddressCombo_);
    baseRow->addWidget(baseAddressHintLabel_);
    baseRow->addStretch(1);
    fwLayout->addRow(baseAddressLabel_, baseRow);

    mainLayout->addWidget(fwGroup_);

    /* ---------- IAP options ---------- */
    optGroup_ = new QGroupBox(central);
    QHBoxLayout *optLayout = new QHBoxLayout(optGroup_);

    iapVidEdit_ = new QLineEdit("1A86", optGroup_);
    iapPidEdit_ = new QLineEdit("FE17", optGroup_);
    iapVidEdit_->setMaximumWidth(80);
    iapPidEdit_->setMaximumWidth(80);

    iapVidLabel_ = new QLabel(optGroup_);
    iapPidLabel_ = new QLabel(optGroup_);
    iapHintLabel_ = new QLabel(optGroup_);

    optLayout->addWidget(iapVidLabel_);
    optLayout->addWidget(iapVidEdit_);
    optLayout->addSpacing(20);
    optLayout->addWidget(iapPidLabel_);
    optLayout->addWidget(iapPidEdit_);
    optLayout->addStretch(1);
    optLayout->addWidget(iapHintLabel_);

    mainLayout->addWidget(optGroup_);

    /* ---------- Progress ---------- */
    QHBoxLayout *progressLayout = new QHBoxLayout();
    progressBar_ = new QProgressBar(central);
    progressBar_->setRange(0, 100);
    progressBar_->setValue(0);
    progressBar_->setTextVisible(true);
    progressLabel_ = new QLabel(central);
    progressLabel_->setMinimumWidth(160);
    progressLayout->addWidget(progressBar_, 1);
    progressLayout->addWidget(progressLabel_);
    mainLayout->addLayout(progressLayout);

    /* ---------- Log ---------- */
    logTitleLabel_ = new QLabel(central);
    mainLayout->addWidget(logTitleLabel_);
    logView_ = new QTextEdit(central);
    logView_->setReadOnly(true);
    QFont monoFont("Consolas", 9);
    monoFont.setStyleHint(QFont::Monospace);
    logView_->setFont(monoFont);
    logView_->setMinimumHeight(180);
    mainLayout->addWidget(logView_, 1);

    /* ---------- Buttons ---------- */
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(1);

    /* Bootloader only: "Reboot into:" plus one button per APP slot. The label
       and the buttons sit next to each other, so the row starts with the
       label and the buttons line up behind it. */
    iapSlotLabel_ = new QLabel(central);
    buttonLayout->addWidget(iapSlotLabel_);
    for (int i = 0; i < IAP_APP_SLOT_NUM; ++i) {
        QPushButton *button = new QPushButton(central);
        iapSlotButtons_.append(button);
        buttonLayout->addWidget(button);
        connect(button, &QPushButton::clicked, this, [this, i]() { runSlotSwitch(i); });
    }

    iapButton_ = new QPushButton(central);
    startButton_ = new QPushButton(central);
    exitButton_ = new QPushButton(central);
    buttonLayout->addWidget(iapButton_);
    buttonLayout->addWidget(startButton_);
    buttonLayout->addWidget(exitButton_);
    mainLayout->addLayout(buttonLayout);

    setCentralWidget(central);

    connect(refreshButton_, &QPushButton::clicked, this, &MainWindow::onRefreshDevices);
    connect(browseButton_, &QPushButton::clicked, this, &MainWindow::onBrowseFirmware);
    connect(iapButton_, &QPushButton::clicked, this, &MainWindow::onIapButtonClicked);
    connect(startButton_, &QPushButton::clicked, this, &MainWindow::onStartUpgrade);
    connect(exitButton_, &QPushButton::clicked, this, &MainWindow::close);
    connect(fileEdit_, &QLineEdit::textChanged, this, &MainWindow::onFirmwarePathChanged);
    connect(deviceCombo_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onDeviceIndexChanged);
    /*
     * The address range shown for a .bin depends on the base address, so
     * picking another slot (or typing an address) has to redraw it - the
     * programmed range must never disagree with what is on screen. Typed
     * text is committed with editingFinished, so this does not re-read the
     * file on every keypress.
     */
    connect(baseAddressCombo_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this]() {
                updateBinBaseAddressFromUi();
                updateFirmwareInfo();
            });
    if (baseAddressCombo_->isEditable() && baseAddressCombo_->lineEdit()) {
        connect(baseAddressCombo_->lineEdit(), &QLineEdit::editingFinished, this, [this]() {
            updateBinBaseAddressFromUi();
            updateFirmwareInfo();
        });
    }
}

void MainWindow::createMenus()
{
    fileMenu_ = menuBar()->addMenu(QString());
    openAction_ = new QAction(this);
    exitAction_ = new QAction(this);
    fileMenu_->addAction(openAction_);
    fileMenu_->addSeparator();
    fileMenu_->addAction(exitAction_);
    connect(openAction_, &QAction::triggered, this, &MainWindow::onBrowseFirmware);
    connect(exitAction_, &QAction::triggered, this, &MainWindow::close);

    toolMenu_ = menuBar()->addMenu(QString());
    refreshAction_ = new QAction(this);
    rebootAction_ = new QAction(this);
    slotMenu_ = toolMenu_->addMenu(QString());
    clearLogAction_ = new QAction(this);
    toolMenu_->addAction(refreshAction_);
    toolMenu_->addSeparator();
    toolMenu_->addAction(rebootAction_);
    toolMenu_->addAction(slotMenu_->menuAction());
    toolMenu_->addSeparator();
    toolMenu_->addAction(clearLogAction_);
    connect(refreshAction_, &QAction::triggered, this, &MainWindow::onRefreshDevices);
    connect(clearLogAction_, &QAction::triggered, this, &MainWindow::onClearLog);
    connect(rebootAction_, &QAction::triggered, this, &MainWindow::onRebootDevice);

    /* One entry per APP slot; the data carries the slot index */
    for (int i = 0; i < IAP_APP_SLOT_NUM; ++i) {
        QAction *action = slotMenu_->addAction(QString());
        action->setData(i);
        slotActions_.append(action);
        connect(action, &QAction::triggered, this, &MainWindow::onSlotActionTriggered);
    }

    /* ---------- Theme menu (light / dark / follow system) ---------- */
    viewMenu_ = menuBar()->addMenu(QString());
    themeActionGroup_ = new QActionGroup(this);
    themeActionGroup_->setExclusive(true);

    for (int i = 0; i < 3; ++i) {
        QAction *action = new QAction(this);
        action->setCheckable(true);
        action->setData(i);
        themeActionGroup_->addAction(action);
        viewMenu_->addAction(action);
        themeActions_.append(action);
    }
    connect(themeActionGroup_, &QActionGroup::triggered,
            this, &MainWindow::onThemeActionTriggered);
    connect(ThemeManager::instance(), &ThemeManager::themeChanged,
            this, &MainWindow::onThemeChanged);

    /* ---------- Language menu ---------- */
    langMenu_ = menuBar()->addMenu(QString());
    langActionGroup_ = new QActionGroup(this);
    langActionGroup_->setExclusive(true);

    for (int i = 0; i < LanguageManager::preferenceNames().size(); ++i) {
        QAction *action = new QAction(this);
        action->setCheckable(true);
        action->setData(i);
        langActionGroup_->addAction(action);
        langMenu_->addAction(action);
        langActions_.append(action);
    }
    connect(langActionGroup_, &QActionGroup::triggered,
            this, &MainWindow::onLanguageActionTriggered);

    helpMenu_ = menuBar()->addMenu(QString());
    aboutAction_ = new QAction(this);
    helpMenu_->addAction(aboutAction_);
    connect(aboutAction_, &QAction::triggered, this, &MainWindow::showAbout);
}

/** Apply every UI text for the current language (called on construction and
 *  whenever the language changes) */
void MainWindow::retranslateUi()
{
    setWindowTitle(tr("CH32H417 Logic Analyzer Firmware Upgrade Tool"));

    /* Group boxes */
    deviceGroup_->setTitle(tr("Device"));
    fwGroup_->setTitle(tr("Firmware File"));
    optGroup_->setTitle(tr("IAP Settings"));

    /* Row captions */
    deviceListLabel_->setText(tr("Device List:"));
    deviceStatusTitleLabel_->setText(tr("Device Status:"));
    deviceVersionTitleLabel_->setText(tr("Firmware Version:"));
    filePathLabel_->setText(tr("File Path:"));
    firmwareInfoTitleLabel_->setText(tr("Firmware Info:"));
    /* The line edit only holds the hexadecimal digits, the 0x prefix comes
       from the caption */
    baseAddressLabel_->setText(tr("BIN Base Address: 0x"));
    updateBaseAddressHint();
    iapVidLabel_->setText(tr("VID: 0x"));
    iapPidLabel_->setText(tr("PID: 0x"));
    iapHintLabel_->setText(tr("Defaults: VID=0x1A86 PID=0xFE17"));

    /* Widgets */
    refreshButton_->setText(tr("Refresh(&R)"));
    browseButton_->setText(tr("Browse(&B)..."));
    /*
     * The dropdown itself stays plain (slot number and address only); what the
     * slots are used for belongs into the tooltip, where it costs no width.
     */
    baseAddressCombo_->setToolTip(tr("Programming start address for .bin files (hexadecimal, e.g. 08006000). "
                                      "On the WeAct Studio Logic Analyzer V2 pick one of the three APP slots: "
                                      "slot 0 = logic analyzer, slot 1 = USB to UART, slot 2 = example."));
    fileEdit_->setPlaceholderText(tr("Select or drop a .hex / .bin firmware file"));

    logTitleLabel_->setText(tr("Upgrade Log"));
    iapSlotLabel_->setText(tr("Reboot into:"));
    for (int i = 0; i < iapSlotButtons_.size(); ++i) {
        iapSlotButtons_.at(i)->setText(tr("Slot %1").arg(i));
        iapSlotButtons_.at(i)->setToolTip(
            tr("Make slot %1 (0x%2) the active one and boot it")
                .arg(i).arg(iapctl_slot_base_address(i), 8, 16, QChar('0')));
    }
    startButton_->setText(tr("Start Upgrade(&S)"));
    exitButton_->setText(tr("Exit(&X)"));

    /*
     * Menus (a LanguageChange event can also arrive very early during
     * construction, when the menus do not exist yet, hence the null checks)
     */
    if (fileMenu_) {
        fileMenu_->setTitle(tr("File(&F)"));
        openAction_->setText(tr("Open Firmware(&O)..."));
        exitAction_->setText(tr("Exit(&X)"));
        toolMenu_->setTitle(tr("Tools(&T)"));
        refreshAction_->setText(tr("Refresh Devices(&R)"));
        rebootAction_->setText(tr("Reboot into Active Slot(&B)"));
        slotMenu_->setTitle(tr("Switch APP Slot(&S)"));
        for (int i = 0; i < slotActions_.size(); ++i) {
            slotActions_.at(i)->setText(tr("Slot %1: 0x%2")
                                            .arg(i)
                                            .arg(iapctl_slot_base_address(i), 8, 16, QChar('0')));
        }
        clearLogAction_->setText(tr("Clear Log(&L)"));
        viewMenu_->setTitle(tr("View(&V)"));
        langMenu_->setTitle(tr("Language(&L)"));
        helpMenu_->setTitle(tr("Help(&H)"));
        aboutAction_->setText(tr("About(&A)"));

        /* Language menu entries */
        const QStringList names = LanguageManager::preferenceNames();
        for (int i = 0; i < langActions_.size() && i < names.size(); ++i)
            langActions_.at(i)->setText(names.at(i));

        /* Theme menu entries */
        for (int i = 0; i < themeActions_.size() && i < 3; ++i)
            themeActions_.at(i)->setText(
                ThemeManager::modeName(static_cast<ThemeManager::Mode>(i)));
    }

    /* Dynamic texts */
    updateDeviceStatusText();
    updateFirmwareInfo();
    updateProgressText();
    if (rebootAction_) {
        updateBootloaderActions();
        updateIapButton();
    }
}

/* ==========================================================================
 * Language and theme switching
 * ========================================================================== */

void MainWindow::onLanguageActionTriggered(QAction *action)
{
    if (!action)
        return;

    const int index = action->data().toInt();
    LanguageManager::instance()->setPreference(
        static_cast<LanguageManager::Preference>(index));
}

void MainWindow::onLanguageChanged()
{
    const int index = static_cast<int>(LanguageManager::instance()->preference());
    for (int i = 0; i < langActions_.size(); ++i)
        langActions_.at(i)->setChecked(i == index);
}

void MainWindow::onThemeActionTriggered(QAction *action)
{
    if (!action)
        return;

    const int index = action->data().toInt();
    ThemeManager::instance()->setMode(static_cast<ThemeManager::Mode>(index));
}

void MainWindow::onThemeChanged()
{
    const int index = static_cast<int>(ThemeManager::instance()->mode());
    for (int i = 0; i < themeActions_.size(); ++i)
        themeActions_.at(i)->setChecked(i == index);

    /* The log and status colours follow the theme, so redraw everything */
    renderLog();
    updateDeviceStatusText();
    updateFirmwareInfo();
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        retranslateUi();

    QMainWindow::changeEvent(event);
}

/* ==========================================================================
 * Settings
 * ========================================================================== */

void MainWindow::loadSettings()
{
    QSettings settings(kSettingsOrg, kSettingsApp);
    fileEdit_->setText(settings.value("firmwarePath").toString());
    const QString baseText = settings.value("binBaseAddress", "08006000").toString();
    bool baseOk = false;
    const quint32 baseValue = baseText.toUInt(&baseOk, 16);
    if (baseOk)
        binBaseAddressValue_ = baseValue;
    baseAddressCombo_->setEditText(QString::number(binBaseAddressValue_, 16)
                                       .rightJustified(8, QLatin1Char('0')));
    iapVidEdit_->setText(settings.value("iapVid", "1A86").toString());
    iapPidEdit_->setText(settings.value("iapPid", "FE17").toString());
    restoreGeometry(settings.value("geometry").toByteArray());

    onLanguageChanged();     /* sync the language menu check marks */
    onThemeChanged();        /* sync the theme menu check marks */
}

void MainWindow::saveSettings()
{
    QSettings settings(kSettingsOrg, kSettingsApp);
    settings.setValue("firmwarePath", fileEdit_->text());
    settings.setValue("binBaseAddress",
                      QString::number(binBaseAddress(), 16).rightJustified(8, QLatin1Char('0')));
    settings.setValue("iapVid", iapVidEdit_->text());
    settings.setValue("iapPid", iapPidEdit_->text());
    settings.setValue("geometry", saveGeometry());
}

/* ==========================================================================
 * Devices
 * ========================================================================== */

quint16 MainWindow::iapVid() const
{
    bool ok = false;
    const quint16 value = static_cast<quint16>(iapVidEdit_->text().trimmed().toUInt(&ok, 16));
    return ok ? value : CH32H417_IAP_VID;
}

quint16 MainWindow::iapPid() const
{
    bool ok = false;
    const quint16 value = static_cast<quint16>(iapPidEdit_->text().trimmed().toUInt(&ok, 16));
    return ok ? value : CH32H417_IAP_PID;
}

quint32 MainWindow::binBaseAddress() const
{
    return binBaseAddressValue_;
}

/*
 * Take the address out of the widget and remember it. Called whenever the user
 * picks a slot or finishes typing an address - the stored value is what the
 * upgrade uses, so it must survive the slot list being rebuilt.
 */
void MainWindow::updateBinBaseAddressFromUi()
{
    /* A preset slot item carries its address in Qt::UserRole */
    const QVariant data = baseAddressCombo_->itemData(baseAddressCombo_->currentIndex());
    if (data.isValid()) {
        binBaseAddressValue_ = static_cast<quint32>(data.toUInt());
        return;
    }

    /* Typed text is plain hexadecimal, with an optional 0x prefix tolerated.
     * Text that does not parse (an empty field, a label) keeps the last good
     * value rather than silently jumping back to the default. */
    bool ok = false;
    QString text = baseAddressCombo_->currentText().trimmed().toLower();
    if (text.startsWith(QLatin1String("0x")))
        text.remove(0, 2);
    const quint32 value = text.toUInt(&ok, 16);
    if (ok)
        binBaseAddressValue_ = value;
}

void MainWindow::updateBaseAddressHint()
{
    /* V2 boards show the slot presets in the dropdown; other devices keep the
       note about the number base */
    baseAddressHintLabel_->setText(tr("Hexadecimal, e.g. 08006000"));
}

/*
 * Fill the BIN base address dropdown. V2 boards get the three APP slots of
 * the IAP firmware (see the MCU project: Common/iap.c, IAP_SlotOfBase — the
 * erase command only accepts exactly these bases). Other devices keep the
 * plain editable hex input.
 */
void MainWindow::updateBaseAddressSlots(bool v2)
{
    /* Rebuilding the list is not a user action: without this the periodic
       device refresh would re-read the firmware file on every tick */
    const bool blocked = baseAddressCombo_->blockSignals(true);

    if (!v2) {
        if (baseAddressCombo_->count() == 0) {
            baseAddressCombo_->blockSignals(blocked);
            return;                         /* already a plain hex input */
        }

        /* Drop the presets; the field goes back to showing the bare address
           (not a slot label, which would not parse any more) */
        baseAddressCombo_->clear();
        baseAddressCombo_->setEditText(QString::number(binBaseAddressValue_, 16)
                                           .rightJustified(8, QLatin1Char('0')));
        baseAddressCombo_->blockSignals(blocked);
        return;
    }

    /* Rebuild the list around the address in use, so neither a periodic device
       refresh nor a V2 board coming and going resets the slot choice */
    baseAddressCombo_->clear();
    for (int i = 0; i < IAP_APP_SLOT_NUM; ++i) {
        baseAddressCombo_->addItem(tr("Slot %1: 0x%2").arg(i).arg(
                                       iapctl_slot_base_address(i), 8, 16, QChar('0')),
                                   iapctl_slot_base_address(i));
    }

    int select = 0;
    for (int i = 0; i < baseAddressCombo_->count(); ++i) {
        if (static_cast<quint32>(baseAddressCombo_->itemData(i).toUInt()) == binBaseAddressValue_) {
            select = i;
            break;
        }
    }
    baseAddressCombo_->setCurrentIndex(select);
    baseAddressCombo_->blockSignals(blocked);
}

/*
 * On the WeAct Studio Logic Analyzer V2 the IAP VID/PID are fixed and the BIN
 * base address is chosen from the three APP slots. When a V2 board is detected
 * the values are filled in automatically and the VID/PID locked, to keep the
 * user from bricking the device.
 */
void MainWindow::updateV2Lock()
{
    const int current = deviceCombo_->currentIndex();
    const bool v2 = !devices_.isEmpty() && current >= 0 && current < devices_.size()
                    && devices_.at(current).modelName()
                           == QLatin1String("WeAct Studio Logic Analyzer V2");

    binBaseAddressLocked_ = v2;

    updateBaseAddressSlots(v2);

    if (v2) {
        iapVidEdit_->setText(QStringLiteral("1A86"));
        iapPidEdit_->setText(QStringLiteral("FE17"));
    }

    /* The base address combo stays usable for V2 boards: choosing one of the
       slot presets is exactly what it is there for. Only the VID/PID fields
       get locked. */
    baseAddressCombo_->setEnabled(!upgrading_);
    iapVidEdit_->setReadOnly(v2);
    iapVidEdit_->setEnabled(!v2 && !upgrading_);
    iapVidEdit_->setFocusPolicy(v2 ? Qt::NoFocus : Qt::StrongFocus);
    iapPidEdit_->setReadOnly(v2);
    iapPidEdit_->setEnabled(!v2 && !upgrading_);
    iapPidEdit_->setFocusPolicy(v2 ? Qt::NoFocus : Qt::StrongFocus);

    updateBaseAddressHint();
}

void MainWindow::refreshDeviceList()
{
    QString error;
    const DeviceMode mode = ch375dev_detect(CH32H417_APP_VID, CH32H417_APP_PID,
                                            iapVid(), iapPid(),
                                            appDeviceIndex_, appDevice_, devices_, error);
    deviceMode_ = mode;
    deviceDetectError_ = error;

    deviceCombo_->blockSignals(true);
    deviceCombo_->clear();

    if (devices_.isEmpty()) {
        deviceCombo_->addItem(tr("(No device found)"), -1);
        deviceCombo_->setEnabled(false);
        deviceCombo_->setToolTip(tr("No device found"));
    } else {
        for (const Ch375DeviceInfo &info : devices_) {
            const QString full = info.description();
            deviceCombo_->addItem(deviceListLabel(info), info.index);
            /* The full text goes into the tooltip, so hovering shows the
               VID/PID and serial number */
            deviceCombo_->setItemData(deviceCombo_->count() - 1, full, Qt::ToolTipRole);
        }
        deviceCombo_->setEnabled(true);
        const int cur = deviceCombo_->currentIndex();
        deviceCombo_->setToolTip(
            cur >= 0 ? deviceCombo_->itemData(cur, Qt::ToolTipRole).toString() : QString());
    }

    /*
     * On the WeAct Studio Logic Analyzer V2 the application start address is
     * fixed at 0x08006000 and the IAP VID/PID are fixed as well; the user must
     * not change them, otherwise the wrong region could be programmed.
     */
    updateV2Lock();

    deviceCombo_->blockSignals(false);

    switch (mode) {
    case DeviceMode::AppRunning: {
        /*
         * Re-read the version only when the device changed or when the previous
         * read failed. Unplugging and plugging back in keeps the same key, so a
         * pure "index changed" test would never re-read and the UI would stay
         * at "read failed"; a failure must therefore allow a retry next time.
         * The key covers the channel as well, so a board that changes from the
         * CH375 driver to WinUSB is queried again.
         */
        const QString key = deviceKey(appDevice_);
        if (appDevice_.viaSerial()) {
            /* The USB-to-UART application has no version command on its CDC
               channels; the version stays unknown without error retries */
            versionValid_ = false;
            versionQueriedKey_ = key;
            deviceDetectError_.clear();
        } else if (key != versionQueriedKey_ || !versionValid_) {
            versionValid_ = ch375dev_get_version_for(appDevice_, swVersion_, hwVersion_, error);
            if (versionValid_) {
                versionQueriedKey_ = key;
                deviceDetectError_.clear();
            } else {
                versionQueriedKey_.clear();      /* keep retrying on the next refresh */
                deviceDetectError_ = error;
            }
        }
        break;
    }

    case DeviceMode::IapBootloader:
    case DeviceMode::DeviceBusy:
    default:
        versionValid_ = false;
        versionQueriedKey_.clear();             /* not in application mode, re-read when it reconnects */
        break;
    }

    updateDeviceStatusText();
    updateBootloaderActions();
    updateIapButton();
}

/** Status text colours: kind 0=connected 1=IAP mode 2=not found (adapted to
 *  light / dark automatically) */
QString MainWindow::statusColor(int kind) const
{
    const bool dark = ThemeManager::instance()->isDark();
    switch (kind) {
    case 0:
        return dark ? QStringLiteral("#5CC45C") : QStringLiteral("#008000");
    case 1:
        return dark ? QStringLiteral("#E8A33D") : QStringLiteral("#C06000");
    default:
        return dark ? QStringLiteral("#FF7B7B") : QStringLiteral("#A00000");
    }
}

/** Rebuild the device section texts (reused on language / theme changes) */
void MainWindow::updateDeviceStatusText()
{
    switch (deviceMode_) {
    case DeviceMode::AppRunning:
        /*
         * Two channels can reach a board in application mode: the CH375 driver
         * and a generic USB driver (libusb). Naming the channel here tells the
         * user why a board bound to WinUSB is still upgradeable.
         */
        deviceStatusLabel_->setText(
            tr("<font color='%1'>Connected (application mode, %2 channel)</font>")
                .arg(statusColor(0))
                .arg(appDevice_.channelName()));
        /* The USB-to-UART application cannot answer a version query */
        if (appDevice_.viaSerial()) {
            deviceVersionLabel_->setText(tr("-"));
            deviceVersionLabel_->setToolTip(
                tr("The firmware version cannot be read on the USB-UART (serial) channel"));
        } else {
            /* Only the numeric version is shown, e.g. v1.1 */
            deviceVersionLabel_->setText(
                versionValid_
                    ? QStringLiteral("v%1.%2").arg(swVersion_).arg(hwVersion_)
                    : tr("Read failed"));
            deviceVersionLabel_->setToolTip(
                versionValid_
                    ? tr("Software version: v%1  Hardware version: v%2").arg(swVersion_).arg(hwVersion_)
                    : deviceDetectError_);
        }
        break;

    case DeviceMode::IapBootloader:
        deviceStatusLabel_->setText(
            tr("<font color='%1'>Connected (IAP upgrade mode)</font>").arg(statusColor(1)));
        deviceVersionLabel_->setText(tr("-"));
        deviceVersionLabel_->setToolTip(QString());
        break;

    case DeviceMode::DeviceBusy:
        deviceStatusLabel_->setText(
            tr("<font color='%1'>Device in use by another program</font>").arg(statusColor(1)));
        deviceVersionLabel_->setText(tr("-"));
        deviceVersionLabel_->setToolTip(deviceDetectError_);
        break;

    default:
        deviceStatusLabel_->setText(
            tr("<font color='%1'>No device found</font>").arg(statusColor(2)));
        deviceVersionLabel_->setText(tr("-"));
        deviceVersionLabel_->setToolTip(QString());
        if (!deviceDetectError_.isEmpty())
            deviceStatusLabel_->setToolTip(deviceDetectError_);
        break;
    }
}

void MainWindow::onRefreshDevices()
{
    refreshDeviceList();
}

/* ==========================================================================
 * The one button next to "Start Upgrade"
 *
 * In application mode it reboots the board into its bootloader - the first
 * half of an upgrade, useful on its own to leave a board in the bootloader.
 * In IAP mode the same button offers the way back: rebooting into the active
 * slot, which is what CMD_IAP_REBOOT (0x85) does.
 * ========================================================================== */

void MainWindow::updateIapButton()
{
    if (!iapButton_)
        return;

    const bool inIap = (deviceMode_ == DeviceMode::IapBootloader);
    const bool haveDevice = inIap || (deviceMode_ == DeviceMode::AppRunning);
    const bool idle = haveDevice && !upgrading_;

    /* The slot buttons only exist for a board that sits in the bootloader */
    iapSlotLabel_->setVisible(inIap);
    for (QPushButton *button : iapSlotButtons_) {
        button->setVisible(inIap);
        button->setEnabled(idle);
    }

    iapButton_->setText(inIap ? tr("Leave &IAP")
                              : tr("Reboot into &IAP"));
    iapButton_->setVisible(haveDevice);
    iapButton_->setEnabled(idle);
    iapButton_->setToolTip(inIap
        ? tr("Reboot the board and run the active APP slot again")
        : tr("Reboot the board into its bootloader (IAP mode)"));
}

void MainWindow::onIapButtonClicked()
{
    if (upgrading_ || !iapButton_)
        return;

    /* Leave the bootloader: the board runs its active slot again */
    if (deviceMode_ == DeviceMode::IapBootloader) {
        appendLog(tr("Rebooting the device out of IAP mode ..."));

        QApplication::setOverrideCursor(Qt::WaitCursor);
        QString error;
        const bool ok = iapctl_reboot(iapVid(), iapPid(), error);
        QApplication::restoreOverrideCursor();

        if (!ok) {
            appendLog(tr("Leaving IAP failed: %1").arg(error), true);
            QMessageBox::critical(this, tr("Failed"), error);
            return;
        }

        appendLog(tr("Reboot request accepted, the device restarts ..."));
        setBusy(true);
        QTimer::singleShot(2000, this, [this]() {
            setBusy(false);
            refreshDeviceList();
        });
        return;
    }

    /* Application mode: ask the board to reboot into its bootloader */
    if (deviceMode_ != DeviceMode::AppRunning)
        return;

    /* No firmware file needed - the worker stops right after the switch */
    IapWorker::Config config = buildIapWorkerConfig();
    config.onlyEnterIap = true;
    config.firmwarePath.clear();

    startIapWorker(config, true);
}

/* ==========================================================================
 * Bootloader control: reboot / slot switch
 *
 * Both commands exist only in the IAP bootloader, so they are offered only
 * while a board actually sits there. They are single HID round trips (the
 * firmware answers, then acts), which is short enough to do on the GUI thread
 * with a busy cursor.
 * ========================================================================== */

/** True when the bootloader commands can be sent right now */
bool MainWindow::bootloaderControlAvailable() const
{
    return deviceMode_ == DeviceMode::IapBootloader && !upgrading_;
}

/*
 * The commands stay clickable even when they cannot run: a greyed out entry
 * with no explanation reads like a broken feature. Clicking it then tells the
 * user what is missing, which is what the command line version does with its
 * "no device in IAP mode" error.
 */
void MainWindow::updateBootloaderActions()
{
    const QString hint = upgrading_
        ? tr("Not available while an upgrade is running")
        : (deviceMode_ == DeviceMode::IapBootloader
               ? QString()
               : tr("Needs a board that sits in the IAP bootloader"));

    rebootAction_->setToolTip(hint);
    slotMenu_->setToolTip(hint);
}

/** Why a bootloader command cannot run right now, and what to do about it */
void MainWindow::reportBootloaderUnavailable()
{
    if (upgrading_) {
        QMessageBox::information(this, tr("Not Available"),
                                 tr("Wait for the running upgrade to finish."));
        return;
    }

    appendLog(tr("This command needs a board that sits in the IAP bootloader, "
                 "the current device is in application mode."), true);
    QMessageBox::information(
        this, tr("Not Available"),
        tr("No CH32H417 device in IAP mode found.\n"
           "These commands need a board that sits in the bootloader "
           "(power-cycle it with the button held)."));
}

void MainWindow::onRebootDevice()
{
    if (!bootloaderControlAvailable()) {
        reportBootloaderUnavailable();
        return;
    }

    appendLog(tr("Rebooting the device into its active slot ..."));

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString error;
    const bool ok = iapctl_reboot(iapVid(), iapPid(), error);
    QApplication::restoreOverrideCursor();

    if (!ok) {
        appendLog(tr("Reboot failed: %1").arg(error), true);
        QMessageBox::critical(this, tr("Failed"), error);
        return;
    }

    appendLog(tr("Reboot request accepted, the device restarts ..."));

    /* The board reboots into its slot, so it comes back as an application
       device - give it a moment, then let the device list catch up */
    setBusy(true);
    QTimer::singleShot(2000, this, [this]() {
        setBusy(false);
        refreshDeviceList();
    });
}

void MainWindow::onSlotActionTriggered()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        runSlotSwitch(action->data().toInt());
}

/** Make another slot active and boot it (menu entries and the buttons) */
void MainWindow::runSlotSwitch(int slot)
{
    if (!bootloaderControlAvailable()) {
        reportBootloaderUnavailable();
        return;
    }

    if (slot < 0 || slot >= IAP_APP_SLOT_NUM)
        return;

    appendLog(tr("Switching to APP slot %1 (0x%2) ...")
                  .arg(slot).arg(iapctl_slot_base_address(slot), 8, 16, QChar('0')));

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString error;
    const bool ok = iapctl_set_slot(iapVid(), iapPid(), slot, error);
    QApplication::restoreOverrideCursor();

    if (!ok) {
        appendLog(tr("Slot switch failed: %1").arg(error), true);
        QMessageBox::critical(this, tr("Failed"), error);
        return;
    }

    appendLog(tr("Slot %1 is now active, the device reboots into it ...").arg(slot));

    setBusy(true);
    QTimer::singleShot(2000, this, [this]() {
        setBusy(false);
        refreshDeviceList();
    });
}

void MainWindow::onAutoRefreshTimeout()
{
    if (!upgrading_)
        refreshDeviceList();
}

void MainWindow::onDeviceIndexChanged(int index)
{
    if (index < 0 || index >= devices_.size())
        return;

    appDeviceIndex_ = devices_.at(index).index;
    appDevice_ = devices_.at(index);
    deviceCombo_->setToolTip(devices_.at(index).description());

    /* Re-evaluate the V2 lock (BIN base address + IAP VID/PID) after a switch */
    updateV2Lock();

    if (devices_.at(index).isIap) {
        /* The firmware version cannot be queried in IAP mode */
        versionValid_ = false;
        versionQueriedKey_.clear();
        updateDeviceStatusText();
        return;
    }

    if (devices_.at(index).viaSerial()) {
        /* The USB-to-UART application has no version command */
        versionValid_ = false;
        versionQueriedKey_ = deviceKey(devices_.at(index));
        updateDeviceStatusText();
        return;
    }

    quint8 swVer = 0, hwVer = 0;
    QString error;
    if (ch375dev_get_version_for(devices_.at(index), swVer, hwVer, error)) {
        versionValid_ = true;
        versionQueriedKey_ = deviceKey(devices_.at(index));
        swVersion_ = swVer;
        hwVersion_ = hwVer;
        updateDeviceStatusText();
    }
}

void MainWindow::appendCh375Log(int level, const QString &message)
{
    if (level > CH375_LOG_INFO)     /* standalone mode shows warn/error/info only */
        return;
    appendLog(QString("[CH375] %1").arg(message), level == CH375_LOG_ERROR);
}

/* ==========================================================================
 * Firmware file
 * ========================================================================== */

void MainWindow::onBrowseFirmware()
{
    const QString path = QFileDialog::getOpenFileName(
        this,
        tr("Select Firmware File"),
        QFileInfo(fileEdit_->text()).absolutePath(),
        tr("Firmware Files (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;Binary Files (*.bin);;All Files (*.*)"));

    if (!path.isEmpty())
        fileEdit_->setText(path);
}

void MainWindow::onFirmwarePathChanged(const QString &path)
{
    Q_UNUSED(path);
    updateFirmwareInfo();
}

void MainWindow::updateFirmwareInfo()
{
    const QString path = fileEdit_->text().trimmed();

    if (path.isEmpty() || !QFileInfo(path).exists()) {
        firmwareInfoLabel_->setText(
            tr("<font color='%1'>No valid firmware file selected</font>").arg(statusColor(2)));
        return;
    }

    QString error;
    FirmwareImage image;

    if (!firmware_load(path, binBaseAddress(), image, error)) {
        firmwareInfoLabel_->setText(
            tr("<font color='%1'>%2</font>").arg(statusColor(2)).arg(error.toHtmlEscaped()));
        return;
    }

    firmwareInfoLabel_->setText(
        tr("%1  Size: %2  Address: 0x%3 - 0x%4  Checksum: 0x%5")
            .arg(image.fromHex ? tr("Intel HEX") : tr("BIN"))
            .arg(firmware_format_size(image.data.size()))
            .arg(image.startAddress, 8, 16, QChar('0'))
            .arg(image.endAddress, 8, 16, QChar('0'))
            .arg(image.checksum, 8, 16, QChar('0')));
}

/* ==========================================================================
 * Upgrade sequence
 * ========================================================================== */

void MainWindow::setBusy(bool busy)
{
    upgrading_ = busy;
    startButton_->setEnabled(!busy);
    refreshButton_->setEnabled(!busy);
    browseButton_->setEnabled(!busy);
    fileEdit_->setEnabled(!busy);
    deviceCombo_->setEnabled(!busy && !devices_.isEmpty());
    /* Fields locked by the V2 detection stay read only and must not become
       editable again just because the busy state changed */
    baseAddressCombo_->setEnabled(!busy);
    iapVidEdit_->setEnabled(!busy && !binBaseAddressLocked_);
    iapPidEdit_->setEnabled(!busy && !binBaseAddressLocked_);
    updateBootloaderActions();
    updateIapButton();
}

void MainWindow::onStartUpgrade()
{
    if (upgrading_)
        return;

    const QString path = fileEdit_->text().trimmed();
    if (path.isEmpty() || !QFileInfo(path).exists()) {
        QMessageBox::warning(this, tr("Hint"), tr("Please select a valid firmware file first."));
        return;
    }

    if (deviceMode_ == DeviceMode::NotFound) {
        const int ret = QMessageBox::question(
            this, tr("No Device Found"),
            tr("No CH32H417 device was detected.\n\n"
               "If the device is already in IAP mode (for example powered up with "
               "the button held down), you can continue;\n"
               "otherwise please connect the device first.\n\nContinue?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (ret != QMessageBox::Yes)
            return;
    }

    FirmwareImage image;
    QString error;
    if (!firmware_load(path, binBaseAddress(), image, error)) {
        QMessageBox::critical(this, tr("Firmware Error"), error);
        return;
    }

    startIapWorker(buildIapWorkerConfig(), false);
}

/** Describe the currently selected device, the way the worker will reach it */
IapWorker::Config MainWindow::buildIapWorkerConfig() const
{
    IapWorker::Config config;
    config.firmwarePath = fileEdit_->text().trimmed();
    config.binBaseAddress = binBaseAddress();
    config.iapVid = iapVid();
    config.iapPid = iapPid();
    config.alreadyInIap = (deviceMode_ == DeviceMode::IapBootloader);
    config.ch375Index = (deviceMode_ == DeviceMode::AppRunning) ? appDeviceIndex_ : -1;
    config.viaLibusb = (deviceMode_ == DeviceMode::AppRunning) && appDevice_.viaLibusb();
    config.libusbBus = appDevice_.bus;
    config.libusbAddress = appDevice_.address;
    config.viaSerial = (deviceMode_ == DeviceMode::AppRunning) && appDevice_.viaSerial();
    config.serialPort = appDevice_.comPort;
    config.deviceBusy = (deviceMode_ == DeviceMode::DeviceBusy) || appDevice_.busy;
    config.hidWaitSeconds = 15;
    return config;
}

/** Clear the log, show what is about to happen and run the worker */
void MainWindow::startIapWorker(const IapWorker::Config &config, bool iapOnly)
{
    logView_->clear();
    progressBar_->setValue(0);
    progressState_ = ProgressState::Running;
    progressLabel_->setText(tr("Preparing ..."));
    iapOnlyRun_ = iapOnly;
    setBusy(true);

    if (deviceMode_ == DeviceMode::IapBootloader) {
        appendLog(tr("Target device: IAP HID (VID:0x%1 PID:0x%2)")
                      .arg(config.iapVid, 4, 16, QChar('0'))
                      .arg(config.iapPid, 4, 16, QChar('0')));
    } else if (config.viaSerial) {
        appendLog(tr("Target device: serial (COM port %1)").arg(config.serialPort));
    } else if (config.viaLibusb) {
        appendLog(tr("Target device: libusb (bus %1, address %2)")
                      .arg(config.libusbBus).arg(config.libusbAddress));
    } else {
        appendLog(tr("Target device: CH375 #%1").arg(config.ch375Index));
    }

    worker_ = new IapWorker(config);
    workerThread_ = new QThread(this);
    worker_->moveToThread(workerThread_);

    connect(workerThread_, &QThread::started, worker_, &IapWorker::run);
    connect(worker_, &IapWorker::progressUpdated, this, &MainWindow::onProgressUpdated);
    connect(worker_, &IapWorker::logMessage, this, &MainWindow::onLogMessage);
    connect(worker_, &IapWorker::finished, this, &MainWindow::onUpgradeFinished);
    connect(worker_, &IapWorker::finished, worker_, &IapWorker::deleteLater);
    connect(worker_, &IapWorker::finished, workerThread_, &QThread::quit);
    connect(workerThread_, &QThread::finished, workerThread_, &QObject::deleteLater);

    workerThread_->start();
}

void MainWindow::onProgressUpdated(int percent, const QString &status)
{
    progressBar_->setValue(percent);
    progressLabel_->setText(status);
}

void MainWindow::onLogMessage(const QString &message)
{
    appendLog(message);
}

void MainWindow::onUpgradeFinished(bool success, const QString &message)
{
    setBusy(false);
    worker_ = nullptr;
    workerThread_ = nullptr;

    /* The "reboot into IAP" button only switches the board over - it did not
       download anything, so it must not claim the firmware was upgraded */
    if (iapOnlyRun_) {
        const bool enteredIap = success;
        iapOnlyRun_ = false;

        if (enteredIap) {
            progressState_ = ProgressState::Succeeded;
            progressLabel_->setText(tr("Device is in IAP Mode"));
            appendLog(message);
            QTimer::singleShot(500, this, &MainWindow::onRefreshDevices);
        } else {
            progressState_ = ProgressState::Failed;
            progressLabel_->setText(tr("Failed"));
            appendLog(message, true);
            appendLog(tr("Please power-cycle the device (disconnect and reconnect "
                         "the USB cable or the power supply) and run the upgrade again."),
                      true);
            QMessageBox::critical(this, tr("Failed"), message);
        }
        return;
    }

    if (success) {
        progressBar_->setValue(100);
        progressState_ = ProgressState::Succeeded;
        progressLabel_->setText(tr("Upgrade Complete"));
        appendLog(message);
        QMessageBox::information(this, tr("Complete"),
                                 tr("Firmware upgrade succeeded!\n"
                                    "The device will restart and run the new firmware."));
    } else {
        progressState_ = ProgressState::Failed;
        progressLabel_->setText(tr("Upgrade Failed"));
        appendLog(message, true);
        appendLog(tr("Please power-cycle the device (disconnect and reconnect "
                     "the USB cable or the power supply) and run the upgrade again."),
                  true);
        QMessageBox::critical(this, tr("Failed"),
                              message + QStringLiteral("\n\n")
                                  + tr("Please power-cycle the device (disconnect and "
                                       "reconnect the USB cable or the power supply) "
                                       "and run the upgrade again."));
    }

    QTimer::singleShot(500, this, &MainWindow::onRefreshDevices);
}

/** Rebuild the progress text for the current state (reused on language switch) */
void MainWindow::updateProgressText()
{
    switch (progressState_) {
    case ProgressState::Running:
        /* Texts produced during the upgrade come from the worker thread in the
           language that was active then; the next message updates them */
        break;
    case ProgressState::Succeeded:
        progressLabel_->setText(tr("Upgrade Complete"));
        break;
    case ProgressState::Failed:
        progressLabel_->setText(tr("Upgrade Failed"));
        break;
    case ProgressState::Idle:
    default:
        progressLabel_->setText(tr("Ready"));
        break;
    }
}

/* Log colours follow the current theme: bright text on dark, always readable */
QString MainWindow::logTextColor() const
{
    if (ThemeManager::instance()->isDark())
        return QStringLiteral("#DDDDDD");
    return palette().color(QPalette::Text).name();
}

QString MainWindow::logErrorColor() const
{
    return ThemeManager::instance()->isDark() ? QStringLiteral("#FF8080")
                                             : QStringLiteral("#C00000");
}

void MainWindow::appendLogLine(const LogEntry &entry)
{
    const QString color = entry.isError ? logErrorColor() : logTextColor();
    const QString line = QStringLiteral("<span style='color:%1'>[%2] %3</span>")
                             .arg(color)
                             .arg(entry.time.toHtmlEscaped())
                             .arg(entry.text.toHtmlEscaped());
    logView_->append(line);
    logView_->ensureCursorVisible();
}

void MainWindow::appendLog(const QString &message, bool isError)
{
    LogEntry entry;
    entry.time = QDateTime::currentDateTime().toString(QStringLiteral("hh:mm:ss"));
    entry.text = message;
    entry.isError = isError;

    logEntries_.append(entry);
    /* Keep the buffer from growing without bound during long sessions */
    while (logEntries_.size() > 2000)
        logEntries_.removeFirst();

    appendLogLine(entry);
}

/** Redraw the whole log with the new colours after a theme change */
void MainWindow::renderLog()
{
    logView_->clear();
    for (const LogEntry &entry : logEntries_)
        appendLogLine(entry);
}

void MainWindow::onClearLog()
{
    logEntries_.clear();
    logView_->clear();
}

void MainWindow::showAbout()
{
    QMessageBox box(this);
    box.setWindowTitle(tr("About"));
    box.setIconPixmap(QPixmap(QStringLiteral(":/icons/logo_128"))
                          .scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    box.setText(
        tr("<h3>CH32H417 Logic Analyzer<br>Firmware Upgrade Tool</h3>"
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
           "WinUSB when the board is bound to libusb.</p>")
            .arg(QApplication::applicationVersion())
            .arg(QString::fromLatin1(qVersion())));
    box.setTextFormat(Qt::RichText);
    box.setStandardButtons(QMessageBox::Ok);
    box.exec();
}

/* ==========================================================================
 * Drag and drop / closing
 * ========================================================================== */

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;

    const QString path = urls.first().toLocalFile();
    if (!path.isEmpty()) {
        fileEdit_->setText(path);
        event->acceptProposedAction();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (upgrading_) {
        const int ret = QMessageBox::warning(
            this, tr("Upgrade in Progress"),
            tr("An upgrade is running; exiting now may corrupt the device firmware.\n"
               "Are you sure you want to exit?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (ret != QMessageBox::Yes) {
            event->ignore();
            return;
        }
    }

    saveSettings();
    event->accept();
}
