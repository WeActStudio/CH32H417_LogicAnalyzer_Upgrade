/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * Command line interface: headless firmware upgrade (no window is shown).
 *
 * The mode is used when the command line asks for it, and also when the
 * program is started from a command prompt: a window popping out of a shell
 * command is never what the user asked for.
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef CLI_H
#define CLI_H

#include <QStringList>

/**
 * True when the command line mode should be used: the command line carries one
 * of --cli / --firmware / --list / --help / --version, or the program was
 * started from a command prompt (cmd / PowerShell / ...).
 */
bool cliRequested(const QStringList &args);

/**
 * Run the command line mode (help / version / list / upgrade).
 * @return process exit code (see kCliExitCodes in cli.cpp)
 */
int cliRun(const QStringList &args);

#endif /* CLI_H */
