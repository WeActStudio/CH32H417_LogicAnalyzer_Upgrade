/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * 主题管理（浅色 / 深色，跟随系统）
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "thememanager.h"

#include <QApplication>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QStyle>
#include <QStyleHints>
#include <QSettings>

namespace {

const char *kSettingsOrg = "WeActStudio";
const char *kSettingsApp = "CH32H417 Logic Analyzer Upgrade";
const char *kSettingsKey = "theme";

/* 深色配色（Fusion 风格） */
QPalette darkPalette()
{
    QPalette p;

    const QColor window       (0x2b, 0x2b, 0x2b);
    const QColor windowText   (0xe6, 0xe6, 0xe6);
    const QColor base         (0x1e, 0x1e, 0x1e);
    const QColor alternateBase(0x32, 0x32, 0x32);
    const QColor button       (0x3c, 0x3c, 0x3c);
    const QColor buttonText   (0xe6, 0xe6, 0xe6);
    const QColor text         (0xe6, 0xe6, 0xe6);
    const QColor disabledText (0x80, 0x80, 0x80);
    const QColor highlight    (0x2a, 0x82, 0xda);
    const QColor link         (0x6c, 0xb0, 0xff);

    p.setColor(QPalette::Window, window);
    p.setColor(QPalette::WindowText, windowText);
    p.setColor(QPalette::Base, base);
    p.setColor(QPalette::AlternateBase, alternateBase);
    p.setColor(QPalette::ToolTipBase, window);
    p.setColor(QPalette::ToolTipText, windowText);
    p.setColor(QPalette::Text, text);
    p.setColor(QPalette::Button, button);
    p.setColor(QPalette::ButtonText, buttonText);
    p.setColor(QPalette::BrightText, Qt::white);
    p.setColor(QPalette::Link, link);
    p.setColor(QPalette::Highlight, highlight);
    p.setColor(QPalette::HighlightedText, Qt::white);

    p.setColor(QPalette::Disabled, QPalette::WindowText, disabledText);
    p.setColor(QPalette::Disabled, QPalette::Text, disabledText);
    p.setColor(QPalette::Disabled, QPalette::ButtonText, disabledText);
    p.setColor(QPalette::Disabled, QPalette::Highlight, QColor(0x40, 0x40, 0x40));
    p.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledText);

    return p;
}

/*
 * 浅色配色（Fusion 风格）
 *
 * 注意：这里必须显式给出每一项的取值，不能直接用 QPalette() 的默认值 ——
 * QPalette 的默认构造函数取的是“当前应用调色板”，若之前已经应用过深色板，
 * 直接 setPalette(QPalette()) 会把深色板原样再设回去，导致从深色切回浅色无效。
 */
QPalette lightPalette()
{
    QPalette p;

    const QColor window       (0xf0, 0xf0, 0xf0);
    const QColor windowText   (0x1e, 0x1e, 0x1e);
    const QColor base         (0xff, 0xff, 0xff);
    const QColor alternateBase(0xf7, 0xf7, 0xf7);
    const QColor button       (0xe1, 0xe1, 0xe1);
    const QColor buttonText   (0x1e, 0x1e, 0x1e);
    const QColor text         (0x1e, 0x1e, 0x1e);
    const QColor disabledText (0x80, 0x80, 0x80);
    const QColor highlight    (0x2a, 0x82, 0xda);
    const QColor link         (0x00, 0x51, 0xa8);

    p.setColor(QPalette::Window, window);
    p.setColor(QPalette::WindowText, windowText);
    p.setColor(QPalette::Base, base);
    p.setColor(QPalette::AlternateBase, alternateBase);
    p.setColor(QPalette::ToolTipBase, base);
    p.setColor(QPalette::ToolTipText, windowText);
    p.setColor(QPalette::Text, text);
    p.setColor(QPalette::Button, button);
    p.setColor(QPalette::ButtonText, buttonText);
    p.setColor(QPalette::BrightText, Qt::white);
    p.setColor(QPalette::Link, link);
    p.setColor(QPalette::Highlight, highlight);
    p.setColor(QPalette::HighlightedText, Qt::white);

    p.setColor(QPalette::Disabled, QPalette::WindowText, disabledText);
    p.setColor(QPalette::Disabled, QPalette::Text, disabledText);
    p.setColor(QPalette::Disabled, QPalette::ButtonText, disabledText);
    p.setColor(QPalette::Disabled, QPalette::Highlight, QColor(0xc0, 0xc0, 0xc0));
    p.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledText);

    return p;
}

} // namespace

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent)
    , mode_(Mode::Auto)
    , appliedDark_(false)
{
}

ThemeManager *ThemeManager::instance()
{
    static ThemeManager *self = nullptr;
    if (!self) {
        self = new ThemeManager(qApp);
        self->loadFromSettings();
    }
    return self;
}

bool ThemeManager::systemPrefersDark()
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    return QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
#else
    /* Qt 5 没有 colorScheme 接口：读取 Windows 个性化设置
     * HKCU\Software\Microsoft\Windows\CurrentVersion\Themes\Personalize\AppsUseLightTheme
     * 0 = 深色，1 = 浅色 */
    QSettings reg(
        QLatin1String("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize"),
        QSettings::NativeFormat);
    return reg.value(QLatin1String("AppsUseLightTheme"), 1).toInt() == 0;
#endif
}

bool ThemeManager::effectiveDark() const
{
    switch (mode_) {
    case Mode::Dark:
        return true;
    case Mode::Light:
        return false;
    case Mode::Auto:
    default:
        return systemPrefersDark();
    }
}

bool ThemeManager::isDark() const
{
    return effectiveDark();
}

QString ThemeManager::modeName(Mode mode)
{
    switch (mode) {
    case Mode::Auto:
        return QCoreApplication::translate("ThemeManager", "跟随系统(&S)");
    case Mode::Light:
        return QCoreApplication::translate("ThemeManager", "浅色(&L)");
    case Mode::Dark:
    default:
        return QCoreApplication::translate("ThemeManager", "深色(&D)");
    }
}

void ThemeManager::loadFromSettings()
{
    QSettings settings(kSettingsOrg, kSettingsApp);
    const QString saved = settings.value(kSettingsKey, QLatin1String("auto")).toString();

    if (saved.compare(QLatin1String("dark"), Qt::CaseInsensitive) == 0)
        mode_ = Mode::Dark;
    else if (saved.compare(QLatin1String("light"), Qt::CaseInsensitive) == 0)
        mode_ = Mode::Light;
    else
        mode_ = Mode::Auto;
}

void ThemeManager::saveToSettings()
{
    QSettings settings(kSettingsOrg, kSettingsApp);

    QString value;
    switch (mode_) {
    case Mode::Dark:
        value = QLatin1String("dark");
        break;
    case Mode::Light:
        value = QLatin1String("light");
        break;
    case Mode::Auto:
    default:
        value = QLatin1String("auto");
        break;
    }

    settings.setValue(kSettingsKey, value);
}

void ThemeManager::apply()
{
    const bool dark = effectiveDark();

    /* Fusion 风格保证自定义调色板在静态构建下也生效 */
    if (QApplication::style()->objectName().compare(QLatin1String("fusion"), Qt::CaseInsensitive) != 0)
        QApplication::setStyle(QLatin1String("Fusion"));

    QApplication::setPalette(dark ? darkPalette() : lightPalette());
    appliedDark_ = dark;

    Q_EMIT themeChanged();
}

void ThemeManager::setMode(Mode mode)
{
    if (mode_ == mode)
        return;

    mode_ = mode;
    saveToSettings();
    apply();
}
