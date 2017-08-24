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
#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdint.h>

#include "brainfuck.h"
#include "err_lib.h"

#define OK 0
#define UNOPENED_JUMP -1
#define UNCLOSED_JUMP -2

#define WARNING_CODE 1
#define DEBUG_CODE   2


int setCode(char* in,int mode);
int getJumps();
command* getCommand();


#endif
