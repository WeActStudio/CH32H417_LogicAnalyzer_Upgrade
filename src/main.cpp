/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * Program entry point
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <QApplication>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QIcon>
#include <QLocale>
#include <QStyleHints>
#include <QTimer>
#include <QWidget>
#include <QDebug>

#include "mainwindow.h"
#include "cli.h"
#include "libusbdev.h"
#include "languagemanager.h"
#include "thememanager.h"

namespace {

/** Map a --lang / --autoswitch value onto a preference; Auto on anything else */
LanguageManager::Preference preferenceFromCode(const QString &code)
{
    const QString value = code.toLower();

    if (value == QLatin1String("en"))
        return LanguageManager::Preference::English;
    if (value == QLatin1String("zh_cn") || value == QLatin1String("zh"))
        return LanguageManager::Preference::ChineseSimplified;
    if (value == QLatin1String("ru"))
        return LanguageManager::Preference::Russian;
    if (value == QLatin1String("de"))
        return LanguageManager::Preference::German;
    if (value == QLatin1String("es"))
        return LanguageManager::Preference::Spanish;

    return LanguageManager::Preference::Auto;
}

} // namespace

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setApplicationName("CH32H417 Logic Analyzer Upgrade");
    QApplication::setApplicationVersion("1.0.0");
    /* Company behind the settings path and the About dialog */
    QApplication::setOrganizationName("WeActStudio");

    /*
     * Headless mode: any argument on the command line runs the upgrade without
     * a window and returns a process exit code; without arguments the graphical
     * interface starts. The switches of the graphical interface itself
     * (--lang / --theme / --screenshot / --autoswitch / --about) always keep it.
     * No translator is installed on the command line path.
     */
    QStringList args;
    for (int i = 1; i < argc; ++i)
        args << QString::fromLocal8Bit(argv[i]);

    /*
     * Headless mode: any argument on the command line runs the upgrade without
     * a window and returns a process exit code; without arguments the graphical
     * interface starts. The switches of the graphical interface itself
     * (--lang / --theme / --screenshot / --autoswitch / --about) always keep it.
     * No translator is installed on the command line path.
     *
     * The work is handed over to the console companion as soon as it is
     * installed next to this program: PowerShell does not wait for a Windows
     * GUI application, but it does wait for that one, and only it can be
     * redirected by another program without any console trickery.
     */
    if (cliRequested(args)) {
        const int forwarded = cliForwardToConsoleApp(args);
        if (forwarded >= 0)
            return forwarded;

        return cliRun(args);
    }

    /* Application icon: logo.ico is embedded in the executable, setting it here
     * as well makes sure the title bar, the task bar and the About dialog all
     * use the same logo. */
    QApplication::setWindowIcon(QIcon(QStringLiteral(":/icons/logo")));

    /*
     * UI language: English is the source language of every string, the other
     * languages come from the compiled app_<lang>.qm. The UI follows the system
     * language by default and falls back to English for anything else.
     * The user can switch languages in the "Language" menu; the choice is
     * remembered and takes effect immediately.
     * The translation must be installed before any window is created.
     */
    LanguageManager *langMgr = LanguageManager::instance();

    /* Command line override: --lang=en | zh_CN | ru | de | es | auto */
    for (int i = 1; i < argc; ++i) {
        const QString arg = QString::fromLocal8Bit(argv[i]);
        if (!arg.startsWith(QLatin1String("--lang")))
            continue;

        const QString value = arg.contains(QLatin1Char('='))
                                  ? arg.section(QLatin1Char('='), 1)
                                  : (i + 1 < argc ? QString::fromLocal8Bit(argv[++i]) : QString());

        langMgr->setPreference(preferenceFromCode(value));
        break;
    }
    langMgr->apply();
    qDebug() << "UI language:" << langMgr->languageCode()
             << "| system:" << QLocale::system().name();

    /* Do NOT call QApplication::setApplicationDisplayName: on Windows the title
     * bar would show "window title - application display name" and the display
     * name is not updated when the language changes, which would leave Chinese
     * text behind in English mode. The window title is owned entirely by
     * MainWindow::retranslateUi(). */
    /*
     * UI theme: follows the system light/dark setting by default; with Qt 6.5+
     * the theme switches live when the system theme changes, no restart needed.
     */
    ThemeManager *themeMgr = ThemeManager::instance();

    /* Command line override: --theme=light | --theme=dark | --theme=auto
     * (handy for verification runs and screenshots) */
    for (int i = 1; i < argc; ++i) {
        const QString arg = QString::fromLocal8Bit(argv[i]);
        if (!arg.startsWith(QLatin1String("--theme")))
            continue;

        const QString value = arg.contains(QLatin1Char('='))
                                  ? arg.section(QLatin1Char('='), 1).toLower()
                                  : QString();

        if (value == QLatin1String("light"))
            themeMgr->setMode(ThemeManager::Mode::Light);
        else if (value == QLatin1String("dark"))
            themeMgr->setMode(ThemeManager::Mode::Dark);
        else
            themeMgr->setMode(ThemeManager::Mode::Auto);
        break;
    }

    themeMgr->apply();
    qDebug() << "dark mode:" << themeMgr->isDark();

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    /* Follow the system light/dark switch live */
    QObject::connect(QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged,
                     themeMgr, [themeMgr](Qt::ColorScheme) {
                         themeMgr->apply();
                         qDebug() << "system color scheme changed, dark:" << themeMgr->isDark();
                     });
#endif

    MainWindow window;
    window.show();

    /* Automation helper: --screenshot=<file> grabs the window once it is shown.
     * The active window is used, so dialogs opened by --about are captured too. */
    for (int i = 1; i < argc; ++i) {
        const QString arg = QString::fromLocal8Bit(argv[i]);
        if (!arg.startsWith(QLatin1String("--screenshot=")))
            continue;
        const QString path = arg.section(QLatin1Char('='), 1);
        QTimer::singleShot(1500, &window, [&window, path]() {
            QWidget *target = QApplication::activeWindow();
            if (!target)
                target = &window;
            target->grab().save(path);
            qDebug() << "screenshot saved:" << path;
        });
        break;
    }

    /* Automation helper: --about opens the About dialog (with --screenshot it
     * produces a picture of the About dialog) */
    for (int i = 1; i < argc; ++i) {
        if (QString::fromLocal8Bit(argv[i]) != QLatin1String("--about"))
            continue;
        QTimer::singleShot(800, &window, [&window]() { window.showAbout(); });
        break;
    }

    /* Automation helper: --autoswitch=en|zh_CN|ru|de|es switches the language
     * after the window is shown (simulates the menu action) */
    for (int i = 1; i < argc; ++i) {
        const QString arg = QString::fromLocal8Bit(argv[i]);
        if (!arg.startsWith(QLatin1String("--autoswitch=")))
            continue;
        const QString value = arg.section(QLatin1Char('='), 1);
        QTimer::singleShot(1200, &window, [value]() {
            LanguageManager::instance()->setPreference(preferenceFromCode(value));
        });
        break;
    }

    const int code = app.exec();

    /* Close the libusb session before the process ends */
    libusbdev_cleanup();

    return code;
}
