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

#include "lib_args.h"
#include "err_lib.h"

#define READ_STATE 1
#define WRITE_STATE 2


static args a;
static char wrong;

static int state;

static int isopt(char* arg){
    return *arg == '-';
}

int parseIOpt(char* arg){

    arg++;
    char c;
    
    while((c = *arg++)){
        switch(c){
            case DEBUG:
                a.debug = SIMPLE_DEBUG;
                break;
            case DEBUG_WAIT:
                a.debug = WAIT_DEBUG;
                break;
            case WARNING_ALL:
                a.warnlv = WARN_ALL;
                break;
            case INTERACTIVE:
                a.interactive = TRUE;
                break;
            case IGNORE:
                a.ignore = TRUE;
                break;
            case EXECUTE:
                a.mode = EXEC_MODE;
                break;
            case READ_F:
            	state = READ_STATE;
            	break;
            case WRITE_F:
            	state = WRITE_STATE;
				break;
            case HELP_A:
            	a.help = TRUE;
            	break;
            default:
            	wrong = c;
                return UNKNOWN_ARG;
            	break;
        }
    }
    return OK;
}


int pass(int argc,char** argv){
    
    setName(*argv++);
    argc--;
    
    a.exe = NULL;
    a.prg = NULL;
    
    a.ifile = NULL;
    a.ofile = NULL;

    a.mode = FILE_MODE;
    a.help = FALSE;
    
    char stop = FALSE;
    
    state = 0;
    while(!stop && argc--){
        
        char* arg = *argv++;

        if(isopt(arg) && (!state)){
          int ans = parseIOpt(arg);
          if(ans != OK)
        	  return ans;
        }
        else if(state == READ_STATE){
        	a.ifile = arg;
        	state = 0;
        }
        else if(state == WRITE_STATE){
        	a.ofile = arg;
        	state = 0;
        }
        else{
            if(a.mode == FILE_MODE)
                a.prg = arg;
            else
                a.exe = arg;
            stop = TRUE;
        }
    }
    
    a.pargc = argc;
    a.pargv = argv;
    
    return OK;
}

int hasPrg(){

    if(a.mode == FILE_MODE && a.prg == NULL){
    	return NO_PRG;
    }
    else if(a.mode == EXEC_MODE && a.exe == NULL){
    	return NO_EXE;
    }
    else if(a.interactive && a.exe == NULL && a.prg == NULL){
    	return NO_PRG;
    }
    return OK;
}

char getWrongOption(){
	return wrong;
}

args* getArgs(){
    return &a;
}
