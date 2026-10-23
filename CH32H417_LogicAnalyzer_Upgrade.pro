# ============================================================================
#  CH32H417 Logic Analyzer - firmware upgrade tool
#
#  Build environment: MSYS2 (D:\msys64) MINGW64
#    - Qt5 static libs : D:\msys64\mingw64\qt5-static
#    - hidapi static   : D:\msys64\mingw64\lib\libhidapi.a
#
#  Build: run ./build.sh in an MSYS2 MINGW64 shell (or double click build.bat)
# ============================================================================

QT += core gui widgets

TEMPLATE = app

# Executable name
TARGET   = "CH32H417 Logic Analyzer Upgrade"

VERSION  = 1.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

CONFIG  -= debug_and_release debug_and_release_target

# ----------------------------------------------------------------------------
#  Common settings for the MSYS2 static Qt builds: Windows style prefix plus
#  the Qt6 static link order fixes (shared with the unit tests, see
#  qt6_static_link.pri)
# ----------------------------------------------------------------------------
include($$PWD/qt6_static_link.pri)

# Qt6 needs C++17; Qt5 is fine with C++11 (the same project file supports both
# the Qt5 and the Qt6 static libraries)
greaterThan(QT_MAJOR_VERSION, 5) {
    CONFIG += c++17
    DEFINES += QT6_BUILD

    # The Qt6 static link order fixes (harfbuzz / freetype / iconv) live in
    # qt6_static_link.pri
} else {
    CONFIG += c++11
}

# ----------------------------------------------------------------------------
#  Release build and size optimisation
#
#  Release is the default: no debug symbols, linker garbage collection enabled.
#  Size is reduced by:
#    - -Os          : optimise for size
#    - -Wl,-s       : strip the symbol table
#    - --gc-sections: drop unused sections (with -ffunction/-fdata-sections)
#    - keeping only the platform and Vista style plugins and dropping the
#      unused image format plugins (PNG is built into Qt, so qico / qjpeg /
#      qtiff are not needed)
# ----------------------------------------------------------------------------
CONFIG  += release
CONFIG  -= debug

QMAKE_CXXFLAGS_RELEASE += -Os -ffunction-sections -fdata-sections
QMAKE_CFLAGS_RELEASE   += -Os -ffunction-sections -fdata-sections
QMAKE_LFLAGS_RELEASE   += -Wl,-s -Wl,--gc-sections

# A static Qt links in every default plugin. This program only needs:
#   platforms     -> qwindows (required)
#   styles        -> qmodernwindowsstyle (to follow the system dark mode)
#   imageformats  -> not needed: the UI artwork is PNG, supported by Qt6Gui
#   iconengines   -> not needed: no SVG icons
# On Qt6 a whole plugin class is disabled with QTPLUGIN.<type> = -
# (QTPLUGIN -= has no effect with a static Qt).
# This drops tiff/jpeg/webp/svg and a pile of third party libraries, and is the
# single biggest win for the binary size.
QTPLUGIN.imageformats = -
QTPLUGIN.iconengines  = -

# Qt5 static builds need big object file support
QMAKE_CXXFLAGS += -Wa,-mbig-obj
QMAKE_CFLAGS   += -Wa,-mbig-obj

INCLUDEPATH += $$PWD $$PWD/src

SOURCES += \
    src/main.cpp \
    src/cli.cpp \
    src/mainwindow.cpp \
    src/iapworker.cpp \
    src/iapctl.cpp \
    src/languagemanager.cpp \
    src/thememanager.cpp \
    src/firmwareimage.cpp \
    src/ch375dev.cpp \
    src/libusbdev.cpp \
    src/serialdev.cpp \
    src/ch375_wrapper.c

HEADERS += \
    src/cli.h \
    src/mainwindow.h \
    src/iapworker.h \
    src/iapctl.h \
    src/languagemanager.h \
    src/thememanager.h \
    src/firmwareimage.h \
    src/ch375dev.h \
    src/libusbdev.h \
    src/serialdev.h \
    src/ch375_wrapper.h

# ----------------------------------------------------------------------------
#  hidapi (MSYS2 mingw-w64-x86_64-hidapi, static library)
# ----------------------------------------------------------------------------
INCLUDEPATH += $$MSYS_PREFIX_WIN/include/hidapi
LIBS += -L$$MSYS_PREFIX_WIN/lib -lhidapi
LIBS += -lsetupapi -lhid

# ----------------------------------------------------------------------------
#  Serial channel (USB-to-UART application): SetupAPI + cfgmgr32 are linked
#  statically from the MinGW toolchain, no runtime DLL is needed.
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
#  libusb (MSYS2 mingw-w64-x86_64-libusb, static library)
#
#  Second way to reach a board: the CH375 driver and a generic USB driver
#  (WinUSB) are mutually exclusive, so both channels are built in and the one
#  that can open the board is used.
# ----------------------------------------------------------------------------
INCLUDEPATH += $$MSYS_PREFIX_WIN/include/libusb-1.0
LIBS += -L$$MSYS_PREFIX_WIN/lib -lusb-1.0
LIBS += -lsetupapi -lcfgmgr32

# ----------------------------------------------------------------------------
#  UI translation (Simplified Chinese, Russian, German, Spanish)
#
#  English is the source language of every tr() string in the sources;
#  translations/app_<lang>.ts is compiled with lrelease into
#  src/translations/app_<lang>.qm and packed into the executable through
#  src/translations.qrc (no external file needed at run time).
#  build.sh runs lupdate / lrelease before qmake.
# ----------------------------------------------------------------------------
TRANSLATIONS += \
    $$PWD/translations/app_zh_CN.ts \
    $$PWD/translations/app_ru.ts \
    $$PWD/translations/app_de.ts \
    $$PWD/translations/app_es.ts

RESOURCES += $$PWD/src/translations.qrc

# ----------------------------------------------------------------------------
#  Application icon and image resources
#
#  resources/icons/logo.png : source logo (1080x1080 RGBA)
#  resources/icons/logo.ico : multi size icon (16~256, with alpha) generated
#                             from logo.png by tools/make_icon.py
#  logo.ico is embedded into the executable through src/app.rc, logo.png is
#  built into the binary through the qrc for the UI
# ----------------------------------------------------------------------------
RESOURCES += $$PWD/resources/resources.qrc

# ----------------------------------------------------------------------------
#  Windows resources (icon + version information)
# ----------------------------------------------------------------------------
RC_FILE = src/app.rc

# ----------------------------------------------------------------------------
#  Copy the CH375 driver DLLs next to the executable
# ----------------------------------------------------------------------------
DLL_FILES = $$PWD/CH375DLL.dll $$PWD/CH375DLL64.dll

defineTest(copyDlls) {
    for(f, DLL_FILES) {
        QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($$f) $$shell_path($$OUT_PWD) $$escape_expand(\\n\\t)
    }
    export(QMAKE_POST_LINK)
    return(true)
}
copyDlls()
