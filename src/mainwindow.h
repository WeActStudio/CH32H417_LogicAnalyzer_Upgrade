/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * Main window
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
 * Main window of the upgrade tool.
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
    /* Internal CH375 DLL log (may come from a worker thread, posted to the UI
       through the event queue) */
    void appendCh375Log(int level, const QString &message);

    /* Open the About dialog; public so that the "--about" command line helper
       can show it for screenshots */
    void showAbout();

private Q_SLOTS:
    void onRefreshDevices();
    void onIapButtonClicked();
    void updateIapButton();
    void onRebootDevice();
    void onSlotActionTriggered();
    void onBrowseFirmware();
    void onStartUpgrade();
    void onClearLog();

    void onFirmwarePathChanged(const QString &path);
    void onDeviceIndexChanged(int index);

    void onProgressUpdated(int percent, const QString &status);
    void onLogMessage(const QString &message);
    void onUpgradeFinished(bool success, const QString &message);

    void onAutoRefreshTimeout();

    void onThemeActionTriggered(QAction *action);
    void onThemeChanged();

    /* Language menu */
    void onLanguageActionTriggered(QAction *action);
    void onLanguageChanged();

private:
    void setupUi();
    void createMenus();
    void retranslateUi();
    void loadSettings();
    void saveSettings();

    void refreshDeviceList();
    void updateDeviceStatusText();
    void updateFirmwareInfo();
    void updateProgressText();
    void setBusy(bool busy);
    void appendLog(const QString &message, bool isError = false);

    /* Log entries are kept so that the whole log can be repainted when the
       light/dark theme changes; the colours always follow the current theme */
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
    QString statusColor(int kind) const;   /* 0=connected 1=IAP mode 2=not found */

    quint16 iapVid() const;
    quint16 iapPid() const;
    quint32 binBaseAddress() const;
    void updateBinBaseAddressFromUi();
    void updateBaseAddressHint();
    void updateV2Lock();

    bool ensureNotBusy();

private:
    /* Device section */
    QComboBox *deviceCombo_;
    QPushButton *refreshButton_;
    QLabel *deviceStatusLabel_;
    QLabel *deviceVersionLabel_;
    QTimer *autoRefreshTimer_;

    /* Bootloader commands (reboot / slot switch) */
    bool bootloaderControlAvailable() const;
    void updateBootloaderActions();
    void reportBootloaderUnavailable();
    void runSlotSwitch(int slot);

    /* Upgrade worker plumbing, shared by the full upgrade and the
       "reboot into IAP" button */
    IapWorker::Config buildIapWorkerConfig() const;
    void startIapWorker(const IapWorker::Config &config, bool iapOnly);
    bool iapOnlyRun_;           /* The running worker only switches to IAP */

    /* Firmware section */
    QLineEdit *fileEdit_;
    QPushButton *browseButton_;
    QLabel *firmwareInfoLabel_;
    QComboBox *baseAddressCombo_;     /* BIN base address: free hex input, V2 gets slot presets */
    QLabel *baseAddressHintLabel_;    /* Hexadecimal note behind the BIN base address */
    bool binBaseAddressLocked_;       /* V2 boards: IAP VID/PID fixed, base picks a slot */
    /*
     * The current BIN base address, kept aside from the combo box: the slot
     * list is rebuilt (and briefly emptied) on every device refresh, so the
     * value must not be read back from the widget - a lost value would reset
     * the slot selection to the first entry after an upgrade.
     */
    quint32 binBaseAddressValue_;
    void updateBaseAddressSlots(bool v2);

    /* Options section */
    QLineEdit *iapVidEdit_;
    QLineEdit *iapPidEdit_;

    /* Progress and log */
    QProgressBar *progressBar_;
    QLabel *progressLabel_;
    QTextEdit *logView_;
    QLabel *logTitleLabel_;

    /* Buttons */
    QLabel *iapSlotLabel_;          /* "Reboot into:", only shown in IAP mode */
    QList<QPushButton *> iapSlotButtons_;
    QPushButton *iapButton_;           /* Reboot into IAP / leave IAP, depends on the mode */
    QPushButton *startButton_;
    QPushButton *exitButton_;

    /* Menus */
    QMenu *fileMenu_;
    QMenu *toolMenu_;
    QMenu *viewMenu_;
    QMenu *langMenu_;
    QMenu *helpMenu_;
    QAction *openAction_;
    QAction *exitAction_;
    QAction *refreshAction_;
    QAction *clearLogAction_;
    /* Bootloader control (only available while a board sits in IAP mode) */
    QAction *rebootAction_;
    QMenu *slotMenu_;
    QList<QAction *> slotActions_;
    QAction *aboutAction_;
    QActionGroup *langActionGroup_;
    QList<QAction *> langActions_;

    /* Theme menu (follow system / light / dark) */
    QActionGroup *themeActionGroup_;
    QList<QAction *> themeActions_;

    /* Group boxes and row captions */
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

    /* Upgrade thread */
    IapWorker *worker_;
    QThread *workerThread_;
    bool upgrading_;

    /* State */
    QList<Ch375DeviceInfo> devices_;
    int appDeviceIndex_;                /* CH375 index, -1 when the board was found on another channel */
    Ch375DeviceInfo appDevice_;         /* The application mode device, on whichever channel */
    DeviceMode deviceMode_;
    QString versionQueriedKey_;         /* Channel + index whose version was already queried */

    /* Raw state kept so dynamic texts can be rebuilt */
    QString deviceDetectError_;
    bool versionValid_;
    quint8 swVersion_;
    quint8 hwVersion_;

    enum class ProgressState { Idle, Running, Succeeded, Failed };
    ProgressState progressState_;

    /* Log entries (used to repaint with new colours after a theme change) */
    QList<LogEntry> logEntries_;
};

#endif /* MAINWINDOW_H */
