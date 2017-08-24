/*
 *   bfi - execute brainfuck programs
 *   Copyright (C) 2017 Filippo Ranza
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIB_INTER_H
#define LIB_INTER_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "brainfuck.h"


#define PROMPT "=%"

//Interactive Shell commands
#define RUN   "run"
#define EXIT  "exit"
#define CLEAR "cl"
#define HELP  "help"

#define CHDIR "cd"
#define PWD   "pwd"
#define LIST  "ls"

//Interactive interpreter commands
#define RUN_C 	1
#define EXIT_C	2
#define CLEAR_C 3
#define HELP_C 	4

#define CHDIR_C 6
#define PWD_C 	7
#define LIST_C 	8

void startConsole();

#endif
