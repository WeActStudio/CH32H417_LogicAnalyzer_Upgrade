/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * Command line interface implementation
 *
 * Exit codes:
 *   0  success
 *   1  usage / argument error
 *   2  firmware file error
 *   3  no usable device found
 *   4  upgrade failed
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "cli.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QEventLoop>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QStringList>
#include <QTextStream>
#include <QThread>

#include "ch375dev.h"
#include "ch375_wrapper.h"
#include "firmwareimage.h"
#include "iapworker.h"

#include <cstdio>
#include <cstring>
#include <vector>

#ifdef Q_OS_WIN
#include <windows.h>
#include <tlhelp32.h>
#endif

namespace {

/* Process exit codes (documented in README.md / README_zh_CN.md) */
enum {
    kExitOk = 0,
    kExitUsage = 1,
    kExitFirmware = 2,
    kExitNoDevice = 3,
    kExitUpgradeFailed = 4
};

struct CliOptions
{
    bool help = false;
    bool version = false;
    bool list = false;
    bool quiet = false;
    bool verbose = false;
    bool preferLibusb = false;   /* Use the libusb / WinUSB channel when both can see the board */

    QString firmware;
    QString device;
    QString logFile;

    quint32 binBase = 0x08006000;
    quint16 iapVid = CH32H417_IAP_VID;
    quint16 iapPid = CH32H417_IAP_PID;
    int waitSeconds = 15;
};

QFile *logFileHandle = nullptr;

/* Set once the first line has been written (see beginOutput()) */
bool outputStarted = false;

/*
 * Set by the console companion: the shell waits for that process, so it cannot
 * print a prompt while the output is written.
 */
bool shellWaits = false;

#ifdef Q_OS_WIN
/** File name of the console companion, next to the graphical program */
const wchar_t kConsoleAppName[] = L"CH32H417 Logic Analyzer Upgrade CLI.exe";

/*
 * The prompt PowerShell printed while this program was starting up. It is
 * erased before the output starts and written again below it, so the screen
 * ends up looking the way it does under cmd.exe: the command, the output and
 * then a ready prompt with the cursor behind it.
 */
bool shellPromptErased = false;
QString shellPromptText;
WORD shellPromptAttributes = 0;
#endif /* Q_OS_WIN */

#ifdef Q_OS_WIN
/**
 * File name (without directories) of the process that started this program,
 * empty when it cannot be determined.
 */
QString parentProcessName()
{
    const DWORD pid = ::GetCurrentProcessId();

    HANDLE snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return QString();

    PROCESSENTRY32W entry;
    std::memset(&entry, 0, sizeof(entry));
    entry.dwSize = sizeof(entry);

    DWORD parentPid = 0;
    if (::Process32FirstW(snapshot, &entry)) {
        do {
            if (entry.th32ProcessID == pid) {
                parentPid = entry.th32ParentProcessID;
                break;
            }
        } while (::Process32NextW(snapshot, &entry));
    }
    ::CloseHandle(snapshot);

    if (parentPid == 0)
        return QString();

    HANDLE parent = ::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, parentPid);
    if (!parent)
        return QString();

    WCHAR path[MAX_PATH];
    DWORD size = MAX_PATH;
    QString name;
    if (::QueryFullProcessImageNameW(parent, 0, path, &size))
        name = QString::fromWCharArray(path).section(QLatin1Char('\\'), -1);

    ::CloseHandle(parent);
    return name;
}

/**
 * Shells that do not wait for a Windows GUI application: they print the next
 * prompt while the program is still running, so the output would otherwise be
 * appended to that prompt.
 */
bool isNonWaitingShell(const QString &name)
{
    static const QStringList shells = {
        QStringLiteral("powershell.exe"), QStringLiteral("pwsh.exe")
    };
    return shells.contains(name, Qt::CaseInsensitive);
}
#endif /* Q_OS_WIN */

/**
 * A Windows GUI application has no console. Attach to the console of the
 * calling process (cmd / PowerShell) so that the output is visible; when the
 * program was started without one, allocate a console of its own.
 */
void acquireConsole()
{
#ifdef Q_OS_WIN
    /*
     * A Windows GUI application starts without stdio handles. When the output
     * is redirected ("> file" or a pipe) the handle is inherited and must be
     * left alone, otherwise the redirected output would be lost. Only when
     * there is no handle at all do we attach to the console of the calling
     * process (cmd / PowerShell) and reopen stdout / stderr on it.
     */
    const HANDLE out = ::GetStdHandle(STD_OUTPUT_HANDLE);
    const bool redirected = (out != NULL && out != INVALID_HANDLE_VALUE);

    if (!redirected) {
        if (!::AttachConsole(ATTACH_PARENT_PROCESS))
            ::AllocConsole();

        std::freopen("CONOUT$", "w", stdout);
        std::freopen("CONOUT$", "w", stderr);
        std::freopen("CONIN$", "r", stdin);
    }
#endif
    setvbuf(stdout, nullptr, _IONBF, 0);
    setvbuf(stderr, nullptr, _IONBF, 0);
}

/**
 * Handle of the console the output goes to, or NULL when there is none (the
 * output was redirected to a file or to a pipe). @a opened tells whether the
 * handle has to be closed again.
 */
HANDLE consoleOutput(bool &opened)
{
    opened = false;

    HANDLE out = ::GetStdHandle(STD_OUTPUT_HANDLE);
    if (out != NULL && out != INVALID_HANDLE_VALUE)
        return out;

    /* Started without stdio handles: use the console acquireConsole() attached
       to (or allocated). */
    out = ::CreateFileW(L"CONOUT$", GENERIC_READ | GENERIC_WRITE,
                        FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                        OPEN_EXISTING, 0, nullptr);
    if (out == INVALID_HANDLE_VALUE)
        return NULL;

    opened = true;
    return out;
}

/**
 * First @a count characters of a console row, empty when it cannot be read.
 * @a attributes (optional) receives the colours the row is written in.
 */
QString consoleRowText(HANDLE out, SHORT row, int count, WORD *attributes = nullptr)
{
    if (count <= 0)
        return QString();

    std::vector<CHAR_INFO> buffer(static_cast<size_t>(count));

    COORD size;
    size.X = static_cast<SHORT>(count);
    size.Y = 1;

    COORD origin;
    origin.X = 0;
    origin.Y = row;

    SMALL_RECT rect;
    rect.Left = 0;
    rect.Top = row;
    rect.Right = static_cast<SHORT>(count - 1);
    rect.Bottom = row;

    if (!::ReadConsoleOutputW(out, buffer.data(), size, origin, &rect))
        return QString();

    WORD attr = 0;
    QString text;
    text.reserve(count);
    for (int i = 0; i < count; ++i) {
        text.append(QChar(buffer[static_cast<size_t>(i)].Char.UnicodeChar));
        /* The colour of the first cell that is not blank */
        if (attr == 0 && buffer[static_cast<size_t>(i)].Char.UnicodeChar != L' ')
            attr = buffer[static_cast<size_t>(i)].Attributes;
    }

    if (attributes)
        *attributes = attr;

    return text;
}

/** Overwrite a console row with blanks and put the cursor at its start */
void eraseConsoleRow(HANDLE out, SHORT row, SHORT width)
{
    DWORD written = 0;

    COORD start;
    start.X = 0;
    start.Y = row;
    ::FillConsoleOutputCharacterW(out, L' ', width, start, &written);

    CONSOLE_SCREEN_BUFFER_INFO info;
    if (::GetConsoleScreenBufferInfo(out, &info))
        ::FillConsoleOutputAttribute(out, info.wAttributes, width, start, &written);

    ::SetConsoleCursorPosition(out, start);
}

/**
 * Take over the line the calling shell left behind.
 *
 * PowerShell (unlike cmd.exe) does not wait for a Windows GUI application: it
 * prints its next prompt while this program is still starting up. Left alone
 * that prompt would stay above the output as a stray line that belongs to
 * nothing, so it is read back, erased and written again below the output (see
 * finishShellPrompt()). The output itself therefore starts on the very line
 * the prompt was on.
 *
 * When the cursor is still in the first column the shell has not written a
 * prompt (cmd.exe waits for this program, and a redirected output is not a
 * console at all), and nothing is touched.
 */
void startOnFreshLine()
{
#ifdef Q_OS_WIN
    bool opened = false;
    HANDLE out = consoleOutput(opened);
    if (!out)
        return;

    /* Not a console (a file or a pipe): nothing to align with. */
    CONSOLE_SCREEN_BUFFER_INFO info;
    bool cursorKnown = (::GetConsoleScreenBufferInfo(out, &info) != FALSE);

    /*
     * A shell that does not wait prints its prompt only after this program
     * has been started, so give it a moment to show up (it normally takes a
     * few milliseconds) instead of racing against it. The console companion
     * is waited for by the shell, there nothing can show up any more.
     */
    if (cursorKnown && !shellWaits && info.dwCursorPosition.X == 0
        && isNonWaitingShell(parentProcessName())) {
        for (int i = 0; i < 30 && info.dwCursorPosition.X == 0; ++i) {
            QThread::msleep(10);
            cursorKnown = (::GetConsoleScreenBufferInfo(out, &info) != FALSE);
            if (!cursorKnown)
                break;
        }
    }

    if (cursorKnown && info.dwCursorPosition.X != 0) {
        const SHORT row = info.dwCursorPosition.Y;
        WORD attributes = 0;
        const QString prompt = consoleRowText(out, row, info.dwSize.X, &attributes)
                                   .trimmed();

        /* Erase the prompt: the output takes the line it was written on */
        eraseConsoleRow(out, row, info.dwSize.X);

        /*
         * Only a prompt that could be read back can be drawn again below the
         * output. Some terminals refuse ReadConsoleOutputW; there the cursor
         * simply stays at the end of the output, which is still better than a
         * stray prompt line above it.
         */
        if (!prompt.isEmpty()) {
            shellPromptText = prompt;
            shellPromptAttributes = attributes;
            shellPromptErased = true;
        }
    }

    if (opened)
        ::CloseHandle(out);
#endif
}

/**
 * Draw the prompt that was erased before the output, below it.
 *
 * PowerShell is already waiting for input while the output is written, so
 * without this the cursor would sit at the end of the output with no prompt
 * anywhere near: the shell only looks alive again after the user presses a
 * key. Writing the prompt back leaves a ready shell behind.
 */
void finishShellPrompt()
{
#ifdef Q_OS_WIN
    if (!shellPromptErased || !outputStarted)
        return;
    shellPromptErased = false;

    bool opened = false;
    HANDLE out = consoleOutput(opened);
    if (!out)
        return;

    DWORD written = 0;

    /* Output that did not end with a line break: continue on the next line */
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (::GetConsoleScreenBufferInfo(out, &info) && info.dwCursorPosition.X != 0)
        ::WriteConsoleW(out, L"\r\n", 2, &written, nullptr);

    COORD start;
    if (::GetConsoleScreenBufferInfo(out, &info))
        start = info.dwCursorPosition;
    else {
        start.X = 0;
        start.Y = 0;
    }

    ::WriteConsoleW(out, reinterpret_cast<LPCWSTR>(shellPromptText.utf16()),
                    static_cast<DWORD>(shellPromptText.size()), &written, nullptr);

    if (shellPromptAttributes != 0 && written > 0) {
        DWORD painted = 0;
        ::FillConsoleOutputAttribute(out, shellPromptAttributes, written, start, &painted);
    }

    if (opened)
        ::CloseHandle(out);
#endif
}

/**
 * Called before the very first line is written: the shell prompt PowerShell
 * prints while this program is starting up is on the screen by then, so the
 * cursor position tells whether the output has to continue below it.
 */
void beginOutput()
{
    if (outputStarted)
        return;
    outputStarted = true;
    startOnFreshLine();
}

void printLine(const QString &text)
{
    beginOutput();

    std::fputs(qPrintable(text), stdout);
    std::fputc('\n', stdout);

    if (logFileHandle)
        logFileHandle->write((text + QLatin1Char('\n')).toUtf8());
}

void printError(const QString &text)
{
    beginOutput();

    std::fputs(qPrintable(text), stderr);
    std::fputc('\n', stderr);

    if (logFileHandle)
        logFileHandle->write((text + QLatin1Char('\n')).toUtf8());
}

void printUsage(FILE *stream)
{
    beginOutput();

    /*
     * No leading empty line: beginOutput() already continues below the prompt
     * the calling shell may have printed, and a redirected output ("> file")
     * must start with the banner, not with a blank line.
     */
    const QString usage = QStringLiteral(
        "CH32H417 Logic Analyzer Firmware Upgrade Tool %1\n"
        "\n"
        "Usage:\n"
        "  \"CH32H417 Logic Analyzer Upgrade\" --firmware <file> [options]\n"
        "  \"CH32H417 Logic Analyzer Upgrade\" --list\n"
        "  \"CH32H417 Logic Analyzer Upgrade\" --help | --version\n"
        "\n"
        "Upgrade options:\n"
        "  -f, --firmware <path>    Firmware file (.hex or .bin), required for upgrading\n"
        "  -d, --device <selector>  Device index (0..15) or USB serial number prefix\n"
        "  -b, --base <hex>         Base address for .bin files (default 08006000)\n"
        "      --iap-vid <hex>      VID in IAP (HID) mode (default 1A86)\n"
        "      --iap-pid <hex>      PID in IAP (HID) mode (default FE17)\n"
        "  -w, --wait <seconds>     Seconds to wait for the IAP device (default 15)\n"
        "      --libusb             Prefer the libusb / WinUSB channel over CH375\n"
        "      --log <path>         Also write the upgrade log to a file\n"
        "  -q, --quiet              Print only the progress, the errors and the result\n"
        "      --verbose            Also print the CH375 driver diagnostics\n"
        "\n"
        "Other commands:\n"
        "  -l, --list               List the attached devices and exit\n"
        "  -h, --help               Show this help and exit\n"
        "      --version            Show the version and exit\n"
        "\n"
        "Exit codes:\n"
        "  0 success   1 usage error   2 firmware error   3 no device   4 upgrade failed\n"
        "\n"
        "Examples:\n"
        "  \"CH32H417 Logic Analyzer Upgrade\" --list\n"
        "  \"CH32H417 Logic Analyzer Upgrade\" -f firmware.hex\n"
        "  \"CH32H417 Logic Analyzer Upgrade\" -f app.bin -b 08006000 -d 0 -q\n"
        "\n"
        "Note: the graphical interface only opens when the program is started\n"
        "      from Windows Explorer (or any other non-console parent). From a\n"
        "      command prompt it stays in this command line mode.\r\n")
        .arg(QCoreApplication::applicationVersion());

    std::fputs(qPrintable(usage), stream);
}

/**
 * Read the value of an option that can be written as "--name=value" or
 * "--name value" ("-n value" for the short forms).
 */
bool optionValue(const QStringList &args, int &i, const QString &arg,
                 const QString &name, QString &value)
{
    const QString prefix = QStringLiteral("--") + name + QStringLiteral("=");
    if (arg.startsWith(prefix)) {
        value = arg.mid(prefix.size());
        return true;
    }
    if (arg == QStringLiteral("--") + name || arg == QStringLiteral("-") + name.left(1)) {
        if (i + 1 >= args.size())
            return false;
        value = args.at(++i);
        return true;
    }
    return false;
}

bool parseHex16(const QString &text, quint16 &value, QString &error)
{
    QString t = text.trimmed();
    if (t.startsWith(QLatin1String("0x"), Qt::CaseInsensitive))
        t = t.mid(2);

    bool ok = false;
    const unsigned int v = t.toUInt(&ok, 16);
    if (!ok || v > 0xFFFF) {
        error = QStringLiteral("Invalid hexadecimal value: %1").arg(text);
        return false;
    }

    value = static_cast<quint16>(v);
    return true;
}

bool parseHex32(const QString &text, quint32 &value, QString &error)
{
    QString t = text.trimmed();
    if (t.startsWith(QLatin1String("0x"), Qt::CaseInsensitive))
        t = t.mid(2);

    bool ok = false;
    const unsigned long v = t.toULong(&ok, 16);
    if (!ok || v > 0xFFFFFFFFUL) {
        error = QStringLiteral("Invalid hexadecimal value: %1").arg(text);
        return false;
    }

    value = static_cast<quint32>(v);
    return true;
}

bool parseArgs(const QStringList &args, CliOptions &opt, QString &error)
{
    for (int i = 0; i < args.size(); ++i) {
        const QString arg = args.at(i);
        QString value;

        if (arg == QLatin1String("-h") || arg == QLatin1String("--help")) {
            opt.help = true;
            continue;
        }
        if (arg == QLatin1String("--version")) {
            opt.version = true;
            continue;
        }
        if (arg == QLatin1String("-l") || arg == QLatin1String("--list")) {
            opt.list = true;
            continue;
        }
        if (arg == QLatin1String("-q") || arg == QLatin1String("--quiet")) {
            opt.quiet = true;
            continue;
        }
        if (arg == QLatin1String("--verbose")) {
            opt.verbose = true;
            continue;
        }
        if (arg == QLatin1String("--libusb")) {
            /* Prefer the libusb / WinUSB channel over the CH375 one */
            opt.preferLibusb = true;
            continue;
        }
        if (arg == QLatin1String("--cli")) {
            continue;   /* explicit headless mode, no extra meaning */
        }
        /* GUI only switches, accepted and ignored in the headless mode */
        if (arg.startsWith(QLatin1String("--lang")) || arg.startsWith(QLatin1String("--theme"))
            || arg.startsWith(QLatin1String("--screenshot")) || arg.startsWith(QLatin1String("--autoswitch"))) {
            /* "--xxx=value" carries the value in the same argument */
            if (arg.contains(QLatin1Char('=')))
                continue;
            if (i + 1 < args.size())
                ++i;
            continue;
        }

        if (arg == QLatin1String("-f") || arg.startsWith(QLatin1String("--firmware"))) {
            if (!optionValue(args, i, arg, QStringLiteral("firmware"), value)) {
                error = QStringLiteral("Missing value for --firmware");
                return false;
            }
            opt.firmware = value;
            continue;
        }
        if (arg == QLatin1String("-d") || arg.startsWith(QLatin1String("--device"))) {
            if (!optionValue(args, i, arg, QStringLiteral("device"), value)) {
                error = QStringLiteral("Missing value for --device");
                return false;
            }
            opt.device = value;
            continue;
        }
        if (arg == QLatin1String("-b") || arg.startsWith(QLatin1String("--base"))) {
            if (!optionValue(args, i, arg, QStringLiteral("base"), value)) {
                error = QStringLiteral("Missing value for --base");
                return false;
            }
            if (!parseHex32(value, opt.binBase, error))
                return false;
            continue;
        }
        if (arg.startsWith(QLatin1String("--iap-vid"))) {
            if (!optionValue(args, i, arg, QStringLiteral("iap-vid"), value)) {
                error = QStringLiteral("Missing value for --iap-vid");
                return false;
            }
            if (!parseHex16(value, opt.iapVid, error))
                return false;
            continue;
        }
        if (arg.startsWith(QLatin1String("--iap-pid"))) {
            if (!optionValue(args, i, arg, QStringLiteral("iap-pid"), value)) {
                error = QStringLiteral("Missing value for --iap-pid");
                return false;
            }
            if (!parseHex16(value, opt.iapPid, error))
                return false;
            continue;
        }
        if (arg == QLatin1String("-w") || arg.startsWith(QLatin1String("--wait"))) {
            if (!optionValue(args, i, arg, QStringLiteral("wait"), value)) {
                error = QStringLiteral("Missing value for --wait");
                return false;
            }
            bool ok = false;
            const int seconds = value.toInt(&ok);
            if (!ok || seconds < 1) {
                error = QStringLiteral("Invalid value for --wait: %1").arg(value);
                return false;
            }
            opt.waitSeconds = seconds;
            continue;
        }
        if (arg.startsWith(QLatin1String("--log"))) {
            if (!optionValue(args, i, arg, QStringLiteral("log"), value)) {
                error = QStringLiteral("Missing value for --log");
                return false;
            }
            opt.logFile = value;
            continue;
        }

        error = QStringLiteral("Unknown option: %1").arg(arg);
        return false;
    }

    return true;
}

/* CH375 DLL diagnostics printed through the CLI (may come from any thread) */
void ch375CliLog(int level, const char *message)
{
    if (!message)
        return;

    const char *tag = (level == CH375_LOG_ERROR) ? "error"
                                                 : ((level == CH375_LOG_WARN) ? "warn " : "info ");
    printLine(QStringLiteral("  [ch375 %1] %2")
                  .arg(QString::fromLatin1(tag))
                  .arg(QString::fromLocal8Bit(message)));
}

void printDeviceList(const QList<Ch375DeviceInfo> &devices)
{
    if (devices.isEmpty()) {
        printLine(QStringLiteral("No device found"));
        return;
    }

    for (const Ch375DeviceInfo &info : devices)
        printLine(info.description());
}

/**
 * Pick the device to upgrade: an explicit index / serial number / COM port
 * wins, otherwise the first application mode device, otherwise a device
 * already in IAP mode.
 *
 * A board is claimed by one driver at a time, so it appears on a single
 * channel. When several channels report an application mode device (possible
 * while a board is re-enumerating) the CH375 one is used, unless --libusb was
 * given.
 */
int selectDevice(const QList<Ch375DeviceInfo> &devices, const QString &selector,
                 bool preferLibusb, Ch375DeviceInfo &selected)
{
    if (!selector.isEmpty()) {
        bool isIndex = false;
        const int index = selector.toInt(&isIndex);

        for (const Ch375DeviceInfo &info : devices) {
            if (isIndex) {
                if (!info.isIap && info.index == index) {
                    selected = info;
                    return 0;
                }
            } else if (info.serial.startsWith(selector, Qt::CaseInsensitive)
                       || (!info.comPort.isEmpty()
                           && info.comPort.compare(selector, Qt::CaseInsensitive) == 0)) {
                /* A serial device can be picked by its COM port name, too */
                selected = info;
                return 0;
            }
        }
        return -1;
    }

    /* Implicit choice: application mode first, honouring the channel order.
     * Busy devices (held by another program) are only used when the user picks
     * them explicitly, so the upgrade fails with the clear "in use" message. */
    const Ch375DeviceInfo *fallback = nullptr;
    for (const Ch375DeviceInfo &info : devices) {
        if (info.isIap || info.busy)
            continue;
        if (info.viaLibusb() == preferLibusb) {
            selected = info;
            return 0;
        }
        if (!fallback)
            fallback = &info;
    }
    if (fallback) {
        selected = *fallback;
        return 0;
    }

    for (const Ch375DeviceInfo &info : devices) {
        if (!info.busy) {
            selected = info;
            return 0;
        }
    }

    return -1;
}

} // namespace

/**
 * True when the command line mode should be used: any argument on the command
 * line selects it (--cli / --firmware / --list / --help / --version, ...), and
 * without arguments the graphical interface starts.
 */
bool cliRequested(const QStringList &args)
{
    /* Switches that belong to the graphical interface: with one of these the
       program never falls back to the command line mode. */
    static const QStringList guiSwitches = {
        QStringLiteral("--lang"), QStringLiteral("--theme"),
        QStringLiteral("--screenshot"), QStringLiteral("--autoswitch"),
        QStringLiteral("--about")
    };

    if (args.isEmpty())
        return false;

    for (const QString &arg : args) {
        if (arg == QLatin1String("--cli") || arg == QLatin1String("-h")
            || arg == QLatin1String("--help") || arg == QLatin1String("--version")
            || arg == QLatin1String("-l") || arg == QLatin1String("--list")
            || arg == QLatin1String("-f") || arg.startsWith(QLatin1String("--firmware")))
            return true;

        /* Anything else starting with "--" is a command line switch; an unknown
           one is reported as an error instead of silently starting the GUI. */
        if (arg.startsWith(QLatin1String("--"))) {
            bool known = false;
            for (const QString &gui : guiSwitches) {
                if (arg.startsWith(gui)) {
                    known = true;
                    break;
                }
            }
            if (!known)
                return true;
        }
    }

    for (const QString &arg : args) {
        for (const QString &gui : guiSwitches) {
            if (arg.startsWith(gui))
                return false;
        }
    }

    /*
     * Anything else is a command line invocation: an argument the command line
     * mode does not know (a bare file name, for instance) is reported there as
     * an error instead of silently starting the graphical interface.
     */
    return true;
}

/**
 * The calling shell waits for this process: no prompt can show up while the
 * output is written and nothing has to be cleaned up afterwards.
 */
void cliSetShellWaits(bool waits)
{
    shellWaits = waits;
}

/** A command line argument, quoted when it contains spaces */
QString consoleQuote(const QString &text)
{
    if (text.isEmpty())
        return QStringLiteral("\"\"");

    if (!text.contains(QLatin1Char(' ')) && !text.contains(QLatin1Char('\t')))
        return text;

    return QLatin1Char('"') + text + QLatin1Char('"');
}

#ifdef Q_OS_WIN
/**
 * An inheritable copy of a standard handle. Only inheritable handles may be
 * handed to a child process through STARTUPINFO (see CreateProcessW).
 */
HANDLE inheritableHandle(HANDLE source)
{
    HANDLE copy = NULL;

    if (!::DuplicateHandle(::GetCurrentProcess(), source, ::GetCurrentProcess(),
                           &copy, 0, TRUE, DUPLICATE_SAME_ACCESS))
        return NULL;

    return copy;
}

/** Open a console stream with a handle a child process may inherit */
HANDLE openConsoleStream(LPCWSTR name, DWORD access)
{
    SECURITY_ATTRIBUTES security;
    std::memset(&security, 0, sizeof(security));
    security.nLength = sizeof(security);
    security.bInheritHandle = TRUE;

    const HANDLE handle = ::CreateFileW(name, access, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                        &security, OPEN_EXISTING, 0, nullptr);
    return (handle == INVALID_HANDLE_VALUE) ? NULL : handle;
}
#endif /* Q_OS_WIN */

int cliForwardToConsoleApp(const QStringList &args)
{
#ifdef Q_OS_WIN
    const QString program = QDir::toNativeSeparators(
        QCoreApplication::applicationDirPath() + QLatin1Char('/')
        + QString::fromWCharArray(kConsoleAppName));

    if (!QFileInfo::exists(program))
        return -1;   /* not installed next to this program */

    HANDLE input = ::GetStdHandle(STD_INPUT_HANDLE);
    HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE error = ::GetStdHandle(STD_ERROR_HANDLE);

    /*
     * With a redirected output ("> file" or a pipe) those three handles are
     * the redirect and the child has to keep using them. Without one there is
     * no console at all: attach to the one of the calling shell and open its
     * streams, so that the child writes to the same screen.
     */
    HANDLE opened[3] = { NULL, NULL, NULL };

    const bool redirected = (output != NULL && output != INVALID_HANDLE_VALUE);

    if (!redirected) {
        if (!::AttachConsole(ATTACH_PARENT_PROCESS))
            return -1;   /* no console at all: run the command line mode here */

        output = opened[1] = openConsoleStream(L"CONOUT$", GENERIC_READ | GENERIC_WRITE);
        error = opened[2] = openConsoleStream(L"CONOUT$", GENERIC_READ | GENERIC_WRITE);
        input = opened[0] = openConsoleStream(L"CONIN$", GENERIC_READ | GENERIC_WRITE);

        if (!output)
            return -1;
    } else {
        input = opened[0] = inheritableHandle(input);
        output = opened[1] = inheritableHandle(output);
        error = opened[2] = inheritableHandle(error);

        if (!output)
            return -1;
    }

    QString commandLine = consoleQuote(program);
    for (const QString &arg : args)
        commandLine += QLatin1Char(' ') + consoleQuote(arg);

    std::wstring command = commandLine.toStdWString();

    STARTUPINFOW startup;
    std::memset(&startup, 0, sizeof(startup));
    startup.cb = sizeof(startup);
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = (input != INVALID_HANDLE_VALUE) ? input : NULL;
    startup.hStdOutput = (output != INVALID_HANDLE_VALUE) ? output : NULL;
    startup.hStdError = (error != INVALID_HANDLE_VALUE) ? error : NULL;

    PROCESS_INFORMATION process;
    std::memset(&process, 0, sizeof(process));

    const BOOL started = ::CreateProcessW(nullptr, &command[0], nullptr, nullptr, TRUE, 0,
                                          nullptr, nullptr, &startup, &process);

    for (HANDLE handle : opened) {
        if (handle && handle != INVALID_HANDLE_VALUE)
            ::CloseHandle(handle);
    }

    if (!started)
        return -1;

    ::WaitForSingleObject(process.hProcess, INFINITE);

    DWORD code = 0;
    ::GetExitCodeProcess(process.hProcess, &code);
    ::CloseHandle(process.hThread);
    ::CloseHandle(process.hProcess);

    return static_cast<int>(code);
#else
    Q_UNUSED(args);
    return -1;
#endif
}

/* Runs the command line mode, cliRun() only adds the console clean-up */
int cliRunImpl(const QStringList &args);

int cliRun(const QStringList &args)
{
    const int code = cliRunImpl(args);

    /* Draw the prompt below the output, with the cursor behind it */
    finishShellPrompt();
    return code;
}

int cliRunImpl(const QStringList &args)
{
    acquireConsole();

    CliOptions opt;
    QString error;

    if (!parseArgs(args, opt, error)) {
        printError(QStringLiteral("Error: %1").arg(error));
        printUsage(stderr);
        return kExitUsage;
    }

    if (args.isEmpty()) {
        /* Started from a command prompt without any switch: show the usage
           instead of opening the graphical interface. */
        printUsage(stdout);
        return kExitOk;
    }

    if (opt.help) {
        printUsage(stdout);
        return kExitOk;
    }

    if (opt.version) {
        printLine(QStringLiteral("%1 %2")
                      .arg(QCoreApplication::applicationName())
                      .arg(QCoreApplication::applicationVersion()));
        return kExitOk;
    }

    /* Optional log file */
    QFile logFile;
    if (!opt.logFile.isEmpty()) {
        logFile.setFileName(opt.logFile);
        if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            printError(QStringLiteral("Error: cannot open the log file: %1").arg(opt.logFile));
            return kExitUsage;
        }
        logFileHandle = &logFile;
    }

    /* The driver diagnostics are very chatty (one line per CH375 index),
       so they are only printed with --verbose. */
    ch375_set_log_func(opt.verbose ? ch375CliLog : nullptr);

    /* ---------------------------------------------------------------------
     * Device enumeration (also used by --list)
     * --------------------------------------------------------------------- */
    QList<Ch375DeviceInfo> devices;
    int appIndex = -1;
    Ch375DeviceInfo appDevice;
    QString detectError;

    const DeviceMode mode = ch375dev_detect(CH32H417_APP_VID, CH32H417_APP_PID,
                                            opt.iapVid, opt.iapPid,
                                            appIndex, appDevice, devices, detectError);

    if (mode == DeviceMode::NotFound) {
        /* The CH375 driver may be missing while the board is already in IAP
           mode: try the HID channel before giving up. */
        devices = ch375dev_enum_hid_devices(opt.iapVid, opt.iapPid);
        if (!detectError.isEmpty() && !opt.quiet)
            printLine(QStringLiteral("  [warning] %1").arg(detectError));
    }

    if (opt.list) {
        printDeviceList(devices);
        return devices.isEmpty() ? kExitNoDevice : kExitOk;
    }

    /* ---------------------------------------------------------------------
     * Upgrade
     * --------------------------------------------------------------------- */
    if (opt.firmware.isEmpty()) {
        printError(QStringLiteral("Error: no firmware file given (use --firmware <file>)"));
        printUsage(stderr);
        return kExitUsage;
    }

    const QFileInfo fwInfo(opt.firmware);
    if (!fwInfo.exists() || !fwInfo.isFile()) {
        printError(QStringLiteral("Error: firmware file not found: %1").arg(opt.firmware));
        return kExitFirmware;
    }

    /* Parse the firmware up front: a broken file must fail before the device
       is switched into IAP mode. */
    FirmwareImage image;
    QString fwError;
    if (!firmware_load(opt.firmware, opt.binBase, image, fwError)) {
        printError(QStringLiteral("Error: %1").arg(fwError));
        return kExitFirmware;
    }

    Ch375DeviceInfo device;
    if (selectDevice(devices, opt.device, opt.preferLibusb, device) != 0) {
        if (opt.device.isEmpty()) {
            /* A board that is held by another program is not a plain "no
               device" situation: tell the user what blocks the upgrade. */
            for (const Ch375DeviceInfo &info : devices) {
                if (!info.busy)
                    continue;
                printError(QStringLiteral(
                    "Error: the CH32H417 device at USB bus %1 address %2 is in "
                    "use by another program. Close that program and try again.")
                               .arg(info.bus).arg(info.address));
                return kExitNoDevice;
            }
            printError(QStringLiteral("Error: no CH32H417 device found"));
        } else {
            printError(QStringLiteral("Error: no device matches \"%1\"").arg(opt.device));
        }
        printDeviceList(devices);
        return kExitNoDevice;
    }

    if (!opt.quiet) {
        printLine(QStringLiteral("Firmware : %1").arg(fwInfo.absoluteFilePath()));
        printLine(QStringLiteral("  Format : %1").arg(image.fromHex ? "Intel HEX" : "BIN"));
        printLine(QStringLiteral("  Size   : %1 bytes (%2)")
                      .arg(image.data.size())
                      .arg(firmware_format_size(image.data.size())));
        printLine(QStringLiteral("  Range  : 0x%1 - 0x%2")
                      .arg(image.startAddress, 8, 16, QLatin1Char('0'))
                      .arg(image.endAddress, 8, 16, QLatin1Char('0')));
        printLine(QStringLiteral("  Sum    : 0x%1").arg(image.checksum, 8, 16, QLatin1Char('0')));
        printLine(QStringLiteral("Device   : %1").arg(device.description()));
    }

    IapWorker::Config config;
    config.firmwarePath = fwInfo.absoluteFilePath();
    config.binBaseAddress = opt.binBase;
    config.iapVid = opt.iapVid;
    config.iapPid = opt.iapPid;
    config.alreadyInIap = device.isIap;
    config.ch375Index = (!device.isIap && !device.viaLibusb() && !device.viaSerial()) ? device.index : -1;
    config.viaLibusb = !device.isIap && device.viaLibusb();
    config.libusbBus = device.bus;
    config.libusbAddress = device.address;
    config.viaSerial = !device.isIap && device.viaSerial();
    config.serialPort = device.comPort;
    config.deviceBusy = device.busy;
    config.hidWaitSeconds = opt.waitSeconds;

    IapWorker *worker = new IapWorker(config);
    QThread *thread = new QThread;
    worker->moveToThread(thread);

    /* Context object living in this thread: the lambdas below run here, so
       stdout is only touched from one thread. */
    QObject context;

    bool success = false;
    QString resultMessage;
    QString lastStatus;

    QObject::connect(thread, &QThread::started, worker, &IapWorker::run);
    QObject::connect(worker, &IapWorker::logMessage, &context,
                     [&](const QString &message) {
                         if (!opt.quiet)
                             printLine(message);
                     });
    QObject::connect(worker, &IapWorker::progressUpdated, &context,
                     [&](int percent, const QString &status) {
                         /*
                          * The printed progress is the percentage inside the
                          * current step (Programming / Verifying FLASH), which
                          * the worker rounds down to a multiple of 10: printing
                          * it whenever the text changes gives one line every
                          * 10% instead of one line per transferred block. The
                          * number in front of it is the progress of the whole
                          * upgrade.
                          */
                         if (status == lastStatus)
                             return;

                         lastStatus = status;
                         printLine(QStringLiteral("[%1%] %2")
                                       .arg(percent, 3)
                                       .arg(status));
                     });
    QObject::connect(worker, &IapWorker::finished, &context,
                     [&](bool ok, const QString &message) {
                         success = ok;
                         resultMessage = message;
                         thread->quit();
                     });

    QEventLoop loop;
    QObject::connect(thread, &QThread::finished, &loop, &QEventLoop::quit);

    thread->start();
    loop.exec();
    thread->wait();

    delete worker;
    delete thread;

    ch375_set_log_func(nullptr);

    if (success) {
        printLine(QStringLiteral("OK: %1").arg(resultMessage));
        return kExitOk;
    }

    printError(QStringLiteral("FAILED: %1").arg(resultMessage));
    printError(QStringLiteral("Please power-cycle the device (disconnect and reconnect "
                              "the USB cable or the power supply) and try again."));
    return kExitUpgradeFailed;
}
