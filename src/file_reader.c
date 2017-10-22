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

#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "err_lib.h"
#include "mem_lib.h"

#define STAT_FAIL -1

#define IN_PLACE 1
#define STANDARD 0

typedef struct {
    char* fname;
    ino_t inode;
    size_t size;
    FILE* fp;

}file;

typedef struct{
    file f;
    int stat;
}open_stat;


static char* _in;



static open_stat* prg;
static open_stat* in;
static open_stat* out;

static int mode;



//find file type
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

//open a file with error checking
static open_stat* openFile(char* fname,int mode){

    int out = OK;

    struct stat buff;
    int ans = stat(fname,&buff);
    if(mode == O_WRONLY){
        if(ans != STAT_FAIL) {
            out = FILE_EXISTS;
        }
    }
    else{
        if(ans == STAT_FAIL) {
            out = NO_FILE;
        }
    }

    mode_t  m = buff.st_mode;
    if((ans = getFType(m)) != OK)
        out = ans;

    int openMode = (mode == O_RDONLY) ? O_RDONLY : (O_WRONLY | O_CREAT | O_CREAT);
    int fd = open(fname, openMode,DEFFILEMODE);
    if(fd == -1 )
        die(43,fname);

    FILE* fp = (mode == O_WRONLY) ? fdopen(fd,"w") : fdopen(fd,"r");
    if(fp == NULL)
        out = FILE_ERR;

    open_stat* os = (open_stat*) allocmem(1, sizeof(open_stat));

    os->f.fname = fname;
    os->f.inode = buff.st_ino;
    os->f.fp    = fp;
    os->f.size  = (size_t) buff.st_size;

    os->stat = out;
    return os;
}

//functions to read and buffer program file.
/*
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
*/

static void readFile(){
    int in;
    char* tmp = _in;

    while((in = fgetc(prg->f.fp)) != EOF)
        *tmp++ = (char) in;

    *tmp = '\0';
}

int  setFile(char* fname){

    _in = NULL;

    prg = openFile(fname,O_RDONLY);
    if(prg->stat != OK)
        return prg->stat;

    size_t sz = (prg->f.size + 1);
    _in = (char*) allocmem(sz,sizeof(uint8_t));

    readFile();
    return OK;
}

char* getBuffer(){
    return _in;
}

void clearPrgFile(){
    
    if(_in != NULL){
        release(_in);
        _in = NULL;
        fclose(prg->f.fp);
        release(prg);
    }
}
//end read and buffer functions

//input and output functions
static int inplace(files* f){

    char* tmp = tempnam(".","bfi_inplace");
    if(tmp == NULL)
        die(212,"");

    in = openFile(f->ifile,O_RDONLY);
    if(in->stat != OK)
        return in->stat;

    out = openFile(tmp,O_WRONLY);
    if(out->stat != OK)
        return out->stat;

    return OK;
}

static int standard(files* f){

    if(f->ifile != NULL){
        in = openFile(f->ifile,O_RDONLY);
        if(in->stat != OK)
            return in->stat;
    }

    if(f->ofile != NULL){
        out = openFile(f->ofile,O_WRONLY);
        if(out->stat != OK)
            return out->stat;
    }

    return OK;
}

int setIOFiles(files* f){

    int out;
    mode = f->mode;
    if(mode)
        out = inplace(f);
    else
        out = standard(f);

    return out;

}

FILE* getInputFP(){
    return in == NULL ? stdin :  in->f.fp;
}

FILE* getOutputFP(){
	return out == NULL ? stdout : out->f.fp;
}

int closeIOFiles(){

    int ans = 0;

    if(in != NULL)
        fclose(in->f.fp);

    if(out != NULL)
        fclose(out->f.fp);

    if(mode == IN_PLACE)
        ans = rename(out->f.fname,in->f.fname);

    return ans == 0;
}
//end input and output functions

