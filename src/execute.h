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
#ifndef EXECUTE_H
#define EXECUTE_H

#include "brainfuck.h"
#include "lib_args.h"

#include <stdio.h>

#define DEF_SZ 1000
#define MAX_SZ 1000000

#define MEM_ERR -1
#define OK 0


void init(FILE* i,FILE *o);
void setArgs(int8_t** args,int c);

int debugger(command* cmd,int mode);
int execute(command* cmd);

void resetExec();

#endif
