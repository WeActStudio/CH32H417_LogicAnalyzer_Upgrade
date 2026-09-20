/*
 * CH32H417 逻辑分析仪固件升级工具
 *
 * 界面语言单元测试：验证中英文翻译文件与语言选择逻辑
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

    /* ---------- 1. 英文翻译 ---------- */
    std::printf("== English ==\n");
    LanguageManager::instance()->setPreference(LanguageManager::Preference::English);
    CHECK(LanguageManager::instance()->languageCode() == "en", "languageCode() == en");
    CHECK(T("MainWindow", "设备") == "Device", "设备 -> Device");
    CHECK(T("MainWindow", "固件文件") == "Firmware File", "固件文件 -> Firmware File");
    CHECK(T("MainWindow", "IAP 参数") == "IAP Parameters", "IAP 参数 -> IAP Parameters");
    CHECK(T("MainWindow", "就绪") == "Ready", "就绪 -> Ready");
    CHECK(T("MainWindow", "开始升级(&S)") == "&Start Upgrade", "开始升级(&S) -> &Start Upgrade");
    CHECK(T("IapWorker", "编程 FLASH ...") == "Programming FLASH ...",
          "IAP 编程提示 -> Programming FLASH ...");
    CHECK(T("LanguageManager", "简体中文") == "Simplified Chinese", "语言名 -> Simplified Chinese");

    /* ---------- 2. 中文翻译 ---------- */
    std::printf("== Chinese ==\n");
    LanguageManager::instance()->setPreference(
        LanguageManager::Preference::ChineseSimplified);
    CHECK(LanguageManager::instance()->languageCode() == "zh_CN", "languageCode() == zh_CN");
    CHECK(T("MainWindow", "设备") == "设备", "设备 保持中文");
    CHECK(T("MainWindow", "就绪") == "就绪", "就绪 保持中文");

    /* ---------- 3. 跟随系统 ---------- */
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
          qPrintable(QString("Auto 解析为 %1（系统 %2）")
                         .arg(LanguageManager::instance()->languageCode())
                         .arg(QLocale::system().name())));

    /* 不支持的语言必须回退英文：用非中文系统校验一次 */
    if (!systemIsChinese)
        CHECK(LanguageManager::instance()->languageCode() == "en", "非中文系统回退英文");

    /* ---------- 4. 菜单项齐全 ---------- */
    CHECK(LanguageManager::preferenceNames().size() == 3, "3 个语言选项");

    std::printf("\npassed: %d  failed: %d\n", g_passed, g_failed);
    if (g_failed == 0)
        std::printf("ALL TESTS PASSED\n");

    return g_failed == 0 ? 0 : 1;
}
