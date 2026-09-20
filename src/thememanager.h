/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * 主题管理（浅色 / 深色，跟随系统）
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QPalette>

/**
 * 界面主题管理。
 *
 * - Qt 6.5 及以上：通过 QStyleHints::colorSchemeChanged 实时跟随系统深浅色切换；
 * - Qt 5（回退）：启动时读取 Windows 注册表 AppsUseLightTheme 判断。
 *
 * 深色模式采用 Fusion 风格 + 自定义深色 QPalette，保证静态编译下也能正确显示
 * （静态构建通常只带 windowsvista 风格插件，原生风格不一定跟随系统深色设置）。
 */
class ThemeManager : public QObject
{
    Q_OBJECT

public:
    enum class Mode {
        Auto,   /* 跟随系统 */
        Light,  /* 强制浅色 */
        Dark    /* 强制深色 */
    };

    static ThemeManager *instance();

    Mode mode() const { return mode_; }

    /** 当前实际生效的是否为深色 */
    bool isDark() const;

    /** 系统是否处于深色模式（与用户设置无关） */
    static bool systemPrefersDark();

    /** 菜单显示名（随界面语言变化） */
    static QString modeName(Mode mode);

    /** 应用当前主题（切换语言 / 系统主题变化后也会调用） */
    void apply();

public Q_SLOTS:
    void setMode(Mode mode);

Q_SIGNALS:
    void themeChanged();

private:
    explicit ThemeManager(QObject *parent = nullptr);

    bool effectiveDark() const;
    void loadFromSettings();
    void saveToSettings();

    Mode mode_;
    bool appliedDark_;
};

#endif // THEMEMANAGER_H
