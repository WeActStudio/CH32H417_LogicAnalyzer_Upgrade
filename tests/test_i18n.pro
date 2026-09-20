# 界面语言单元测试（需要 Qt Widgets，LanguageManager 会用到 QApplication）
QT += core gui widgets
greaterThan(QT_MAJOR_VERSION, 5): CONFIG += c++17
else: CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
CONFIG -= debug_and_release debug_and_release_target

TEMPLATE = app
TARGET   = test_i18n

DEFINES += CH375_STANDALONE

MSYS_PREFIX = $$(MSYSTEM_PREFIX)
isEmpty(MSYS_PREFIX): MSYS_PREFIX = /mingw64

# 与主程序共用静态 Qt 的链接修正（Qt6 的 harfbuzz / freetype / iconv 链接顺序）
include($$PWD/../qt6_static_link.pri)

SOURCES += \
    test_i18n.cpp \
    ../src/languagemanager.cpp

HEADERS += ../src/languagemanager.h

# 与主程序共用同一份翻译资源
RESOURCES += ../src/translations.qrc

INCLUDEPATH += .. ../src
