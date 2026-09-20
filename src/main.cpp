/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * 程序入口
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
#include <QDebug>

#include "mainwindow.h"
#include "languagemanager.h"
#include "thememanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setApplicationName("CH32H417 Logic Analyzer Upgrade");
    QApplication::setApplicationVersion("1.0.0");
    /* 与 languagemanager / thememanager / mainwindow 里的 kSettingsOrg 保持一致，
     * 注册表路径统一为 WeActStudio\CH32H417 Logic Analyzer Upgrade */
    QApplication::setOrganizationName("WeActStudio");

    /* 应用程序图标：logo.ico 已嵌入 exe 资源，这里再显式设置，
     * 保证标题栏 / 任务栏 / 关于对话框都使用同一 logo。 */
    QApplication::setWindowIcon(QIcon(QStringLiteral(":/icons/logo")));

    /*
     * 界面语言：默认跟随系统，系统语言不支持时回退英文。
     * 用户可在菜单 "语言" 中切换，选择会被记住，切换后立即生效。
     * 必须在创建窗口之前装载翻译。
     */
    LanguageManager *langMgr = LanguageManager::instance();

    /* 命令行可覆盖：--lang=en | --lang=zh_CN | --lang=auto */
    for (int i = 1; i < argc; ++i) {
        const QString arg = QString::fromLocal8Bit(argv[i]);
        if (!arg.startsWith(QLatin1String("--lang")))
            continue;

        const QString value = arg.contains(QLatin1Char('='))
                                  ? arg.section(QLatin1Char('='), 1)
                                  : (i + 1 < argc ? QString::fromLocal8Bit(argv[++i]) : QString());

        if (value.compare(QLatin1String("en"), Qt::CaseInsensitive) == 0)
            langMgr->setPreference(LanguageManager::Preference::English);
        else if (value.compare(QLatin1String("zh_CN"), Qt::CaseInsensitive) == 0
                 || value.compare(QLatin1String("zh"), Qt::CaseInsensitive) == 0)
            langMgr->setPreference(LanguageManager::Preference::ChineseSimplified);
        else
            langMgr->setPreference(LanguageManager::Preference::Auto);
        break;
    }
    langMgr->apply();
    qDebug() << "UI language:" << langMgr->languageCode()
             << "| system:" << QLocale::system().name();

    /* 注意：不要设置 QApplication::setApplicationDisplayName ——
     * Windows 上标题栏会显示 "窗口标题 - 应用显示名" 的拼接，
     * 且显示名不随语言切换更新，导致英文模式下残留中文。
     * 窗口标题由 MainWindow::retranslateUi() 全权控制。 */
    /*
     * 界面主题：默认跟随系统（浅色 / 深色），
     * Qt 6.5+ 在系统主题变化时会自动切换，无需重启。
     */
    ThemeManager *themeMgr = ThemeManager::instance();

    /* 命令行可覆盖：--theme=light | --theme=dark | --theme=auto（便于验证与截图） */
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
    /* 系统深浅色切换时实时跟随 */
    QObject::connect(QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged,
                     themeMgr, [themeMgr](Qt::ColorScheme) {
                         themeMgr->apply();
                         qDebug() << "system color scheme changed, dark:" << themeMgr->isDark();
                     });
#endif

    MainWindow window;
    window.show();

    /* 自动化验证用：--screenshot=<文件> 在窗口显示后抓取界面并存盘 */
    for (int i = 1; i < argc; ++i) {
        const QString arg = QString::fromLocal8Bit(argv[i]);
        if (!arg.startsWith(QLatin1String("--screenshot=")))
            continue;
        const QString path = arg.section(QLatin1Char('='), 1);
        QTimer::singleShot(1500, &window, [&window, path]() {
            window.grab().save(path);
            qDebug() << "screenshot saved:" << path;
        });
        break;
    }

    /* 自动化验证用：--autoswitch=en|zh_CN 窗口显示后自动切换语言（模拟菜单切换） */
    for (int i = 1; i < argc; ++i) {
        const QString arg = QString::fromLocal8Bit(argv[i]);
        if (!arg.startsWith(QLatin1String("--autoswitch=")))
            continue;
        const QString value = arg.section(QLatin1Char('='), 1).toLower();
        QTimer::singleShot(1200, &window, [value]() {
            LanguageManager *mgr = LanguageManager::instance();
            if (value == QLatin1String("en"))
                mgr->setPreference(LanguageManager::Preference::English);
            else if (value == QLatin1String("zh_cn") || value == QLatin1String("zh"))
                mgr->setPreference(LanguageManager::Preference::ChineseSimplified);
            else
                mgr->setPreference(LanguageManager::Preference::Auto);
        });
        break;
    }

    return app.exec();
}
