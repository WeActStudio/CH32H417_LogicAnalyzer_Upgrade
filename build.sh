#!/usr/bin/env bash
#
# CH32H417 Logic Analyzer firmware upgrade tool - build script
#
# Run it in an MSYS2 MINGW64 shell (D:\msys64\mingw64.exe):
#   pacman -S mingw-w64-x86_64-qt5-static mingw-w64-x86_64-hidapi
#
# Usage:
#   ./build.sh            # build Release
#   ./build.sh ts         # only refresh the translation (.ts -> .qm)
#   ./build.sh test       # build and run the unit tests
#   ./build.sh pack       # compress the built exe with UPX (31MB -> about 10MB)
#   ./build.sh size       # relink with a map file and report the size breakdown
#   ./build.sh clean      # remove the build directories
#
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Native Windows programs (qmake / python.exe) do not understand MSYS POSIX
# paths (/h/xxx would be read as H:/h/xxx), so keep a Windows style copy too.
if command -v cygpath >/dev/null 2>&1; then
    SCRIPT_DIR_WIN="$(cygpath -w "${SCRIPT_DIR}")"
else
    SCRIPT_DIR_WIN="${SCRIPT_DIR}"
fi

# Project file (no spaces in the name, easier to handle in the script)
PRO_FILE="CH32H417_LogicAnalyzer_Upgrade.pro"

# Name of the produced executable (matches TARGET in the .pro, contains spaces)
EXE_NAME="CH32H417 Logic Analyzer Upgrade.exe"

# Console companion: the same command line code built as a Windows console
# application. cmd / PowerShell wait for it, other programs can redirect its
# output and the shell prints its own prompt when it is done - none of which
# works with the graphical (Windows GUI subsystem) executable.
CLI_PRO_FILE="CH32H417_LogicAnalyzer_Upgrade_CLI.pro"
CLI_EXE_NAME="CH32H417 Logic Analyzer Upgrade CLI.exe"

BUILD_DIR="${SCRIPT_DIR}/build"
CLI_BUILD_DIR="${SCRIPT_DIR}/build-cli"

# qmake of the MSYS2 static Qt installation.
#
# Qt6 static is preferred (mingw-w64-x86_64-qt6-static); to force Qt5 run:
#   QMAKE_BIN=/mingw64/qt5-static/bin/qmake ./build.sh
if [ -z "${QMAKE_BIN}" ]; then
    if [ -x "/mingw64/qt6-static/bin/qmake" ]; then
        QMAKE_BIN="/mingw64/qt6-static/bin/qmake"
    else
        QMAKE_BIN="/mingw64/qt5-static/bin/qmake"
    fi
fi
QT_BIN_DIR="$(dirname "${QMAKE_BIN}")"

# Windows style MSYS prefix needed by the native g++/qmake (see the .pro)
if [ -z "${MSYS_PREFIX_WIN}" ] && command -v cygpath >/dev/null 2>&1; then
    MSYS_PREFIX_WIN="$(cygpath -m "${MSYSTEM_PREFIX:-/mingw64}")"
fi
export MSYS_PREFIX_WIN

# Qt6's lupdate-pro needs an explicit qmake spec, otherwise it fails with
#   "Could not find qmake spec 'default'"
# Note: paths handed to a native exe must be in Windows style
if [ -d "${QT_BIN_DIR}/../share/qt6/mkspecs/win32-g++" ]; then
    export QMAKESPEC="$(cygpath -m "${QT_BIN_DIR}/../share/qt6/mkspecs/win32-g++")"
fi

# ----------------------------------------------------------------------------
#  Build the Simplified Chinese translation
#
#  English is the source language of every tr() string, so only app_zh_CN.ts
#  is needed:
#    lupdate      extracts the tr() strings  -> translations/app_zh_CN.ts
#    i18n_fill.py fills in the translations (needs python; without it the .ts
#                 committed in the repository is reused)
#    lrelease     compiles .ts -> src/translations/app_zh_CN.qm, packed into
#                 the executable through src/translations.qrc
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

    # On Qt6 lupdate no longer accepts a .pro argument, lupdate-pro is needed
    if [ -x "${QT_BIN_DIR}/lupdate-pro" ]; then
        LUPDATE_BIN="${QT_BIN_DIR}/lupdate-pro"
    else
        LUPDATE_BIN="${QT_BIN_DIR}/lupdate"
    fi

    if [ -n "${PYTHON_BIN}" ] && [ -x "${LUPDATE_BIN}" ]; then
        echo "==> Updating the translation source (lupdate) ..."
        ( cd "${SCRIPT_DIR}" && "${LUPDATE_BIN}" -no-obsolete "${PRO_FILE}" ) \
            || echo "Warning: lupdate failed, keeping the existing .ts"
        "${PYTHON_BIN}" "${SCRIPT_DIR_WIN}/tools/i18n_fill.py" "${SCRIPT_DIR_WIN}"
    else
        echo "==> Skipping lupdate (python missing), using the existing .ts"
    fi

    echo "==> Compiling the translation (lrelease) ..."
    "${QT_BIN_DIR}/lrelease" "${SCRIPT_DIR_WIN}/translations/app_zh_CN.ts" \
        -qm "${SCRIPT_DIR_WIN}/src/translations/app_zh_CN.qm"

    # An updated .qm does not retrigger rcc, touch the qrc so it is repacked
    touch "${SCRIPT_DIR}/src/translations.qrc"
}

if [ "$1" = "ts" ]; then
    generate_translations
    exit 0
fi

# ----------------------------------------------------------------------------
#  When the Qt version is switched (Qt5 <-> Qt6) the object files left in the
#  build directory were compiled against a different set of headers, and a plain
#  make will not rebuild them, which later produces odd undefined references at
#  link time. Store a fingerprint of the current qmake and start from scratch
#  whenever it changes.
# ----------------------------------------------------------------------------
qmake_fingerprint() { "${QMAKE_BIN}" -query QT_VERSION 2>/dev/null; }

purge_if_qt_changed()
{
    local dir="$1"
    local stamp="${dir}/.qt_version"
    local now
    now="$(qmake_fingerprint)"

    if [ -f "${stamp}" ] && [ "$(cat "${stamp}")" != "${now}" ]; then
        echo "==> Qt version changed ($(cat "${stamp}") -> ${now}), cleaning ${dir}"
        rm -rf "${dir}"
    fi
    mkdir -p "${dir}"
    echo "${now}" > "${stamp}"
}

if [ "$1" = "clean" ]; then
    echo "==> Cleaning ${BUILD_DIR} ${CLI_BUILD_DIR} ${SCRIPT_DIR}/tests/build ${SCRIPT_DIR}/build-map"
    rm -rf "${BUILD_DIR}" "${CLI_BUILD_DIR}" "${SCRIPT_DIR}/tests/build" "${SCRIPT_DIR}/build-map" 2>/dev/null || true
    exit 0
fi

# ----------------------------------------------------------------------------
#  UPX compression (optional)
#
#  With a statically linked Qt the executable is about 31MB, most of it Qt
#  library code and data tables. UPX brings it down to roughly 10MB, still a
#  single file with no external dependencies.
#  Note: some antivirus products flag the UPX stub, so this is not enabled
#  by default.
# ----------------------------------------------------------------------------
if [ "$1" = "pack" ]; then
    EXE_PATH="${BUILD_DIR}/${EXE_NAME}"
    CLI_PATH="${BUILD_DIR}/${CLI_EXE_NAME}"
    if [ ! -f "${EXE_PATH}" ]; then
        echo "Error: ${EXE_PATH} not found, run ./build.sh first" >&2
        exit 1
    fi
    if ! command -v upx >/dev/null 2>&1; then
        echo "Error: upx not found, install it with: pacman -S mingw-w64-x86_64-upx" >&2
        exit 1
    fi
    echo "==> Compressing with UPX ..."
    upx --best --lzma "${EXE_PATH}"
    echo "    size: $(du -h "${EXE_PATH}" | cut -f1)"
    if [ -f "${CLI_PATH}" ]; then
        upx --best --lzma "${CLI_PATH}"
        echo "    size: $(du -h "${CLI_PATH}" | cut -f1)"
    fi
    exit 0
fi

# ----------------------------------------------------------------------------
#  Size analysis: relink once with a map file and report what each static
#  library / object file contributes
# ----------------------------------------------------------------------------
if [ "$1" = "size" ]; then
    MAP_DIR="${SCRIPT_DIR}/build-map"
    echo "==> Relinking and generating ${MAP_DIR}/size.map ..."
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
    echo "==> Building and running the unit tests ..."
    purge_if_qt_changed "${SCRIPT_DIR}/tests/build"
    cd "${SCRIPT_DIR}/tests/build"

    STATUS=0

    echo "--- firmware parsing ---"
    "${QMAKE_BIN}" ../test_firmware.pro
    make -j"$(nproc 2>/dev/null || echo 4)"
    ./test_firmware.exe || STATUS=1

    echo "--- UI language ---"
    "${QMAKE_BIN}" ../test_i18n.pro
    make -j"$(nproc 2>/dev/null || echo 4)"
    ./test_i18n.exe || STATUS=1

    exit ${STATUS}
fi

if [ ! -x "${QMAKE_BIN}" ]; then
    echo "Error: qmake not found -> ${QMAKE_BIN}" >&2
    echo "Install it with: pacman -S mingw-w64-x86_64-qt5-static" >&2
    exit 1
fi

echo "==> Qt version: $("${QMAKE_BIN}" -v | tail -1)"
echo "==> MSYSTEM=${MSYSTEM:-unknown}  MSYSTEM_PREFIX=${MSYSTEM_PREFIX:-unknown}"

generate_translations

echo "==> Generating the Makefile ..."

purge_if_qt_changed "${BUILD_DIR}"
cd "${BUILD_DIR}"

"${QMAKE_BIN}" "${SCRIPT_DIR_WIN}/${PRO_FILE}"

echo "==> Compiling ..."
JOBS="$(nproc 2>/dev/null || echo 4)"
make -j"${JOBS}"

# Locate the produced binary
EXE_PATH=""
for candidate in "${BUILD_DIR}/${EXE_NAME}" "${BUILD_DIR}/release/${EXE_NAME}"; do
    if [ -f "${candidate}" ]; then
        EXE_PATH="${candidate}"
        break
    fi
done

if [ -z "${EXE_PATH}" ]; then
    echo "Error: the executable was not produced" >&2
    exit 1
fi

# Keep the driver DLLs next to the executable
cp -f "${SCRIPT_DIR}/CH375DLL.dll"    "$(dirname "${EXE_PATH}")/" 2>/dev/null || true
cp -f "${SCRIPT_DIR}/CH375DLL64.dll"  "$(dirname "${EXE_PATH}")/" 2>/dev/null || true

# ----------------------------------------------------------------------------
#  The console companion, into the same directory: the graphical program looks
#  for it next to itself and hands its command line over to it.
# ----------------------------------------------------------------------------
echo
echo "==> Building the console companion (${CLI_EXE_NAME}) ..."

purge_if_qt_changed "${CLI_BUILD_DIR}"
cd "${CLI_BUILD_DIR}"

"${QMAKE_BIN}" "${SCRIPT_DIR_WIN}/${CLI_PRO_FILE}"
make -j"${JOBS}"

CLI_PATH=""
for candidate in "${CLI_BUILD_DIR}/${CLI_EXE_NAME}" "${CLI_BUILD_DIR}/release/${CLI_EXE_NAME}"; do
    if [ -f "${candidate}" ]; then
        CLI_PATH="${candidate}"
        break
    fi
done

if [ -z "${CLI_PATH}" ]; then
    echo "Error: the console companion was not produced" >&2
    exit 1
fi

cp -f "${CLI_PATH}" "${BUILD_DIR}/${CLI_EXE_NAME}"

echo
echo "==> Build succeeded"
echo "    program: ${EXE_PATH}"
echo "    size:    $(du -h "${EXE_PATH}" | cut -f1)"
echo "    console: ${BUILD_DIR}/${CLI_EXE_NAME}"
echo "    size:    $(du -h "${BUILD_DIR}/${CLI_EXE_NAME}" | cut -f1)"
ls -1 "$(dirname "${EXE_PATH}")"
