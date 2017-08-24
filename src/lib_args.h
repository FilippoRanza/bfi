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
#ifndef LIB_ARGS_H
#define LIB_ARGS_H

#include "brainfuck.h"

//known cli arguments

#define EXECUTE     'e'
#define DEBUG       'd'
#define DEBUG_WAIT  'D'
#define WARNING_ALL 'W'
#define INTERACTIVE 'i'
#define IGNORE      'I'
#define READ_F		'r'
#define WRITE_F 	'w'
#define HELP_A		'h'

#define FILE_MODE 1
#define EXEC_MODE 2

#define WARN     1
#define WARN_ALL 2

#define SIMPLE_DEBUG 1
#define WAIT_DEBUG   2

#define OK			 0
#define UNKNOWN_ARG -1
#define NO_PRG	-2
#define NO_EXE  -3

typedef struct{
    
    char* prg;
    
    char warnlv;
    char debug;
    char ignore;
    char interactive;
    
    char* exe; 
    
    int pargc;
    char** pargv;
    
    char* ifile;
    char* ofile;

    char mode;
    char help;
    

} args;

int pass(int argc,char** argv);
int hasPrg();

char getWrongOption();

args* getArgs();

#endif
