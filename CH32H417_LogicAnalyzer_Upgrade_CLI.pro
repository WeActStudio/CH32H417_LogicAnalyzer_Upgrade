# ============================================================================
#  CH32H417 Logic Analyzer - firmware upgrade tool, console companion
#
#  The very same command line code as the graphical program, but built as a
#  Windows *console* application (CONFIG += console):
#
#    - cmd and PowerShell wait for it instead of printing the next prompt
#      while it is still running (a Windows GUI application is never waited
#      for by PowerShell),
#    - any other program can redirect its stdout / stderr,
#    - the shell prints its own prompt when the process is done, so there is
#      no prompt handling inside this program at all.
#
#  Only QtCore is linked - no window is ever opened - which keeps this
#  executable small and quick to start.
#
#  Build environment: MSYS2 (D:\msys64) MINGW64, same as the graphical one.
# ============================================================================

# QtCore only: the command line never needs QtGui / QtWidgets
QT = core
QT -= gui widgets

TEMPLATE = app

# Executable name: sits next to the graphical program
TARGET   = "CH32H417 Logic Analyzer Upgrade CLI"

VERSION  = 1.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

CONFIG  -= debug_and_release debug_and_release_target
CONFIG  -= windows
CONFIG  += console
CONFIG  += release
CONFIG  -= debug

# ----------------------------------------------------------------------------
#  Common settings for the MSYS2 static Qt builds (shared with the graphical
#  program and the unit tests)
# ----------------------------------------------------------------------------
include($$PWD/qt6_static_link.pri)

greaterThan(QT_MAJOR_VERSION, 5) {
    CONFIG += c++17
    DEFINES += QT6_BUILD
} else {
    CONFIG += c++11
}

QMAKE_CXXFLAGS_RELEASE += -Os -ffunction-sections -fdata-sections
QMAKE_CFLAGS_RELEASE   += -Os -ffunction-sections -fdata-sections
QMAKE_LFLAGS_RELEASE   += -Wl,-s -Wl,--gc-sections

QMAKE_CXXFLAGS += -Wa,-mbig-obj
QMAKE_CFLAGS   += -Wa,-mbig-obj

INCLUDEPATH += $$PWD $$PWD/src

# Only what the command line mode needs: no main window, no theme, no
# translation (its output is English by design)
SOURCES += \
    src/climain.cpp \
    src/cli.cpp \
    src/iapworker.cpp \
    src/firmwareimage.cpp \
    src/ch375dev.cpp \
    src/libusbdev.cpp \
    src/ch375_wrapper.c

HEADERS += \
    src/cli.h \
    src/iapworker.h \
    src/firmwareimage.h \
    src/ch375dev.h \
    src/libusbdev.h \
    src/ch375_wrapper.h

# ----------------------------------------------------------------------------
#  hidapi (MSYS2 mingw-w64-x86_64-hidapi, static library)
# ----------------------------------------------------------------------------
INCLUDEPATH += $$MSYS_PREFIX_WIN/include/hidapi
LIBS += -L$$MSYS_PREFIX_WIN/lib -lhidapi
LIBS += -lsetupapi -lhid

# ----------------------------------------------------------------------------
#  libusb (MSYS2 mingw-w64-x86_64-libusb, static library)
# ----------------------------------------------------------------------------
INCLUDEPATH += $$MSYS_PREFIX_WIN/include/libusb-1.0
LIBS += -L$$MSYS_PREFIX_WIN/lib -lusb-1.0
LIBS += -lsetupapi

# ----------------------------------------------------------------------------
#  Windows resources (icon + version information)
# ----------------------------------------------------------------------------
RC_FILE = src/app_cli.rc

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
