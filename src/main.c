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
#include <errno.h>

#include "file_reader.h"
#include "mem_lib.h"
#include "brainfuck.h"
#include "err_lib.h"
#include "compress.h"
#include "execute.h"
#include "lib_args.h"
#include "warn_lib.h"
#include "lib_inter.h"
#include "help.h"

void dieJump(int code,int jc){

	char* msg = "";
	int err   = 0;

	if(code == UNOPENED_JUMP){
		msg = "there are %c jumps unopened\n";
		err = JUMP_NOT_OPENED;
	}
	else if(code == UNCLOSED_JUMP){
		msg = "there are %c jumps unclosed\n";
		err = JUMP_NOT_CLOSED;
	}

	die(err,msg,jc);

}


void dieFile(int code,char* fname){

	char* msg = "";
	int err   = 0;

	if(code == NO_FILE){
		err = EXIT_STAT_ERR;
		msg = "can't get %s: no suck file\n";
	}
	else if(code == BLCK){
		err = EXIT_WRONG_FILE;
		msg = "%s is a block device\n";
	}
	else if(code == CHR){
		err = EXIT_WRONG_FILE;
		msg = "%s is a character special device\n";
	}
	else if(code == DIR){
		err = EXIT_WRONG_FILE;
		msg = "%s is a directory\n";
	}
	else if(code == FIFO){
		err = EXIT_WRONG_FILE;
		msg = "%s is a FIFO\n";
	}
	else if(code == LNK){
		err = EXIT_WRONG_FILE;
		msg = "%s is a symbolic link\n";
	}
	else if(code == SOCK){
		err = EXIT_WRONG_FILE;
		msg = "%s is a socket\n";
	}
	else if(code == FILE_ERR){
		err = EXIT_OPEN_ERR;
		msg = getFileErrMsg();
	}
	else if(code == NO_CODE){
		err = NO_CODE_ERR;
		msg = "no brainfuck code in %s\n";
	}
	else if(code == FILE_EXISTS){
		err = WRITE_TO_EXISTING_FILE;
		msg = "%s already exists,I won't overwrite it, exit not\n";
	}

	die(err,msg,fname,errno);

}


int main(int argc,char** argv){
 
	int ans;

    if(( ans = pass(argc,argv)) != OK){
    	die(UNKNOW_OPT,"Unknown option:%c\n",getWrongOption());
    }


    args* a = getArgs(); 

    if(a->help){
    	printf("%s\n",help);
    	exit(0);
    }

    setupFiles();

    if(a->ifile != NULL){
    	if((ans = setInputFile(a->ifile)) != OK){
    		dieFile(ans,a->ifile);
    	}
    }
    if(a->ofile != NULL){
    	if((ans = setOutputFile(a->ofile)) != OK){
    		dieFile(ans,a->ofile);
    	}
    }



    int mode = 0;
    if(a->warnlv)
        mode |= WARNING_CODE;
    if(a->debug)
        mode |= DEBUG_CODE;

    initialize();
    init(getInputFP(),getOutputFP());


    char done = FALSE;
    if((ans = hasPrg()) == OK){

        command* cmd;
        if(a->mode == FILE_MODE){
            if((ans = setFile(a->prg)) != OK){
            	dieFile(ans,a->prg);
            }
            if((ans = setCode(getBuffer(),mode))!= OK){
            	dieJump(ans,getJumps());
            }

            clearFiles();
        }
        else{
            if((ans = setCode(a->exe,mode)) != OK){
            	dieJump(ans,getJumps());
            }
        }

        cmd = getCommand();
        
        if(a->warnlv)
            checkExec(cmd);
        
        showWarn();
        
        
        if(!a->ignore)
            setArgs((int8_t**)a->pargv,a->pargc);
        
        if(a->debug){
        	 if((ans = debugger(cmd,a->debug)) != OK){
        		 die(BUFF_ERR,"Execution killed: Buffer Overflow\n");
        	 }
        }
        else{
        	if((ans = execute(cmd)) != OK){
        		die(BUFF_ERR,"Execution killed: Buffer Overflow\n");
        	}
        }

    }
	else if(ans == NO_EXE){
		die(NO_IN_PRG,"No code specified for -e\n");
	}
    else{
    	startConsole();
    	done = TRUE;
    }

    if(a->interactive && (!done)){
        startConsole();
    }

    releaseAll();

    return EXIT_SUCCESS;
    
}
