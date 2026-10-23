/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * UI language management (English, Simplified Chinese, Russian, German,
 * Spanish, plus a follow-system option)
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

/* The translations are compiled into the executable, no external file needed */
const char *kQmPrefix = ":/i18n/";

QString qmFileName(LanguageManager::Language lang)
{
    switch (lang) {
    case LanguageManager::Language::ChineseSimplified:
        return QStringLiteral("app_zh_CN.qm");
    case LanguageManager::Language::Russian:
        return QStringLiteral("app_ru.qm");
    case LanguageManager::Language::German:
        return QStringLiteral("app_de.qm");
    case LanguageManager::Language::Spanish:
        return QStringLiteral("app_es.qm");
    case LanguageManager::Language::English:
    default:
        /* English is the source language, there is no app_en.qm */
        return QString();
    }
}

/** Map the system language onto a supported language; fall back to English */
LanguageManager::Language detectSystemLanguage()
{
    const QLocale locale = QLocale::system();

    switch (locale.language()) {
    case QLocale::Chinese:
        return LanguageManager::Language::ChineseSimplified;
    case QLocale::Russian:
        return LanguageManager::Language::Russian;
    case QLocale::German:
        return LanguageManager::Language::German;
    case QLocale::Spanish:
        return LanguageManager::Language::Spanish;
    case QLocale::English:
        return LanguageManager::Language::English;
    default:
        break;
    }

    /* Fall back to the territory, so that zh_TW is also treated as Chinese */
    const QString name = locale.name();      /* e.g. zh_CN / en_US */
    if (name.startsWith(QLatin1String("zh"), Qt::CaseInsensitive))
        return LanguageManager::Language::ChineseSimplified;

    /* Unsupported language: use English */
    return LanguageManager::Language::English;
}

/** Qt name of a language, as used in the .ts file name and in QSettings */
const char *languageCodeOf(LanguageManager::Language lang)
{
    switch (lang) {
    case LanguageManager::Language::ChineseSimplified:
        return "zh_CN";
    case LanguageManager::Language::Russian:
        return "ru";
    case LanguageManager::Language::German:
        return "de";
    case LanguageManager::Language::Spanish:
        return "es";
    case LanguageManager::Language::English:
    default:
        return "en";
    }
}

} // namespace

LanguageManager::LanguageManager(QObject *parent)
    : QObject(parent)
    , preference_(Preference::English)   /* English is the default UI language */
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
    /* Same order as the Preference enum */
    return QStringList()
           << QCoreApplication::translate("LanguageManager", "Follow System(&A)")
           << QCoreApplication::translate("LanguageManager", "English(&E)")
           << QCoreApplication::translate("LanguageManager", "Simplified Chinese(&C)")
           << QCoreApplication::translate("LanguageManager", "Russian(&R)")
           << QCoreApplication::translate("LanguageManager", "German(&G)")
           << QCoreApplication::translate("LanguageManager", "Spanish(&S)");
}

LanguageManager::Language LanguageManager::resolvedLanguage() const
{
    if (preference_ == Preference::Auto)
        return detectSystemLanguage();

    /* Every explicit choice maps 1:1 onto the Language enum (both start with
       English), only the Auto entry sits in front of it */
    return static_cast<Language>(static_cast<int>(preference_) - 1);
}

QString LanguageManager::languageCode() const
{
    return QString::fromLatin1(languageCodeOf(resolvedLanguage()));
}

QString LanguageManager::languageDisplayName() const
{
    switch (resolvedLanguage()) {
    case Language::ChineseSimplified:
        return QCoreApplication::translate("LanguageManager", "Simplified Chinese");
    case Language::Russian:
        return QCoreApplication::translate("LanguageManager", "Russian");
    case Language::German:
        return QCoreApplication::translate("LanguageManager", "German");
    case Language::Spanish:
        return QCoreApplication::translate("LanguageManager", "Spanish");
    case Language::English:
    default:
        return QCoreApplication::translate("LanguageManager", "English");
    }
}

void LanguageManager::loadFromSettings()
{
    QSettings settings(kSettingsOrg, kSettingsApp);
    const QString saved = settings.value(kSettingsKey, QStringLiteral("en")).toString();

    if (saved.compare(QLatin1String("zh_CN"), Qt::CaseInsensitive) == 0
        || saved.compare(QLatin1String("zh"), Qt::CaseInsensitive) == 0)
        preference_ = Preference::ChineseSimplified;
    else if (saved.compare(QLatin1String("ru"), Qt::CaseInsensitive) == 0)
        preference_ = Preference::Russian;
    else if (saved.compare(QLatin1String("de"), Qt::CaseInsensitive) == 0)
        preference_ = Preference::German;
    else if (saved.compare(QLatin1String("es"), Qt::CaseInsensitive) == 0)
        preference_ = Preference::Spanish;
    else if (saved.compare(QLatin1String("en"), Qt::CaseInsensitive) == 0
             || saved.compare(QLatin1String("en_US"), Qt::CaseInsensitive) == 0)
        preference_ = Preference::English;
    else
        preference_ = Preference::Auto;
}

void LanguageManager::saveToSettings()
{
    QSettings settings(kSettingsOrg, kSettingsApp);

    const QString value = (preference_ == Preference::Auto)
                              ? QStringLiteral("auto")
                              : QString::fromLatin1(
                                    languageCodeOf(resolvedLanguage()));

    settings.setValue(kSettingsKey, value);
}

void LanguageManager::uninstallTranslator()
{
    if (translator_) {
        qApp->removeTranslator(translator_);
        delete translator_;
        translator_ = nullptr;
    }
}

bool LanguageManager::loadLanguage(Language lang)
{
    /* English is the source language of every UI string: nothing to load,
       just drop the translator of the previous language if one is installed. */
    if (lang == Language::English) {
        uninstallTranslator();
        current_ = Language::English;
        return true;
    }

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

    /* Tell every window that its texts must be retranslated */
    QWidgetList widgets = QApplication::topLevelWidgets();
    for (QWidget *widget : widgets)
        QApplication::postEvent(widget, new QEvent(QEvent::LanguageChange));

    /* Non top level widgets (embedded dialogs and the like) too */
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
