/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * 语言管理（中文 / 英文切换、跟随系统语言）
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>

class QTranslator;

/**
 * 界面语言管理
 *
 * - 支持 简体中文 / English 两种界面语言
 * - 支持 "跟随系统"：识别系统语言，无法识别（非中文）时回退到英文
 * - 选择结果写入 QSettings，下次启动自动沿用
 * - 切换语言后向所有顶层窗口投递 LanguageChange 事件，界面即时刷新
 *   （无需重启程序）
 */
class LanguageManager : public QObject
{
    Q_OBJECT

public:
    /** 语言选择项（用户的设置项） */
    enum class Preference {
        Auto,               /**< 跟随系统语言 */
        English,            /**< 英文 */
        ChineseSimplified   /**< 简体中文 */
    };

    /** 实际生效的语言代码 */
    enum class Language {
        English,            /**< en */
        ChineseSimplified   /**< zh_CN */
    };

    static LanguageManager *instance();

    /** 当前用户设置（可能是 Auto） */
    Preference preference() const { return preference_; }

    /** 当前生效的语言（Auto 已解析为具体语言） */
    Language resolvedLanguage() const;

    /** 生效语言的 Qt 名称（en / zh_CN） */
    QString languageCode() const;

    /** 生效语言的本地化名称（English / 简体中文），用于菜单显示 */
    QString languageDisplayName() const;

    /** 可选的设置项（顺序与 Preference 枚举一致） */
    static QStringList preferenceNames();

    /** 设置并应用语言 */
    void setPreference(Preference pref);

    /** 根据当前设置重新装载翻译，并通知界面刷新 */
    void apply();

    /** 载入指定翻译文件；失败返回 false */
    bool loadLanguage(Language lang);

Q_SIGNALS:
    /** 语言已切换（界面刷新前发出） */
    void languageChanged(Language language);

private:
    explicit LanguageManager(QObject *parent = nullptr);
    ~LanguageManager();

    void loadFromSettings();
    void saveToSettings();

    Preference preference_;
    QTranslator *translator_;      /**< 应用自身翻译 */
    Language current_;
};

#endif /* LANGUAGEMANAGER_H */
