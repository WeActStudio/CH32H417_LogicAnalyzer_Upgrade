/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * Command line interface: headless firmware upgrade (no window is shown).
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef CLI_H
#define CLI_H

#include <QStringList>

/**
 * True when the command line mode should be used. Any argument on the command
 * line selects it (--firmware / --list / --help / --version / --cli, ...);
 * without arguments the graphical interface starts.
 *
 * The only exception are the switches that control the graphical interface
 * itself (--lang / --theme / --screenshot / --autoswitch / --about).
 */
bool cliRequested(const QStringList &args);

/**
 * Run the command line mode (help / version / list / upgrade).
 * @return process exit code (see kCliExitCodes in cli.cpp)
 */
int cliRun(const QStringList &args);

/**
 * Tell the command line mode that the calling shell waits for this process,
 * which is the case for the console companion: no prompt can still show up
 * while the output is written, and nothing has to be cleaned up afterwards.
 */
void cliSetShellWaits(bool waits);

/**
 * Run the console companion ("CH32H417 Logic Analyzer Upgrade CLI.exe") that
 * sits next to this executable and wait for it.
 *
 * A Windows GUI application is never waited for by PowerShell, so the
 * graphical program hands its command line over to the console companion and
 * returns its exit code: the shell then sees the output as it is written, and
 * an output redirected by another program is used by the child as well.
 *
 * @return the exit code of the companion, or -1 when it is not available
 */
int cliForwardToConsoleApp(const QStringList &args);

#endif /* CLI_H */
