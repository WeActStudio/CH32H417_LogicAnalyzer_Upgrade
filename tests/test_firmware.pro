# 固件解析单元测试（控制台程序）
QT -= gui
QT += core

TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 5): CONFIG += c++17
else: CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle debug_and_release debug_and_release_target

TARGET = test_firmware

# Shares the static Qt link fixes with the main program (Qt6 harfbuzz /
# freetype / iconv link order)
include($$PWD/../qt6_static_link.pri)

INCLUDEPATH += $$PWD/../src

SOURCES += test_firmware.cpp
HEADERS += $$PWD/../src/firmwareimage.h
SOURCES += $$PWD/../src/firmwareimage.cpp
