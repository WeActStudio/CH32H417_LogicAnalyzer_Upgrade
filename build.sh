#!/usr/bin/env bash
#
# CH32H417 逻辑分析仪固件升级工具 —— 构建脚本
#
# 运行环境：MSYS2 MINGW64（D:\msys64\mingw64.exe）
#   pacman -S mingw-w64-x86_64-qt5-static mingw-w64-x86_64-hidapi
#
# 用法：
#   ./build.sh            # 构建 Release
#   ./build.sh test       # 构建并运行固件解析单元测试
#   ./build.sh pack       # 用 UPX 压缩已构建的 exe（31MB -> 约 10MB）
#   ./build.sh size       # 生成链接 map 并统计各库占用（需重新链接一次）
#   ./build.sh clean      # 清理构建目录
#
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Windows 原生程序（qmake / lupdate / lrelease / python.exe）不识别 MSYS 的 POSIX
# 路径（/h/xxx 会被当成 H:/h/xxx）。这里同时保留一份 Windows 风格路径。
if command -v cygpath >/dev/null 2>&1; then
    SCRIPT_DIR_WIN="$(cygpath -w "${SCRIPT_DIR}")"
else
    SCRIPT_DIR_WIN="${SCRIPT_DIR}"
fi

# 工程文件（文件名不含空格，便于脚本处理）
PRO_FILE="CH32H417_LogicAnalyzer_Upgrade.pro"

# 产物 exe 名（与 .pro 中的 TARGET 一致，含空格）
EXE_NAME="CH32H417 Logic Analyzer Upgrade.exe"

BUILD_DIR="${SCRIPT_DIR}/build"

# MSYS2 静态 Qt 的 qmake 路径
#
# 默认优先 Qt6 静态库（mingw-w64-x86_64-qt6-static）；
# 只想用 Qt5 时：QMAKE_BIN=/mingw64/qt5-static/bin/qmake ./build.sh
if [ -z "${QMAKE_BIN}" ]; then
    if [ -x "/mingw64/qt6-static/bin/qmake" ]; then
        QMAKE_BIN="/mingw64/qt6-static/bin/qmake"
    else
        QMAKE_BIN="/mingw64/qt5-static/bin/qmake"
    fi
fi
QT_BIN_DIR="$(dirname "${QMAKE_BIN}")"

# 原生 g++/qmake 需要的 Windows 风格 MSYS 前缀（详见 .pro 中注释）
if [ -z "${MSYS_PREFIX_WIN}" ] && command -v cygpath >/dev/null 2>&1; then
    MSYS_PREFIX_WIN="$(cygpath -m "${MSYSTEM_PREFIX:-/mingw64}")"
fi
export MSYS_PREFIX_WIN

# Qt6 的 lupdate-pro 需要显式指定 qmake spec，否则报
#   "Could not find qmake spec 'default'"
# 注意：传给原生 exe 的路径必须是 Windows 风格
if [ -d "${QT_BIN_DIR}/../share/qt6/mkspecs/win32-g++" ]; then
    export QMAKESPEC="$(cygpath -m "${QT_BIN_DIR}/../share/qt6/mkspecs/win32-g++")"
fi

# ----------------------------------------------------------------------------
#  切换 Qt 版本（Qt5 <-> Qt6）时，构建目录里残留的 .o 是用另一套头文件编出来的，
#  直接 make 不会重新编译，链接时会出现各种莫名其妙的 undefined reference。
#  这里记录当前 qmake 指纹，不一致就整个目录重来。
# ----------------------------------------------------------------------------
qmake_fingerprint() { "${QMAKE_BIN}" -query QT_VERSION 2>/dev/null; }

purge_if_qt_changed()
{
    local dir="$1"
    local stamp="${dir}/.qt_version"
    local now
    now="$(qmake_fingerprint)"

    if [ -f "${stamp}" ] && [ "$(cat "${stamp}")" != "${now}" ]; then
        echo "==> Qt 版本已切换（$(cat "${stamp}") -> ${now}），清理 ${dir}"
        rm -rf "${dir}"
    fi
    mkdir -p "${dir}"
    echo "${now}" > "${stamp}"
}

# ----------------------------------------------------------------------------
# 生成界面翻译（中文 / 英文）
#
#   lupdate  从源码提取 tr() 字符串 -> translations/*.ts
#   i18n_fill.py 填充译文（需要 python；没有则沿用仓库里已提交的 .ts）
#   lrelease 编译 .ts -> src/translations/*.qm（打包进 exe 资源）
# ----------------------------------------------------------------------------
generate_translations()
{
    local ts_dir="${SCRIPT_DIR}/translations"
    local qm_dir="${SCRIPT_DIR}/src/translations"

    mkdir -p "${ts_dir}" "${qm_dir}"

    if command -v python >/dev/null 2>&1; then
        PYTHON_BIN=python
    elif command -v python3 >/dev/null 2>&1; then
        PYTHON_BIN=python3
    else
        PYTHON_BIN=""
    fi

    # Qt6 的 lupdate 不再接受 .pro 参数，需要使用 lupdate-pro
    if [ -x "${QT_BIN_DIR}/lupdate-pro" ]; then
        LUPDATE_BIN="${QT_BIN_DIR}/lupdate-pro"
    else
        LUPDATE_BIN="${QT_BIN_DIR}/lupdate"
    fi

    if [ -n "${PYTHON_BIN}" ] && [ -x "${LUPDATE_BIN}" ]; then
        echo "==> 更新翻译源文件 (lupdate) ..."
        ( cd "${SCRIPT_DIR}" && "${LUPDATE_BIN}" -no-obsolete "${PRO_FILE}" ) \
            || echo "警告：lupdate 执行失败，沿用现有 .ts"
        "${PYTHON_BIN}" "${SCRIPT_DIR_WIN}/tools/i18n_fill.py" "${SCRIPT_DIR_WIN}"
    else
        echo "==> 跳过 lupdate（缺少 python），使用现有 .ts"
    fi

    echo "==> 编译翻译 (lrelease) ..."
    "${QT_BIN_DIR}/lrelease" "${SCRIPT_DIR_WIN}/translations/app_zh_CN.ts" -qm "${SCRIPT_DIR_WIN}/src/translations/app_zh_CN.qm"
    "${QT_BIN_DIR}/lrelease" "${SCRIPT_DIR_WIN}/translations/app_en.ts"    -qm "${SCRIPT_DIR_WIN}/src/translations/app_en.qm"

    # qm 更新不会自动触发 rcc，touch 一下确保重新打包进 exe
    touch "${SCRIPT_DIR}/src/translations.qrc"
}

if [ "$1" = "ts" ]; then
    generate_translations
    exit 0
fi

if [ "$1" = "clean" ]; then
    echo "==> 清理 ${BUILD_DIR} ${SCRIPT_DIR}/tests/build ${SCRIPT_DIR}/build-map"
    rm -rf "${BUILD_DIR}" "${SCRIPT_DIR}/tests/build" "${SCRIPT_DIR}/build-map" 2>/dev/null || true
    exit 0
fi

# ----------------------------------------------------------------------------
# UPX 压缩（可选）
#
# 静态链接 Qt 后 exe 约 31MB，其中绝大部分是 Qt 库代码与数据表。
# UPX 把它压到约 10MB，仍是单文件、无外部依赖。
# 注意：少数杀毒软件会把 UPX 壳报成可疑文件，所以不默认开启。
# ----------------------------------------------------------------------------
if [ "$1" = "pack" ]; then
    EXE_PATH="${BUILD_DIR}/${EXE_NAME}"
    if [ ! -f "${EXE_PATH}" ]; then
        echo "错误：未找到 ${EXE_PATH}，请先执行 ./build.sh" >&2
        exit 1
    fi
    if ! command -v upx >/dev/null 2>&1; then
        echo "错误：未找到 upx，请先执行：pacman -S mingw-w64-x86_64-upx" >&2
        exit 1
    fi
    echo "==> UPX 压缩 ..."
    upx --best --lzma "${EXE_PATH}"
    echo "    大小：$(du -h "${EXE_PATH}" | cut -f1)"
    exit 0
fi

# ----------------------------------------------------------------------------
# 体积分析：重新链接一次并生成 map，统计各静态库 / 目标文件的占用
# ----------------------------------------------------------------------------
if [ "$1" = "size" ]; then
    MAP_DIR="${SCRIPT_DIR}/build-map"
    echo "==> 重新链接并生成 ${MAP_DIR}/size.map ..."
    purge_if_qt_changed "${MAP_DIR}"
    cd "${MAP_DIR}"
    "${QMAKE_BIN}" "${SCRIPT_DIR_WIN}/${PRO_FILE}" "QMAKE_LFLAGS+=-Wl,-Map=size.map"
    make -j"$(nproc 2>/dev/null || echo 4)"
    echo
    python "${SCRIPT_DIR}/tools/map_size.py" size.map 25
    exit 0
fi

if [ "$1" = "test" ]; then
    generate_translations
    echo "==> 构建并运行单元测试 ..."
    purge_if_qt_changed "${SCRIPT_DIR}/tests/build"
    cd "${SCRIPT_DIR}/tests/build"

    STATUS=0

    echo "--- 固件解析 ---"
    "${QMAKE_BIN}" ../test_firmware.pro
    make -j"$(nproc 2>/dev/null || echo 4)"
    ./test_firmware.exe || STATUS=1

    echo "--- 界面语言 ---"
    "${QMAKE_BIN}" ../test_i18n.pro
    make -j"$(nproc 2>/dev/null || echo 4)"
    ./test_i18n.exe || STATUS=1

    exit ${STATUS}
fi

if [ ! -x "${QMAKE_BIN}" ]; then
    echo "错误：找不到 qmake -> ${QMAKE_BIN}" >&2
    echo "请确认已安装：pacman -S mingw-w64-x86_64-qt5-static" >&2
    exit 1
fi

echo "==> Qt 版本：$("${QMAKE_BIN}" -v | tail -1)"
echo "==> MSYSTEM=${MSYSTEM:-unknown}  MSYSTEM_PREFIX=${MSYSTEM_PREFIX:-unknown}"

generate_translations

echo "==> 生成 Makefile ..."

purge_if_qt_changed "${BUILD_DIR}"
cd "${BUILD_DIR}"

"${QMAKE_BIN}" "${SCRIPT_DIR_WIN}/${PRO_FILE}"

echo "==> 编译 ..."
JOBS="$(nproc 2>/dev/null || echo 4)"
make -j"${JOBS}"

# 定位产物
EXE_PATH=""
for candidate in "${BUILD_DIR}/${EXE_NAME}" "${BUILD_DIR}/release/${EXE_NAME}"; do
    if [ -f "${candidate}" ]; then
        EXE_PATH="${candidate}"
        break
    fi
done

if [ -z "${EXE_PATH}" ]; then
    echo "错误：未找到生成的 exe" >&2
    exit 1
fi

# 确保驱动 DLL 与 exe 同目录
cp -f "${SCRIPT_DIR}/CH375DLL.dll"    "$(dirname "${EXE_PATH}")/" 2>/dev/null || true
cp -f "${SCRIPT_DIR}/CH375DLL64.dll"  "$(dirname "${EXE_PATH}")/" 2>/dev/null || true

echo
echo "==> 构建成功"
echo "    程序：${EXE_PATH}"
echo "    大小：$(du -h "${EXE_PATH}" | cut -f1)"
ls -1 "$(dirname "${EXE_PATH}")"
