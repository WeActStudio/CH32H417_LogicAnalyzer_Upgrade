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

    QString firmware;
    QString device;
    QString logFile;

    quint32 binBase = 0x08006000;
    quint16 iapVid = CH32H417_IAP_VID;
    quint16 iapPid = CH32H417_IAP_PID;
    int waitSeconds = 15;
};

QFile *logFileHandle = nullptr;

/*
 * Set when the program attached to the console of the calling shell (i.e. the
 * output was not redirected) and reset once the shell prompt has been
 * refreshed at the end of the run.
 */
bool consoleAttached = false;

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

/** Shells a user normally starts this program from */
bool isShellProcess(const QString &name)
{
    static const QStringList shells = {
        QStringLiteral("cmd.exe"), QStringLiteral("powershell.exe"),
        QStringLiteral("pwsh.exe"), QStringLiteral("conhost.exe"),
        QStringLiteral("openconsole.exe"), QStringLiteral("windowsterminal.exe"),
        QStringLiteral("wt.exe"), QStringLiteral("bash.exe"),
        QStringLiteral("sh.exe"), QStringLiteral("zsh.exe")
    };
    return shells.contains(name, Qt::CaseInsensitive);
}

/**
 * Shells that do not wait for a Windows GUI application: they print the next
 * prompt while the program is still running, so the output ends up behind the
 * prompt and the prompt is only redrawn after the user presses Enter.
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
 * True when the program was started from a command prompt. In that case the
 * command line mode is used even without any switch: a window popping out of
 * a shell command is never what the user asked for.
 */
bool startedFromShell()
{
#ifdef Q_OS_WIN
    const QString parent = parentProcessName();
    return !parent.isEmpty() && isShellProcess(parent);
#else
    return false;
#endif
}

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
        else
            consoleAttached = true;

        std::freopen("CONOUT$", "w", stdout);
        std::freopen("CONOUT$", "w", stderr);
        std::freopen("CONIN$", "r", stdin);
    }
#endif
    setvbuf(stdout, nullptr, _IONBF, 0);
    setvbuf(stderr, nullptr, _IONBF, 0);
}

/**
 * Make the calling shell draw its prompt again.
 *
 * PowerShell (unlike cmd.exe) does not wait for a Windows GUI application: it
 * prints the next prompt immediately, so the output of the attached program
 * ends up behind that prompt and the prompt only reappears after the user
 * presses Enter. Posting a single Return key event to the console input buffer
 * does that key press, so the prompt shows up right away.
 */
void refreshShellPrompt()
{
    if (!consoleAttached)
        return;
    consoleAttached = false;

#ifdef Q_OS_WIN
    if (!isNonWaitingShell(parentProcessName()))
        return;

    HANDLE input = ::CreateFileW(L"CONIN$", GENERIC_READ | GENERIC_WRITE,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                                 OPEN_EXISTING, 0, nullptr);
    if (input == INVALID_HANDLE_VALUE)
        return;

    INPUT_RECORD events[2];
    std::memset(events, 0, sizeof(events));

    /* Return key, pressed and released */
    for (int i = 0; i < 2; ++i) {
        events[i].EventType = KEY_EVENT;
        events[i].Event.KeyEvent.bKeyDown = (i == 0);
        events[i].Event.KeyEvent.wRepeatCount = 1;
        events[i].Event.KeyEvent.wVirtualKeyCode = VK_RETURN;
        events[i].Event.KeyEvent.wVirtualScanCode = 0x1C;
        events[i].Event.KeyEvent.uChar.UnicodeChar = L'\r';
    }

    DWORD written = 0;
    ::WriteConsoleInputW(input, events, 2, &written);
    ::CloseHandle(input);
#endif
}

void printLine(const QString &text)
{
    std::fputs(qPrintable(text), stdout);
    std::fputc('\n', stdout);

    if (logFileHandle)
        logFileHandle->write((text + QLatin1Char('\n')).toUtf8());
}

void printError(const QString &text)
{
    std::fputs(qPrintable(text), stderr);
    std::fputc('\n', stderr);

    if (logFileHandle)
        logFileHandle->write((text + QLatin1Char('\n')).toUtf8());
}

void printUsage(FILE *stream)
{
    /*
     * The leading empty line keeps the banner clear of the shell prompt: a
     * Windows GUI application attaches to the console of the calling shell
     * after that shell already printed its own text.
     */
    const QString usage = QStringLiteral(
        "\n"
        "CH32H417 Logic Analyzer Firmware Upgrade Tool %1\n"
        "\n"
        "Usage:\n"
        "  \"CH32H417 Logic Analyzer Upgrade\" --firmware <file> [options]\n"
        "  \"CH32H417 Logic Analyzer Upgrade\" --list\n"
        "  \"CH32H417 Logic Analyzer Upgrade\" --help | --version\n"
        "\n"
        "Upgrade options:\n"
        "  -f, --firmware <path>    Firmware file (.hex or .bin), required for upgrading\n"
        "  -d, --device <selector>  CH375 device index (0..15) or USB serial number prefix\n"
        "  -b, --base <hex>         Base address for .bin files (default 08006000)\n"
        "      --iap-vid <hex>      VID in IAP (HID) mode (default 1A86)\n"
        "      --iap-pid <hex>      PID in IAP (HID) mode (default FE17)\n"
        "  -w, --wait <seconds>     Seconds to wait for the IAP device (default 15)\n"
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
        "      command prompt it stays in this command line mode.\n")
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
 * Pick the device to upgrade: an explicit index / serial number wins,
 * otherwise the first application mode device, otherwise a device already in
 * IAP mode.
 */
int selectDevice(const QList<Ch375DeviceInfo> &devices, const QString &selector,
                 Ch375DeviceInfo &selected)
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
            } else if (info.serial.startsWith(selector, Qt::CaseInsensitive)) {
                selected = info;
                return 0;
            }
        }
        return -1;
    }

    for (const Ch375DeviceInfo &info : devices) {
        if (!info.isIap) {
            selected = info;
            return 0;
        }
    }
    for (const Ch375DeviceInfo &info : devices) {
        selected = info;
        return 0;
    }

    return -1;
}

} // namespace

/**
 * True when the command line mode should be used: either because a command
 * line switch asks for it (--cli / --firmware / --list / --help / --version)
 * or because the program was started from a command prompt, where a window
 * is not what the user expects.
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

    return startedFromShell();
}

/* Runs the command line mode, cliRun() only adds the console clean-up */
int cliRunImpl(const QStringList &args);

int cliRun(const QStringList &args)
{
    const int code = cliRunImpl(args);

    /* A GUI application attaches to the console of the calling shell; give
       that shell the key press it needs to show its prompt again. */
    refreshShellPrompt();
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
    QString detectError;

    const DeviceMode mode = ch375dev_detect(CH32H417_APP_VID, CH32H417_APP_PID,
                                            opt.iapVid, opt.iapPid,
                                            appIndex, devices, detectError);

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
    if (selectDevice(devices, opt.device, device) != 0) {
        if (opt.device.isEmpty())
            printError(QStringLiteral("Error: no CH32H417 device found"));
        else
            printError(QStringLiteral("Error: no device matches \"%1\"").arg(opt.device));
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
    config.ch375Index = device.isIap ? -1 : device.index;
    config.hidWaitSeconds = opt.waitSeconds;

    IapWorker *worker = new IapWorker(config);
    QThread *thread = new QThread;
    worker->moveToThread(thread);

    /* Context object living in this thread: the lambdas below run here, so
       stdout is only touched from one thread. */
    QObject context;

    bool success = false;
    QString resultMessage;
    int lastPercent = -1;
    QString lastStatus;

    QObject::connect(thread, &QThread::started, worker, &IapWorker::run);
    QObject::connect(worker, &IapWorker::logMessage, &context,
                     [&](const QString &message) {
                         if (!opt.quiet)
                             printLine(message);
                     });
    QObject::connect(worker, &IapWorker::progressUpdated, &context,
                     [&](int percent, const QString &status) {
                         const bool changed = (status != lastStatus)
                                              || (percent - lastPercent >= 10)
                                              || percent >= 100;
                         if (changed) {
                             lastPercent = percent;
                             lastStatus = status;
                             printLine(QStringLiteral("[%1%] %2")
                                           .arg(percent, 3)
                                           .arg(status));
                         }
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
