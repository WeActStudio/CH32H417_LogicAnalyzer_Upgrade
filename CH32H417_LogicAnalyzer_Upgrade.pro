# ============================================================================
#  CH32H417 Logic Analyzer - 固件升级工具
#
#  构建环境：MSYS2 (D:\msys64) MINGW64
#    - Qt5 静态库   : D:\msys64\mingw64\qt5-static
#    - hidapi 静态库: D:\msys64\mingw64\lib\libhidapi.a
#
#  构建：  在 MSYS2 MINGW64 中执行  ./build.sh     （或双击 build.bat）
# ============================================================================

QT += core gui widgets

TEMPLATE = app

# 程序名（exe 文件名）：CH32H417 Logic Analyzer Upgrade
TARGET   = "CH32H417 Logic Analyzer Upgrade"

VERSION  = 1.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

CONFIG  -= debug_and_release debug_and_release_target

# ----------------------------------------------------------------------------
#  MSYS2 静态 Qt 的公共设置：Windows 风格前缀 + Qt6 静态链接顺序修正
#  （单元测试也 include 同一份，见 qt6_static_link.pri）
# ----------------------------------------------------------------------------
include($$PWD/qt6_static_link.pri)

# Qt6 需要 C++17；Qt5 用 C++11 即可（同一份工程同时支持 Qt5 / Qt6 静态库）
greaterThan(QT_MAJOR_VERSION, 5) {
    CONFIG += c++17
    DEFINES += QT6_BUILD

    # Qt6 静态链接顺序的修正（harfbuzz / freetype / iconv）见 qt6_static_link.pri
} else {
    CONFIG += c++11
}

# ----------------------------------------------------------------------------
#  Release 构建 + 体积优化
#
#  默认即 Release：不带调试符号、开启链接器垃圾段回收。
#  体积优化手段：
#    - -Os          ：以体积为优先的优化级别
#    - -Wl,-s       ：剥离符号表
#    - --gc-sections：丢弃未使用的段（配合 -ffunction/-fdata-sections）
#    - 只保留平台插件与 Vista 风格插件，去掉用不到的图像格式插件
#      （PNG 由 Qt 内建支持，不需要 qico / qjpeg / qtiff 等插件）
# ----------------------------------------------------------------------------
CONFIG  += release
CONFIG  -= debug

QMAKE_CXXFLAGS_RELEASE += -Os -ffunction-sections -fdata-sections
QMAKE_CFLAGS_RELEASE   += -Os -ffunction-sections -fdata-sections
QMAKE_LFLAGS_RELEASE   += -Wl,-s -Wl,--gc-sections

# 静态 Qt 会把所有默认插件都链进来。本程序只用到：
#   platforms     -> qwindows（必须）
#   styles        -> qmodernwindowsstyle（跟随系统深色模式需要）
#   imageformats  -> 不需要：界面图片是 PNG，Qt6Gui 内建支持，不走插件
#   iconengines   -> 不需要：不使用 SVG 图标
# Qt6 用 QTPLUGIN.<类型> = - 整类关闭（QTPLUGIN -= 对静态 Qt 无效）。
# 这一项能省掉 tiff/jpeg/webp/svg 等一大堆第三方库，对体积影响最大。
QTPLUGIN.imageformats = -
QTPLUGIN.iconengines  = -

# ch375_wrapper.c 以独立模式编译（不依赖 libsigrok / glib）
DEFINES += CH375_STANDALONE

# Qt5 静态编译需要大对象支持
QMAKE_CXXFLAGS += -Wa,-mbig-obj
QMAKE_CFLAGS   += -Wa,-mbig-obj

INCLUDEPATH += $$PWD $$PWD/src

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/iapworker.cpp \
    src/languagemanager.cpp \
    src/thememanager.cpp \
    src/firmwareimage.cpp \
    src/ch375dev.cpp \
    src/ch375_wrapper.c

HEADERS += \
    src/mainwindow.h \
    src/iapworker.h \
    src/languagemanager.h \
    src/thememanager.h \
    src/firmwareimage.h \
    src/ch375dev.h \
    src/ch375_wrapper.h

# ----------------------------------------------------------------------------
#  hidapi（MSYS2 mingw-w64-x86_64-hidapi，静态库）
# ----------------------------------------------------------------------------
INCLUDEPATH += $$MSYS_PREFIX_WIN/include/hidapi
LIBS += -L$$MSYS_PREFIX_WIN/lib -lhidapi
LIBS += -lsetupapi -lhid

# ----------------------------------------------------------------------------
#  界面翻译（中文 / 英文）
#
#  源码中的 tr() 字符串以简体中文为源语言；
#  translations/app_zh_CN.ts 与 app_en.ts 经 lrelease 编译为 .qm，
#  再通过 src/translations.qrc 打包进 exe（运行时不依赖外部文件）。
#  build.sh 会在 qmake 之前自动执行 lupdate / lrelease。
# ----------------------------------------------------------------------------
TRANSLATIONS += \
    $$PWD/translations/app_zh_CN.ts \
    $$PWD/translations/app_en.ts

RESOURCES += $$PWD/src/translations.qrc

# ----------------------------------------------------------------------------
#  应用程序图标与图片资源
#
#  resources/icons/logo.png   ：原始 logo（1080x1080 RGBA，由 "logo W.png" 整理而来）
#  resources/icons/logo.ico   ：由 logo.png 生成的多尺寸图标（16~256，含透明通道）
#  logo.ico 通过 src/app.rc 嵌入 exe，logo.png 通过 qrc 内嵌供界面使用
# ----------------------------------------------------------------------------
RESOURCES += $$PWD/resources/resources.qrc

# ----------------------------------------------------------------------------
#  Windows 资源（图标 + 版本信息）
# ----------------------------------------------------------------------------
RC_FILE = src/app.rc

# ----------------------------------------------------------------------------
#  把 CH375 驱动 DLL 复制到输出目录
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
