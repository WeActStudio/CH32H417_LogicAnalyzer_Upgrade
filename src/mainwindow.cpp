/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * 主窗口实现
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

/* 设备列表里单行最多显示的字符数，超出部分省略并在 tooltip 里给出完整信息 */
const int kDeviceLabelMaxChars = 56;

/*
 * 中间省略：头部保留 VID/PID，尾部保留型号与序列号（这两段最有辨识度），
 * 被截掉的是中间相对次要的部分。完整内容始终可在 tooltip 中查看。
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
 * 设备列表单行文字：索引/IAP 标记 + VID/PID + **完整型号** + 序列号。
 * 型号一律完整显示（用户靠它区分设备），长度超出时只省略序列号；
 * 完整信息仍写在 tooltip 里。
 */
QString deviceListLabel(const Ch375DeviceInfo &info)
{
    /* 运行模式显示 CH375 索引；IAP 模式没有 CH375 索引，改用通道标记 */
    const QString tag = info.isIap ? QStringLiteral("IAP")
                                   : QStringLiteral("#%1").arg(info.index);

    QString label = QStringLiteral("%1  %2  %3")
                        .arg(tag)
                        .arg(info.idString())
                        .arg(info.modelName());

    if (info.serial.isEmpty())
        return label;

    const QLatin1String snPrefix("  SN:");
    const int avail = kDeviceLabelMaxChars - label.size() - snPrefix.size();
    if (avail >= 8)
        label += snPrefix + elideMiddle(info.serial, avail);

    return label;
}

MainWindow *g_mainWindow = nullptr;

/* CH375 DLL 内部日志桥接到界面（可能在后台线程被调用） */
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
    , cancelButton_(nullptr)
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
 * 界面搭建
 * ========================================================================== */

void MainWindow::setupUi()
{
    setMinimumSize(680, 620);

    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setSpacing(10);

    /* ---------- 设备区 ---------- */
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

    /* ---------- 固件区 ---------- */
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

    /* ---------- IAP 选项 ---------- */
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

    /* ---------- 进度 ---------- */
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

    /* ---------- 日志 ---------- */
    logTitleLabel_ = new QLabel(central);
    mainLayout->addWidget(logTitleLabel_);
    logView_ = new QTextEdit(central);
    logView_->setReadOnly(true);
    QFont monoFont("Consolas", 9);
    monoFont.setStyleHint(QFont::Monospace);
    logView_->setFont(monoFont);
    logView_->setMinimumHeight(180);
    mainLayout->addWidget(logView_, 1);

    /* ---------- 按钮 ---------- */
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(1);
    startButton_ = new QPushButton(central);
    cancelButton_ = new QPushButton(central);
    exitButton_ = new QPushButton(central);
    cancelButton_->setEnabled(false);
    buttonLayout->addWidget(startButton_);
    buttonLayout->addWidget(cancelButton_);
    buttonLayout->addWidget(exitButton_);
    mainLayout->addLayout(buttonLayout);

    setCentralWidget(central);

    connect(refreshButton_, &QPushButton::clicked, this, &MainWindow::onRefreshDevices);
    connect(browseButton_, &QPushButton::clicked, this, &MainWindow::onBrowseFirmware);
    connect(startButton_, &QPushButton::clicked, this, &MainWindow::onStartUpgrade);
    connect(cancelButton_, &QPushButton::clicked, this, &MainWindow::onCancelUpgrade);
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

    /* ---------- 主题菜单（浅色 / 深色 / 跟随系统） ---------- */
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

    /* ---------- 语言菜单 ---------- */
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
    connect(aboutAction_, &QAction::triggered, this, &MainWindow::onAbout);

    /* 语言切换后同步菜单勾选状态 */
    connect(LanguageManager::instance(), &LanguageManager::languageChanged,
            this, &MainWindow::onLanguageChanged);
}

/** 把所有界面文字设置为当前语言（构造时与切换语言时都会调用） */
void MainWindow::retranslateUi()
{
    setWindowTitle(tr("CH32H417 逻辑分析仪固件升级工具"));

    /* 分组框 */
    deviceGroup_->setTitle(tr("设备"));
    fwGroup_->setTitle(tr("固件文件"));
    optGroup_->setTitle(tr("IAP 参数"));

    /* 行标题 */
    deviceListLabel_->setText(tr("设备列表："));
    deviceStatusTitleLabel_->setText(tr("设备状态："));
    deviceVersionTitleLabel_->setText(tr("固件版本："));
    filePathLabel_->setText(tr("文件路径："));
    firmwareInfoTitleLabel_->setText(tr("固件信息："));
    /* 输入框里只填十六进制数字，0x 前缀由标签给出 */
    baseAddressLabel_->setText(tr("BIN 基地址：0x"));
    updateBaseAddressHint();
    iapVidLabel_->setText(tr("VID：0x"));
    iapPidLabel_->setText(tr("PID：0x"));
    iapHintLabel_->setText(tr("默认值 VID=0x1A86 PID=0xFE17"));

    /* 控件 */
    refreshButton_->setText(tr("刷新(&R)"));
    browseButton_->setText(tr("浏览(&B)..."));
    baseAddressEdit_->setToolTip(tr(".bin 文件的烧录起始地址（十六进制，例如 08006000）"));
    fileEdit_->setPlaceholderText(tr("选择或直接拖入 .hex / .bin 固件文件"));

    logTitleLabel_->setText(tr("升级日志："));
    startButton_->setText(tr("开始升级(&S)"));
    cancelButton_->setText(tr("取消(&C)"));
    exitButton_->setText(tr("退出(&X)"));

    /*
     * 菜单（事件在构造早期也可能到达，此时菜单尚未创建，需要判空）
     */
    if (fileMenu_) {
        fileMenu_->setTitle(tr("文件(&F)"));
        openAction_->setText(tr("打开固件(&O)..."));
        exitAction_->setText(tr("退出(&X)"));
        toolMenu_->setTitle(tr("工具(&T)"));
        refreshAction_->setText(tr("刷新设备(&R)"));
        clearLogAction_->setText(tr("清空日志(&L)"));
        viewMenu_->setTitle(tr("视图(&V)"));
        langMenu_->setTitle(tr("语言(&L)"));
        helpMenu_->setTitle(tr("帮助(&H)"));
        aboutAction_->setText(tr("关于(&A)"));

        /* 语言菜单项 */
        const QStringList names = LanguageManager::preferenceNames();
        for (int i = 0; i < langActions_.size() && i < names.size(); ++i)
            langActions_.at(i)->setText(names.at(i));

        /* 主题菜单项 */
        for (int i = 0; i < themeActions_.size() && i < 3; ++i)
            themeActions_.at(i)->setText(
                ThemeManager::modeName(static_cast<ThemeManager::Mode>(i)));
    }

    /* 动态文本 */
    updateDeviceStatusText();
    updateFirmwareInfo();
    updateProgressText();
}

/* ==========================================================================
 * 语言切换
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

    /* 日志与状态文字的配色随主题变化，需要整体重绘 */
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
 * 设置存取
 * ========================================================================== */

void MainWindow::loadSettings()
{
    QSettings settings(kSettingsOrg, kSettingsApp);
    fileEdit_->setText(settings.value("firmwarePath").toString());
    baseAddressEdit_->setText(settings.value("binBaseAddress", "08006000").toString());
    iapVidEdit_->setText(settings.value("iapVid", "1A86").toString());
    iapPidEdit_->setText(settings.value("iapPid", "FE17").toString());
    restoreGeometry(settings.value("geometry").toByteArray());

    onLanguageChanged();     /* 同步语言菜单勾选状态 */
    onThemeChanged();        /* 同步主题菜单勾选状态 */
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
 * 设备
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
    /* V2 设备会锁定地址并置灰输入框，这里不再额外提示，只保留进制说明 */
    baseAddressHintLabel_->setText(tr("十六进制，例如 08006000"));
}

/*
 * WeAct Studio Logic Analyzer V2 的 APP 起始地址与 IAP 的 VID/PID 都是固定的，
 * 识别到 V2 时自动填好并禁止修改，避免用户填错把设备烧砖。
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
        deviceCombo_->addItem(tr("(未发现设备)"), -1);
        deviceCombo_->setEnabled(false);
        deviceCombo_->setToolTip(tr("未发现设备"));
    } else {
        for (const Ch375DeviceInfo &info : devices_) {
            const QString full = info.description();
            deviceCombo_->addItem(deviceListLabel(info), info.index);
            /* 完整信息放进 tooltip，鼠标悬停即可看到 VID/PID/序列号 */
            deviceCombo_->setItemData(deviceCombo_->count() - 1, full, Qt::ToolTipRole);
        }
        deviceCombo_->setEnabled(true);
        const int cur = deviceCombo_->currentIndex();
        deviceCombo_->setToolTip(
            cur >= 0 ? deviceCombo_->itemData(cur, Qt::ToolTipRole).toString() : QString());
    }

    /*
     * WeAct Studio Logic Analyzer V2 的 APP 起始地址固定为 0x08006000、
     * IAP 的 VID/PID 也是固定的，不允许用户修改，避免烧错区域把设备变砖。
     */
    updateV2Lock();

    deviceCombo_->blockSignals(false);

    switch (mode) {
    case DeviceMode::AppRunning:
        /*
         * 只在设备变化、或上次读取失败时重新读版本。
         * 拔掉再插上时索引没变，若只用「索引变化」判断就不会重读，
         * 会一直停在"读取失败"，所以失败时必须允许下次刷新重试。
         */
        if (appDeviceIndex_ != versionQueriedIndex_ || !versionValid_) {
            versionValid_ = ch375dev_get_version(appDeviceIndex_, swVersion_, hwVersion_, error);
            if (versionValid_) {
                versionQueriedIndex_ = appDeviceIndex_;
                deviceDetectError_.clear();
            } else {
                versionQueriedIndex_ = -2;      /* 下次刷新继续重试 */
                deviceDetectError_ = error;
            }
        }
        break;

    case DeviceMode::IapBootloader:
    default:
        versionValid_ = false;
        versionQueriedIndex_ = -2;              /* 设备不在运行模式，下次连上要重新读 */
        break;
    }

    updateDeviceStatusText();
}

/** 状态文字配色：kind 0=已连接 1=IAP 模式 2=未发现（随深浅色自动调整） */
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

/** 根据设备状态重建设备区文字（语言切换 / 主题切换时复用） */
void MainWindow::updateDeviceStatusText()
{
    switch (deviceMode_) {
    case DeviceMode::AppRunning:
        deviceStatusLabel_->setText(
            tr("<font color='%1'>已连接（运行模式，CH375 通道）</font>").arg(statusColor(0)));
        /* 只显示数字版本号，例如 v1.1 */
        deviceVersionLabel_->setText(
            versionValid_
                ? QStringLiteral("v%1.%2").arg(swVersion_).arg(hwVersion_)
                : tr("读取失败"));
        deviceVersionLabel_->setToolTip(
            versionValid_
                ? tr("软件版本：v%1　硬件版本：v%2").arg(swVersion_).arg(hwVersion_)
                : deviceDetectError_);
        break;

    case DeviceMode::IapBootloader:
        deviceStatusLabel_->setText(
            tr("<font color='%1'>已连接（IAP 升级模式，HID 通道）</font>").arg(statusColor(1)));
        deviceVersionLabel_->setText(tr("-"));
        deviceVersionLabel_->setToolTip(QString());
        break;

    default:
        deviceStatusLabel_->setText(
            tr("<font color='%1'>未发现设备</font>").arg(statusColor(2)));
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

    /* 切换设备后重新判断 V2 锁定（BIN 基地址 + IAP 的 VID/PID） */
    updateV2Lock();

    if (devices_.at(index).isIap) {
        /* IAP 模式无法查询固件版本 */
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
    if (level > CH375_LOG_INFO)     /* 独立模式下只显示 warn/error/info */
        return;
    appendLog(QString("[CH375] %1").arg(message), level == CH375_LOG_ERROR);
}

/* ==========================================================================
 * 固件文件
 * ========================================================================== */

void MainWindow::onBrowseFirmware()
{
    const QString path = QFileDialog::getOpenFileName(
        this,
        tr("选择固件文件"),
        QFileInfo(fileEdit_->text()).absolutePath(),
        tr("固件文件 (*.hex *.bin *.ihex);;Intel HEX (*.hex *.ihex);;二进制文件 (*.bin);;所有文件 (*.*)"));

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
            tr("<font color='%1'>尚未选择有效的固件文件</font>").arg(statusColor(2)));
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
        tr("%1　大小：%2　地址：0x%3 - 0x%4　校验和：0x%5")
            .arg(image.fromHex ? tr("Intel HEX") : tr("BIN"))
            .arg(firmware_format_size(image.data.size()))
            .arg(image.startAddress, 8, 16, QChar('0'))
            .arg(image.endAddress, 8, 16, QChar('0'))
            .arg(image.checksum, 8, 16, QChar('0')));
}

/* ==========================================================================
 * 升级流程
 * ========================================================================== */

void MainWindow::setBusy(bool busy)
{
    upgrading_ = busy;
    startButton_->setEnabled(!busy);
    refreshButton_->setEnabled(!busy);
    browseButton_->setEnabled(!busy);
    fileEdit_->setEnabled(!busy);
    deviceCombo_->setEnabled(!busy && !devices_.isEmpty());
    /* V2 锁定的输入框始终保持只读，不随 busy 状态恢复为可编辑 */
    baseAddressEdit_->setEnabled(!busy && !binBaseAddressLocked_);
    iapVidEdit_->setEnabled(!busy && !binBaseAddressLocked_);
    iapPidEdit_->setEnabled(!busy && !binBaseAddressLocked_);
    cancelButton_->setEnabled(busy);
}

void MainWindow::onStartUpgrade()
{
    if (upgrading_)
        return;

    const QString path = fileEdit_->text().trimmed();
    if (path.isEmpty() || !QFileInfo(path).exists()) {
        QMessageBox::warning(this, tr("提示"), tr("请先选择一个有效的固件文件。"));
        return;
    }

    if (deviceMode_ == DeviceMode::NotFound) {
        const int ret = QMessageBox::question(
            this, tr("未发现设备"),
            tr("当前没有检测到 CH32H417 设备。\n\n"
               "如果设备已经处于 IAP 模式（例如按住按键上电），可以继续升级；\n"
               "否则请先连接设备。\n\n是否继续？"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (ret != QMessageBox::Yes)
            return;
    }

    FirmwareImage image;
    QString error;
    if (!firmware_load(path, binBaseAddress(), image, error)) {
        QMessageBox::critical(this, tr("固件错误"), error);
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
    progressLabel_->setText(tr("准备中 ..."));
    setBusy(true);

    appendLog(tr("目标设备：%1").arg(deviceMode_ == DeviceMode::AppRunning
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

void MainWindow::onCancelUpgrade()
{
    if (!upgrading_ || !worker_)
        return;

    appendLog(tr("正在请求取消 ..."));
    cancelButton_->setEnabled(false);
    worker_->cancel();
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
        progressLabel_->setText(tr("升级完成"));
        appendLog(message);
        QMessageBox::information(this, tr("完成"),
                                 tr("固件升级成功！\n设备将重启并运行新固件。"));
    } else {
        progressState_ = ProgressState::Failed;
        progressLabel_->setText(tr("升级失败"));
        appendLog(message, true);
        QMessageBox::critical(this, tr("失败"), message);
    }

    QTimer::singleShot(500, this, &MainWindow::onRefreshDevices);
}

/** 根据当前状态重建进度文字（语言切换时复用） */
void MainWindow::updateProgressText()
{
    switch (progressState_) {
    case ProgressState::Running:
        /* 升级过程中的文字由工作线程按当时语言生成，切换语言后下一条消息会更新 */
        break;
    case ProgressState::Succeeded:
        progressLabel_->setText(tr("升级完成"));
        break;
    case ProgressState::Failed:
        progressLabel_->setText(tr("升级失败"));
        break;
    case ProgressState::Idle:
    default:
        progressLabel_->setText(tr("就绪"));
        break;
    }
}

/* 日志文字配色：跟随当前主题，深色下用亮色，保证始终可读 */
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
    /* 避免长时间运行后无限增长 */
    while (logEntries_.size() > 2000)
        logEntries_.removeFirst();

    appendLogLine(entry);
}

/** 主题切换后按新配色重绘整段日志 */
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

void MainWindow::onAbout()
{
    QMessageBox box(this);
    box.setWindowTitle(tr("关于"));
    box.setIconPixmap(QPixmap(QStringLiteral(":/icons/logo_128"))
                          .scaled(96, 96, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    box.setText(tr("<h3>CH32H417 逻辑分析仪固件升级工具</h3>"
                   "<p>版本：%1</p>"
                   "<p>基于 Qt 6 开发，使用 MSYS2 (MINGW64) 静态编译。</p>"
                   "<p>升级流程：CH375 通道发送进入 IAP 命令 → 设备复位为 HID IAP 设备 → "
                   "擦除 / 编程 / 校验 / 结束。</p>"
                   "<p>需要安装 CH375 驱动。</p>")
                    .arg(QApplication::applicationVersion()));
    box.setStandardButtons(QMessageBox::Ok);
    box.exec();
}

/* ==========================================================================
 * 拖放 / 关闭
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
            this, tr("正在升级"),
            tr("升级正在进行中，现在退出可能导致设备固件损坏。\n确定要退出吗？"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (ret != QMessageBox::Yes) {
            event->ignore();
            return;
        }
    }

    saveSettings();
    event->accept();
}
