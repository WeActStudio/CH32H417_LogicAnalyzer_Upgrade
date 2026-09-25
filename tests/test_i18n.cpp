/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * Unit test for the UI language: verifies the compiled translation and the
 * language selection logic.
 *
 * English is the source language of every UI string, so in English mode the
 * translated text must be identical to the source text, and in Chinese mode it
 * must come from translations/app_zh_CN.ts.
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <QApplication>
#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <cstdio>

#include "languagemanager.h"

static int g_failed = 0;
static int g_passed = 0;

#define CHECK(cond, msg)                                              \
    do {                                                              \
        if (cond) {                                                  \
            ++g_passed;                                              \
            std::printf("  [OK]   %s\n", msg);                              \
        } else {                                                     \
            ++g_failed;                                              \
            std::printf("  [FAIL] %s\n", msg);                              \
        }                                                            \
    } while (0)

#define T(ctx, src) QCoreApplication::translate(ctx, src)

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("WeAct");
    QCoreApplication::setApplicationName("CH32H417_LogicAnalyzer_Upgrade");

    std::printf("system locale: %s\n", qPrintable(QLocale::system().name()));

    /* ---------- 1. English (the source language) ---------- */
    std::printf("== English ==\n");
    LanguageManager::instance()->setPreference(LanguageManager::Preference::English);
    CHECK(LanguageManager::instance()->languageCode() == "en", "languageCode() == en");
    CHECK(T("MainWindow", "Device") == "Device", "Device stays English");
    CHECK(T("MainWindow", "Firmware File") == "Firmware File", "Firmware File stays English");
    CHECK(T("MainWindow", "IAP Parameters") == "IAP Parameters", "IAP Parameters stays English");
    CHECK(T("MainWindow", "Ready") == "Ready", "Ready stays English");
    CHECK(T("MainWindow", "Start Upgrade(&S)") == "Start Upgrade(&S)", "Start Upgrade stays English");
    CHECK(T("IapWorker", "Programming FLASH ... %1%").arg(50) == "Programming FLASH ... 50%",
          "IAP progress text stays English");
    CHECK(T("LanguageManager", "Simplified Chinese") == "Simplified Chinese",
          "language name stays English");

    /* ---------- 2. Simplified Chinese ---------- */
    std::printf("== Chinese ==\n");
    LanguageManager::instance()->setPreference(
        LanguageManager::Preference::ChineseSimplified);
    CHECK(LanguageManager::instance()->languageCode() == "zh_CN", "languageCode() == zh_CN");
    CHECK(T("MainWindow", "Device") == QString::fromUtf8("设备"), "Device -> 设备");
    CHECK(T("MainWindow", "Firmware File") == QString::fromUtf8("固件文件"), "Firmware File -> 固件文件");
    CHECK(T("MainWindow", "Ready") == QString::fromUtf8("就绪"), "Ready -> 就绪");
    CHECK(T("IapWorker", "Programming FLASH ... %1%").arg(50)
              == QString::fromUtf8("编程 FLASH ... 50%"),
          "Programming FLASH ... %1% -> 编程 FLASH ... 50%");

    /* ---------- 3. Follow the system ---------- */
    std::printf("== Auto ==\n");
    LanguageManager::instance()->setPreference(LanguageManager::Preference::Auto);
    const LanguageManager::Language autoLang =
        LanguageManager::instance()->resolvedLanguage();
    const bool systemIsChinese = QLocale::system().language() == QLocale::Chinese
                                 || QLocale::system().name().startsWith("zh", Qt::CaseInsensitive);
    const LanguageManager::Language expected =
        systemIsChinese ? LanguageManager::Language::ChineseSimplified
                        : LanguageManager::Language::English;
    CHECK(autoLang == expected,
          qPrintable(QString("Auto resolves to %1 (system %2)")
                         .arg(LanguageManager::instance()->languageCode())
                         .arg(QLocale::system().name())));

    /* Unsupported languages must fall back to English: verified on a
       non-Chinese system */
    if (!systemIsChinese)
        CHECK(LanguageManager::instance()->languageCode() == "en", "non-Chinese system falls back to English");

    /* ---------- 4. Menu entries complete ---------- */
    CHECK(LanguageManager::preferenceNames().size() == 3, "3 language options");

    std::printf("\npassed: %d  failed: %d\n", g_passed, g_failed);
    if (g_failed == 0)
        std::printf("ALL TESTS PASSED\n");

    return g_failed == 0 ? 0 : 1;
}
