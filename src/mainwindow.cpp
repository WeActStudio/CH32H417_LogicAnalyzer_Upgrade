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
    return elideMiddle(info.modelName(), kDeviceLabelMaxChars);
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
    , baseAddressEdit_(nullptr)
    , baseAddressHintLabel_(nullptr)
    , binBaseAddressLocked_(false)
    , iapVidEdit_(nullptr)
    , iapPidEdit_(nullptr)
    , progressBar_(nullptr)
    , progressLabel_(nullptr)
    , logView_(nullptr)
    , logTitleLabel_(nullptr)
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
    , versionQueriedIndex_(-2)
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

    baseAddressEdit_ = new QLineEdit("08006000", fwGroup_);
    baseAddressEdit_->setMaximumWidth(120);
    baseAddressLabel_ = new QLabel(fwGroup_);
    baseAddressHintLabel_ = new QLabel(fwGroup_);
    baseAddressHintLabel_->setStyleSheet(QStringLiteral("color: gray;"));

    QHBoxLayout *baseRow = new QHBoxLayout();
    baseRow->addWidget(baseAddressEdit_);
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
    startButton_ = new QPushButton(central);
    exitButton_ = new QPushButton(central);
    buttonLayout->addWidget(startButton_);
    buttonLayout->addWidget(exitButton_);
    mainLayout->addLayout(buttonLayout);

    setCentralWidget(central);

    connect(refreshButton_, &QPushButton::clicked, this, &MainWindow::onRefreshDevices);
    connect(browseButton_, &QPushButton::clicked, this, &MainWindow::onBrowseFirmware);
    connect(startButton_, &QPushButton::clicked, this, &MainWindow::onStartUpgrade);
    connect(exitButton_, &QPushButton::clicked, this, &MainWindow::close);
    connect(fileEdit_, &QLineEdit::textChanged, this, &MainWindow::onFirmwarePathChanged);
    connect(deviceCombo_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onDeviceIndexChanged);

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
    clearLogAction_ = new QAction(this);
    toolMenu_->addAction(refreshAction_);
    toolMenu_->addAction(clearLogAction_);
    connect(refreshAction_, &QAction::triggered, this, &MainWindow::onRefreshDevices);
    connect(clearLogAction_, &QAction::triggered, this, &MainWindow::onClearLog);

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
    baseAddressEdit_->setToolTip(tr("Programming start address for .bin files (hexadecimal, e.g. 08006000)"));
    fileEdit_->setPlaceholderText(tr("Select or drop a .hex / .bin firmware file"));

    logTitleLabel_->setText(tr("Upgrade Log"));
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
    baseAddressEdit_->setText(settings.value("binBaseAddress", "08006000").toString());
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
    settings.setValue("binBaseAddress", baseAddressEdit_->text());
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
    bool ok = false;
    const quint32 value = baseAddressEdit_->text().trimmed().toUInt(&ok, 16);
    return ok ? value : 0x08006000u;
}

void MainWindow::updateBaseAddressHint()
{
    /* V2 devices lock the address and grey out the field, so no extra hint is
       needed here, only the note about the number base */
    baseAddressHintLabel_->setText(tr("Hexadecimal, e.g. 08006000"));
}

/*
 * On the WeAct Studio Logic Analyzer V2 both the application start address and
 * the IAP VID/PID are fixed. When a V2 board is detected the values are filled
 * in automatically and locked, to keep the user from bricking the device.
 */
void MainWindow::updateV2Lock()
{
    const int current = deviceCombo_->currentIndex();
    const bool v2 = !devices_.isEmpty() && current >= 0 && current < devices_.size()
                    && devices_.at(current).modelName()
                           == QLatin1String("WeAct Studio Logic Analyzer V2");

    binBaseAddressLocked_ = v2;

    if (v2) {
        baseAddressEdit_->setText(QStringLiteral("08006000"));
        iapVidEdit_->setText(QStringLiteral("1A86"));
        iapPidEdit_->setText(QStringLiteral("FE17"));
    }

    baseAddressEdit_->setReadOnly(v2);
    baseAddressEdit_->setEnabled(!v2 && !upgrading_);
    baseAddressEdit_->setFocusPolicy(v2 ? Qt::NoFocus : Qt::StrongFocus);
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
                                            appDeviceIndex_, devices_, error);
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
    case DeviceMode::AppRunning:
        /*
         * Re-read the version only when the device changed or when the previous
         * read failed. Unplugging and plugging back in keeps the same index, so
         * a pure "index changed" test would never re-read and the UI would stay
         * at "read failed"; a failure must therefore allow a retry next time.
         */
        if (appDeviceIndex_ != versionQueriedIndex_ || !versionValid_) {
            versionValid_ = ch375dev_get_version(appDeviceIndex_, swVersion_, hwVersion_, error);
            if (versionValid_) {
                versionQueriedIndex_ = appDeviceIndex_;
                deviceDetectError_.clear();
            } else {
                versionQueriedIndex_ = -2;      /* keep retrying on the next refresh */
                deviceDetectError_ = error;
            }
        }
        break;

    case DeviceMode::IapBootloader:
    default:
        versionValid_ = false;
        versionQueriedIndex_ = -2;              /* not in application mode, re-read when it reconnects */
        break;
    }

    updateDeviceStatusText();
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
        deviceStatusLabel_->setText(
            tr("<font color='%1'>Connected (application mode, CH375 channel)</font>").arg(statusColor(0)));
        /* Only the numeric version is shown, e.g. v1.1 */
        deviceVersionLabel_->setText(
            versionValid_
                ? QStringLiteral("v%1.%2").arg(swVersion_).arg(hwVersion_)
                : tr("Read failed"));
        deviceVersionLabel_->setToolTip(
            versionValid_
                ? tr("Software version: v%1  Hardware version: v%2").arg(swVersion_).arg(hwVersion_)
                : deviceDetectError_);
        break;

    case DeviceMode::IapBootloader:
        deviceStatusLabel_->setText(
            tr("<font color='%1'>Connected (IAP upgrade mode)</font>").arg(statusColor(1)));
        deviceVersionLabel_->setText(tr("-"));
        deviceVersionLabel_->setToolTip(QString());
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
    deviceCombo_->setToolTip(devices_.at(index).description());

    /* Re-evaluate the V2 lock (BIN base address + IAP VID/PID) after a switch */
    updateV2Lock();

    if (devices_.at(index).isIap) {
        /* The firmware version cannot be queried in IAP mode */
        versionValid_ = false;
        versionQueriedIndex_ = -2;
        updateDeviceStatusText();
        return;
    }

    quint8 swVer = 0, hwVer = 0;
    QString error;
    if (ch375dev_get_version(appDeviceIndex_, swVer, hwVer, error)) {
        versionValid_ = true;
        versionQueriedIndex_ = appDeviceIndex_;
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
    baseAddressEdit_->setEnabled(!busy && !binBaseAddressLocked_);
    iapVidEdit_->setEnabled(!busy && !binBaseAddressLocked_);
    iapPidEdit_->setEnabled(!busy && !binBaseAddressLocked_);
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

    IapWorker::Config config;
    config.firmwarePath = path;
    config.binBaseAddress = binBaseAddress();
    config.iapVid = iapVid();
    config.iapPid = iapPid();
    config.alreadyInIap = (deviceMode_ == DeviceMode::IapBootloader);
    config.ch375Index = (deviceMode_ == DeviceMode::AppRunning) ? appDeviceIndex_ : -1;
    config.hidWaitSeconds = 15;

    logView_->clear();
    progressBar_->setValue(0);
    progressState_ = ProgressState::Running;
    progressLabel_->setText(tr("Preparing ..."));
    setBusy(true);

    appendLog(tr("Target device: %1").arg(deviceMode_ == DeviceMode::AppRunning
                                    ? QString("CH375 #%1").arg(appDeviceIndex_)
                                    : QString("IAP HID (VID:0x%1 PID:0x%2)")
                                          .arg(config.iapVid, 4, 16, QChar('0'))
                                          .arg(config.iapPid, 4, 16, QChar('0'))));

    worker_ = new IapWorker(config);
    workerThread_ = new QThread(this);
    worker_->moveToThread(workerThread_);

    connect(workerThread_, &QThread::started, worker_, &IapWorker::run);
    connect(worker_, &IapWorker::progressUpdated, this, &MainWindow::onProgressUpdated);
    connect(worker_, &IapWorker::logMessage, this, &MainWindow::onLogMessage);
    connect(worker_, &IapWorker::finished, this, &MainWindow::onUpgradeFinished);
    connect(worker_, &IapWorker::finished, worker_, &IapWorker::deleteLater);
    connect(worker_, &IapWorker::finished, workerThread_, &QThread::quit);
    connect(workerThread_, &QThread::finished, workerThread_, &QThread::deleteLater);

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
           "<p>Upgrade sequence: the enter-IAP command is sent over the CH375 "
           "channel, the device resets into a HID IAP device, then erase / "
           "program / verify / finish.</p>"
           "<p>The CH375 driver must be installed.</p>")
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
