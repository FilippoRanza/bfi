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
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


#include "lib-ttycolor.h"


#define FOREGROUND 1
#define BACKGROUND 0
#define COLOR_LOCATION 6

// extern char setter[];
// extern char resetter[];




static char fgSetter[]   = { 27, 91, 48, 49, 59, 51, 49, 109, 27, 91, 75, 0};
static char bgSetter[]   = { 27, 91, 48, 49, 59, 52, 49, 109, 27, 91, 75, 0};
static char resetter[]   = { 27, 91, 109, 27, 91, 75, 0};

/*
 * Inner Functions:
 *      perform color setting and resetting to a general file pointer
 */
static void _printStr(char* str,FILE* fp){
    
    char c;
    while((c = *str++))
        fputc(c,fp );
    
}

static void _resetStream(FILE* fp){
    _printStr(resetter,fp);
}

static void _setColor(COLOR c,int i,FILE* fp){
    
    if(i){
        fgSetter[COLOR_LOCATION] = (char) c;
        _printStr(fgSetter,fp);
    }        
    else{
        bgSetter[COLOR_LOCATION] = (char) c;
        _printStr(bgSetter,fp);
    }
        
    
    
}

static void _printColorStream(char *fmt,va_list arg,COLOR c,FILE* fp){
    
    _setColor(c,FOREGROUND,fp);
        
    vfprintf(fp,fmt,arg);
    
    _resetStream(fp);
    
}



/*
 * Interface Function:
 *      functions used by the user: designed to be easy and clear
 */

/*
 * vprintf on stdout and stderr
 */
void cvprintferr(COLOR c,char *fmt,va_list args){
    _printColorStream(fmt,args,c,stderr);
}


void cvprintf(COLOR c,char* fmt,va_list args){
   _printColorStream(fmt,args,c,stdout); 
}



/*
 * printf on stdout and stderr
 */
void cprintf(COLOR c,char* fmt,...){
    
     va_list args;
     va_start(args,fmt);
     
     _printColorStream(fmt,args,c,stdout);
     
     va_end(args);
    
}

void cprintferr(COLOR c,char* fmt,...){
    
     va_list args;
     va_start(args,fmt);
     
     _printColorStream(fmt,args,c,stderr);
     
     va_end(args);
          
}

/*
 * Set color functions
 */
void setFG(COLOR c){
    _setColor(c,FOREGROUND,stdout);
}

void setBG(COLOR c){
    _setColor(c,BACKGROUND,stdout);
}

void setFGerr(COLOR c){
    _setColor(c,FOREGROUND,stderr);
}

void setBGerr(COLOR c){
    _setColor(c,BACKGROUND,stderr); 
}


/*
 * Reset functions 
 */
void reset(){
    _resetStream(stdout);
}


void resetErr(){
    _resetStream(stderr);
}



