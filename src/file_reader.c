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
#include "file_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#include "brainfuck.h"
#include "warn_lib.h"
#include "err_lib.h"
#include "mem_lib.h"

#define STAT_FAIL -1

#define READ_M 1
#define WRITE_M 2


static char* _in;
static uint8_t comment;

static FILE* fp;

static FILE* ifp;
static FILE* ofp;

void setupFiles(){
	ifp = stdin;
	ofp = stdout;
}

static int getFType(mode_t m){

	int out = OK;
    if(!S_ISREG(m)){
        
        if(S_ISBLK(m)){
        	out =  BLCK;
        }
        else if(S_ISCHR(m)){
        	out =  CHR;
        }
        else if(S_ISDIR(m)){
        	out =  DIR;
        }
        else if(S_ISFIFO(m)){
        	out =  FIFO;
        }
        else if(S_ISLNK(m)){
        	out =  LNK;
        }
        else if(S_ISSOCK(m)){
        	out =  SOCK;
        }
        
    }

    return out;

}


static int openRead(char* fname){
    struct stat buff;

    if(stat(fname,&buff) == STAT_FAIL){
    	return NO_FILE;
    }

    mode_t m = buff.st_mode;

    int ans;
    if((ans = getFType(m)) != OK)
    	return ans;


    ifp = fopen(fname,"r");

    if(ifp == NULL){
    	return FILE_ERR;
    }

    return OK;
}

static int openWrite(char* fname){
    struct stat buff;

    if(stat(fname,&buff) == STAT_FAIL){

    	ofp = fopen(fname,"w");

        if(ofp == NULL){
        	return FILE_ERR;
        }

    	return OK;
    }

    mode_t m = buff.st_mode;

    int ans;
    if((ans = getFType(m)) != OK)
    	return ans;

    return FILE_EXISTS;
}


static int openStore(char* fname){

    struct stat buff;

    if(stat(fname,&buff) == STAT_FAIL){
    	return NO_FILE;
    }
    
    mode_t m = buff.st_mode;

    int ans;
    if((ans = getFType(m)) != OK)
    	return ans;


    fp = fopen(fname,"r");
    
    if(fp == NULL){
    	return FILE_ERR;
    }
    
	size_t sz = (buff.st_size + 1);
	_in = (char*) allocmem(sz,sizeof(uint8_t));


    return OK;

}


static void readFile(){
    
    int in;

    char* tmp = _in;
        
    while((in = fgetc(fp)) != EOF)
        *tmp++ = (char) in;

    *tmp = '\0';

}


void clearFiles(){
    
    if(_in != NULL){
        release(_in);
        _in = NULL;
        fclose(fp);

    }
    
    comment = FALSE;
    
}



int  setFile(char* fname){
    
    _in = NULL;
    
    int out = openStore(fname);
    if(out != OK)
    	return out;
    
    readFile();

    return OK;
}


char* getBuffer(){
    return _in;
}


int setInputFile(char* fname){
	return *fname == '-' ?  OK : openRead(fname);
}

FILE* getInputFP(){
	return ifp;
}



int setOutputFile(char* fname){
	return *fname == '-' ?  OK : openWrite(fname);
}

FILE* getOutputFP(){
	return ofp;
}


