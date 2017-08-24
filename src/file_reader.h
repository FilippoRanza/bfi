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
#ifndef FILE_READER_H
#define FILE_READER_H


#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include "brainfuck.h"

#define OK   0
#define BLCK -1
#define CHR  -2
#define DIR  -3
#define FIFO -4
#define LNK  -5
#define SOCK -6
#define NO_FILE -7
#define FILE_ERR -8
#define NO_CODE  -9
#define FILE_EXISTS -10


void setupFiles();

int setFile(char* fname);

int setInputFile(char* fname);
FILE* getInputFP();

int setOutputFile(char* fname);
FILE* getOutputFP();

char* getBuffer();

void clearFiles();

#endif
