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
#include "err_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

#include "lib-ttycolor.h"
#include "mem_lib.h"

static char* prg;

void setName(char* name){
    prg = name;
    
}

void die(int val,char* msg,...){
 
    va_list args;
    va_start(args,msg);

    cprintferr(RED,"%s:",prg);
    cvprintferr(RED,msg,args);

    va_end(args);
    
    releaseAll();
    
    exit(val);

    
}

void warn(char* msg,...){
 
    va_list args;
    va_start(args,msg);
    
    cprintferr(YELLOW,"%s:",prg);
    cvprintferr(YELLOW,msg,args);
    
    va_end(args);
}

char* getFileErrMsg(){

	static char* out;
	switch(errno){
		case EACCES:
			out = "can't open %s: access denied\n";
			break;
		case EMFILE:
			out = "can't open %s: too much file already opened\n";
			break;
		case EOVERFLOW:
			out = "can't open %s: file too large\n";
			break;
		case ELOOP:
			out = "can't correctly find %s: there are loops in the path\n";
			break;
		case ENAMETOOLONG:
			out = "can't open %s:a component in the path is too long\n";
			break;
		default:
			out  = "unknown error while opening %s : errno(%d)\n";
	}
	return out;
}

char* getChdirErrMsg(){

	static char* out;
	switch(errno){
		case EACCES:
			out = "can't open %s: access denied\n";
			break;
		case ENOENT:
			out = "can't open %s: a component doesn't name an existing directory\n";
			break;
		case ENOTDIR:
			out = "can't open %s: it's not a directory\n";
			break;
		case ELOOP:
			out = "can't correctly find %s: there are loops in the path\n";
			break;
		case ENAMETOOLONG:
			out = "can't open %s:a component in the path is too long\n";
			break;
		default:
			out  = "unknown error while opening %s : errno(%d)\n";
	}
	return out;
}



