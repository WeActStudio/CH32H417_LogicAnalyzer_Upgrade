/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * Entry point of the console companion
 * ("CH32H417 Logic Analyzer Upgrade CLI.exe").
 *
 * Windows console applications are the only ones a shell really waits for:
 * cmd and PowerShell print their next prompt only after this process is gone,
 * any other program can redirect its output, and the prompt the user sees at
 * the end is the one the shell prints itself. None of that is possible with
 * the graphical program, which is a Windows GUI application: PowerShell does
 * not wait for those and they have no console of their own.
 *
 * The graphical program forwards its command line to this one (see
 * cliForwardToConsoleApp()), so both entry points behave the same.
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <QCoreApplication>

#include "cli.h"
#include "libusbdev.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCoreApplication::setApplicationName("CH32H417 Logic Analyzer Upgrade");
    QCoreApplication::setApplicationVersion("1.0.0");
    /* Company behind the settings path */
    QCoreApplication::setOrganizationName("WeActStudio");

    /*
     * The shell waits for this process, so it cannot print a prompt while the
     * output is written and there is nothing to clean up on the console
     * afterwards (see startOnFreshLine() / finishShellPrompt()).
     */
    cliSetShellWaits(true);

    QStringList args;
    for (int i = 1; i < argc; ++i)
        args << QString::fromLocal8Bit(argv[i]);

    /*
     * Without arguments the graphical program is the one to start (this one
     * prints the usage and returns 0).
     */
    const int code = cliRun(args);

    /* Close the libusb session before the process ends */
    libusbdev_cleanup();

    return code;
}
