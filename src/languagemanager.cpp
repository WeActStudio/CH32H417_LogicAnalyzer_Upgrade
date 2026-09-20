/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * 语言管理（中文 / 英文切换、跟随系统语言）
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "languagemanager.h"

#include <QApplication>
#include <QCoreApplication>
#include <QTranslator>
#include <QLocale>
#include <QSettings>
#include <QWidget>
#include <QEvent>
#include <QDebug>

namespace {

const char *kSettingsOrg = "WeActStudio";
const char *kSettingsApp = "CH32H417 Logic Analyzer Upgrade";
const char *kSettingsKey = "language";

/* 翻译文件编译进 exe 资源，路径固定，不依赖外部文件 */
const char *kQmPrefix = ":/i18n/";

QString qmFileName(LanguageManager::Language lang)
{
    switch (lang) {
    case LanguageManager::Language::ChineseSimplified:
        return QStringLiteral("app_zh_CN.qm");
    case LanguageManager::Language::English:
    default:
        return QStringLiteral("app_en.qm");
    }
}

/** 系统语言 -> 支持的语言；不支持时回退英文 */
LanguageManager::Language detectSystemLanguage()
{
    const QLocale locale = QLocale::system();

    switch (locale.language()) {
    case QLocale::Chinese:
        return LanguageManager::Language::ChineseSimplified;
    case QLocale::English:
        return LanguageManager::Language::English;
    default:
        break;
    }

    /* 进一步按国家/地区判断（例如 zh_TW 也归到中文） */
    const QString name = locale.name();      /* 形如 zh_CN / en_US */
    if (name.startsWith(QLatin1String("zh"), Qt::CaseInsensitive))
        return LanguageManager::Language::ChineseSimplified;

    /* 不支持的语言：显示英文 */
    return LanguageManager::Language::English;
}

} // namespace

LanguageManager::LanguageManager(QObject *parent)
    : QObject(parent)
    , preference_(Preference::Auto)
    , translator_(nullptr)
    , current_(Language::English)
{
}

LanguageManager::~LanguageManager()
{
    delete translator_;
}

LanguageManager *LanguageManager::instance()
{
    static LanguageManager *self = nullptr;
    if (!self) {
        self = new LanguageManager(qApp);
        self->loadFromSettings();
    }
    return self;
}

QStringList LanguageManager::preferenceNames()
{
    /* 与 Preference 枚举顺序一致：Auto / English / ChineseSimplified */
    return QStringList()
           << QCoreApplication::translate("LanguageManager", "跟随系统(&A)")
           << QCoreApplication::translate("LanguageManager", "English(&E)")
           << QCoreApplication::translate("LanguageManager", "简体中文(&C)");
}

LanguageManager::Language LanguageManager::resolvedLanguage() const
{
    if (preference_ == Preference::Auto)
        return detectSystemLanguage();

    return preference_ == Preference::ChineseSimplified
               ? Language::ChineseSimplified
               : Language::English;
}

QString LanguageManager::languageCode() const
{
    switch (resolvedLanguage()) {
    case Language::ChineseSimplified:
        return QStringLiteral("zh_CN");
    case Language::English:
    default:
        return QStringLiteral("en");
    }
}

QString LanguageManager::languageDisplayName() const
{
    switch (resolvedLanguage()) {
    case Language::ChineseSimplified:
        return QCoreApplication::translate("LanguageManager", "简体中文");
    case Language::English:
    default:
        return QCoreApplication::translate("LanguageManager", "English");
    }
}

void LanguageManager::loadFromSettings()
{
    QSettings settings(kSettingsOrg, kSettingsApp);
    const QString saved = settings.value(kSettingsKey, QStringLiteral("auto")).toString();

    if (saved.compare(QLatin1String("zh_CN"), Qt::CaseInsensitive) == 0
        || saved.compare(QLatin1String("zh"), Qt::CaseInsensitive) == 0)
        preference_ = Preference::ChineseSimplified;
    else if (saved.compare(QLatin1String("en"), Qt::CaseInsensitive) == 0
             || saved.compare(QLatin1String("en_US"), Qt::CaseInsensitive) == 0)
        preference_ = Preference::English;
    else
        preference_ = Preference::Auto;
}

void LanguageManager::saveToSettings()
{
    QSettings settings(kSettingsOrg, kSettingsApp);

    QString value;
    switch (preference_) {
    case Preference::ChineseSimplified:
        value = QStringLiteral("zh_CN");
        break;
    case Preference::English:
        value = QStringLiteral("en");
        break;
    case Preference::Auto:
    default:
        value = QStringLiteral("auto");
        break;
    }

    settings.setValue(kSettingsKey, value);
}

bool LanguageManager::loadLanguage(Language lang)
{
    QTranslator *translator = new QTranslator(qApp);
    const QString path = QString::fromLatin1(kQmPrefix) + qmFileName(lang);

    if (!translator->load(path)) {
        qWarning() << "Failed to load translation:" << path;
        delete translator;
        return false;
    }

    if (translator_)
        qApp->removeTranslator(translator_);

    qApp->installTranslator(translator);

    delete translator_;
    translator_ = translator;
    current_ = lang;

    return true;
}

void LanguageManager::apply()
{
    const Language target = resolvedLanguage();

    if (current_ != target || !translator_)
        loadLanguage(target);

    Q_EMIT languageChanged(current_);

    /* 通知所有窗口：界面文字需要重新翻译 */
    QWidgetList widgets = QApplication::topLevelWidgets();
    for (QWidget *widget : widgets)
        QApplication::postEvent(widget, new QEvent(QEvent::LanguageChange));

    /* 非顶层窗口（如内嵌对话框）也一并刷新 */
    for (QWidget *widget : widgets) {
        QList<QWidget *> children = widget->findChildren<QWidget *>();
        for (QWidget *child : children)
            QApplication::postEvent(child, new QEvent(QEvent::LanguageChange));
    }
}

void LanguageManager::setPreference(Preference pref)
{
    if (preference_ == pref)
        return;

    preference_ = pref;
    saveToSettings();
    apply();
}
