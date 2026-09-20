/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * 主窗口
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QDragEnterEvent>
#include <QDropEvent>

#include "ch375dev.h"
#include "iapworker.h"

class QComboBox;
class QLineEdit;
class QLabel;
class QPushButton;
class QProgressBar;
class QTextEdit;
class QThread;
class QTimer;
class QMenu;
class QAction;
class QActionGroup;
class QGroupBox;
class QWidget;

/**
 * 升级工具主窗口
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void changeEvent(QEvent *event) override;

public Q_SLOTS:
    /* CH375 DLL 内部日志（可能来自工作线程，通过队列投递到界面） */
    void appendCh375Log(int level, const QString &message);

private Q_SLOTS:
    void onRefreshDevices();
    void onBrowseFirmware();
    void onStartUpgrade();
    void onCancelUpgrade();
    void onClearLog();
    void onAbout();

    void onFirmwarePathChanged(const QString &path);
    void onDeviceIndexChanged(int index);

    void onProgressUpdated(int percent, const QString &status);
    void onLogMessage(const QString &message);
    void onUpgradeFinished(bool success, const QString &message);

    void onAutoRefreshTimeout();

    /* 语言菜单 */
    void onLanguageActionTriggered(QAction *action);
    void onLanguageChanged();
    void onThemeActionTriggered(QAction *action);
    void onThemeChanged();

private:
    void setupUi();
    void createMenus();
    void createLanguageMenu();
    void retranslateUi();
    void loadSettings();
    void saveSettings();

    void refreshDeviceList();
    void updateDeviceStatusText();
    void updateFirmwareInfo();
    void updateProgressText();
    void setBusy(bool busy);
    void appendLog(const QString &message, bool isError = false);

    /* 日志按条目保存，切换深浅色时整体重绘，颜色始终跟随当前主题 */
    struct LogEntry
    {
        QString time;
        QString text;
        bool isError;
    };
    void appendLogLine(const LogEntry &entry);
    void renderLog();
    QString logTextColor() const;
    QString logErrorColor() const;
    QString statusColor(int kind) const;   /* 0=已连接 1=IAP 模式 2=未发现 */

    quint16 iapVid() const;
    quint16 iapPid() const;
    quint32 binBaseAddress() const;
    void updateBaseAddressHint();
    void updateV2Lock();

    bool ensureNotBusy();

private:
    /* 设备区 */
    QComboBox *deviceCombo_;
    QPushButton *refreshButton_;
    QLabel *deviceStatusLabel_;
    QLabel *deviceVersionLabel_;
    QTimer *autoRefreshTimer_;

    /* 固件区 */
    QLineEdit *fileEdit_;
    QPushButton *browseButton_;
    QLabel *firmwareInfoLabel_;
    QLineEdit *baseAddressEdit_;
    QLabel *baseAddressHintLabel_;    /* BIN 基地址后面的十六进制说明 */
    bool binBaseAddressLocked_;       /* V2 设备固定 0x08006000，禁止修改 */

    /* 选项区 */
    QLineEdit *iapVidEdit_;
    QLineEdit *iapPidEdit_;

    /* 进度与日志 */
    QProgressBar *progressBar_;
    QLabel *progressLabel_;
    QTextEdit *logView_;
    QLabel *logTitleLabel_;

    /* 按钮 */
    QPushButton *startButton_;
    QPushButton *cancelButton_;
    QPushButton *exitButton_;

    /* 菜单 */
    QMenu *fileMenu_;
    QMenu *toolMenu_;
    QMenu *viewMenu_;
    QMenu *langMenu_;
    QMenu *helpMenu_;
    QAction *openAction_;
    QAction *exitAction_;
    QAction *refreshAction_;
    QAction *clearLogAction_;
    QAction *aboutAction_;
    QActionGroup *langActionGroup_;
    QList<QAction *> langActions_;

    /* 主题菜单（跟随系统 / 浅色 / 深色） */
    QActionGroup *themeActionGroup_;
    QList<QAction *> themeActions_;

    /* 分组框与行标题（语言切换时需要重新翻译） */
    QGroupBox *deviceGroup_;
    QGroupBox *fwGroup_;
    QGroupBox *optGroup_;
    QLabel *deviceListLabel_;
    QLabel *deviceStatusTitleLabel_;
    QLabel *deviceVersionTitleLabel_;
    QLabel *filePathLabel_;
    QLabel *firmwareInfoTitleLabel_;
    QLabel *baseAddressLabel_;
    QLabel *iapVidLabel_;
    QLabel *iapPidLabel_;
    QLabel *iapHintLabel_;

    /* 升级线程 */
    IapWorker *worker_;
    QThread *workerThread_;
    bool upgrading_;

    /* 状态 */
    QList<Ch375DeviceInfo> devices_;
    int appDeviceIndex_;
    DeviceMode deviceMode_;
    int versionQueriedIndex_;   /* 已查询过版本的设备索引，避免重复下发命令 */

    /* 重新翻译时用于重建动态文本的原始状态 */
    QString deviceDetectError_;
    bool versionValid_;
    quint8 swVersion_;
    quint8 hwVersion_;

    enum class ProgressState { Idle, Running, Succeeded, Failed };
    ProgressState progressState_;

    /* 日志条目（用于主题切换后按新配色重绘） */
    QList<LogEntry> logEntries_;
};

#endif /* MAINWINDOW_H */
