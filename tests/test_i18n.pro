# Unit test for the UI language (Qt Widgets is needed, LanguageManager uses
# QApplication)
QT += core gui widgets
greaterThan(QT_MAJOR_VERSION, 5): CONFIG += c++17
else: CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
CONFIG -= debug_and_release debug_and_release_target

TEMPLATE = app
TARGET   = test_i18n

MSYS_PREFIX = $$(MSYSTEM_PREFIX)
isEmpty(MSYS_PREFIX): MSYS_PREFIX = /mingw64

# Shares the static Qt link fixes with the main program (Qt6 harfbuzz /
# freetype / iconv link order)
include($$PWD/../qt6_static_link.pri)

SOURCES += \
    test_i18n.cpp \
    ../src/languagemanager.cpp

HEADERS += ../src/languagemanager.h

# Uses the same translation resource as the main program
RESOURCES += ../src/translations.qrc

INCLUDEPATH += .. ../src
