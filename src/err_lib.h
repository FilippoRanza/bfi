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
#ifndef GEN_UTILS_H
#define GEN_UTILS_H

#include <stddef.h>


#define EXIT_STAT_ERR 1
#define EXIT_WRONG_FILE 2
#define EXIT_OPEN_ERR 3
#define MEM_ERROR    4
#define SETUP_ERR    5
#define BUFF_ERR     6


#define NO_CODE_ERR 7
#define JUMP_NOT_CLOSED 8
#define JUMP_NOT_OPENED 9
#define WRITE_TO_EXISTING_FILE 10



#define UNKNOW_OPT 10
#define NO_IN_PRG  11

void setName(char* name);

void die(int val,char* msg,...);
void warn(char* msg,...);

char* getFileErrMsg();
char* getChdirErrMsg();


#endif
