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

#define DEF_MODE 0

#include "brainfuck.h"
#include "lib_inter.h"
#include "file_reader.h"
#include "compress.h"
#include "execute.h"
#include "mem_lib.h"
#include "err_lib.h"
#include "lib_files.h"

#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>


#define HOME '~'

char* getHome(){

	char* home = getenv("HOME");
	if(home == NULL){
		home = getpwuid(getuid())->pw_dir;
	}

	return home;
}


char* expandHome(char *path){

	if(!(*path))
		return NULL;

	if(*path == HOME){

		char* home = getHome();
		if(home == NULL){
			warn("Can't get you home: no expansion for ~\n");
			return NULL;
		}

		int hlen = strlen(home);
		int plen = strlen(path);

		int nlen = plen + hlen;

		char* npath = (char*) allocmem(nlen,sizeof(char));
		char* tmp  = npath + hlen;

		//remove leading ~
		path++;

		strcpy(npath,home);
		strcpy(tmp,path);

		return npath;

	}

	return path;

}

void warnJump(int code,int jc){

	char* msg = "";

	if(code == UNOPENED_JUMP){
		msg = "there are %c jumps unopened\n";
	}
	else if(code == UNCLOSED_JUMP){
		msg = "there are %c jumps unclosed\n";
	}

	warn(msg,jc);

}


void warnFile(int code,char* fname){

	char* msg = "";

	if(code == NO_FILE){
		msg = "can't get %s: no suck file\n";
	}
	else if(code == BLCK){
		msg = "%s is a block device\n";
	}
	else if(code == CHR){
		msg = "%s is a character special device\n";
	}
	else if(code == DIR){
		msg = "%s is a directory\n";
	}
	else if(code == FIFO){
		msg = "%s is a FIFO\n";
	}
	else if(code == LNK){
		msg = "%s is a symbolic link\n";
	}
	else if(code == SOCK){
		msg = "%s is a socket\n";
	}
	else if(code == FILE_ERR){
		msg = getFileErrMsg();
	}
	else if(code == NO_CODE){
		msg = "no brainfuck code in %s\n";
	}

	warn(msg,fname,errno);

}

static char* split(char* str){

	while(*str && *str != ' ')
		str++;

	if(*str){
		*str = '\0';
		return ++str;
	}
	return NULL;
}

static char* trim(char* str){
	while(isspace(*str))
		str++;
	return str;
}

static void exe(char* bfc){
    
	int ans;

    if((ans = setCode(bfc,DEBUG_CODE)) != OK){
    	warnJump(ans,getJumps());
    	return;
    }

    command* cmd = getCommand();

    
   // if(args != NULL)
    //	setArgs((int8_t**)&args,1);

    if((ans = debugger(cmd,0)) != OK){
    	warn("Execution killed: Buffer Overflow\n");
    	resetExec();
    }

    release(cmd);
    
}

static void run(char* fname){
    
	int ans;
	char* args = split(fname);

    if((ans = setFile(fname)) != OK){
    	warnFile(ans,fname);
    	return;
    }

    if((ans = setCode(getBuffer(),0)) != OK){
    	warnJump(ans,getJumps());
    	return;
    }

    command* cmd = getCommand();
    clearFiles();
    
    if(args != NULL)
    	setArgs((int8_t**)&args,1);

    if((ans = debugger(cmd,DEBUG_CODE)) != OK){
    	warn("Execution killed: Buffer Overflow\n");
    	resetExec();
    }

    release(cmd);
}


static int  runCommand(char* cmd){

	int out = TRUE;

	char* tail = split(cmd);
	char* ncmd = "";
	char used = FALSE;

	if(tail != NULL){
		tail = trim(tail);
		ncmd = expandHome(tail);
		used = ((ncmd != NULL) && (ncmd != tail));
	}



    if(strcmp(cmd,RUN) == 0){
		if(ncmd != NULL)
			run(ncmd);
		else
			warn("what should I run?\n");
	}
	else  if(strcmp(cmd,EXIT) == 0){
		out = FALSE;
	}
	else  if(strcmp(cmd,CLEAR) == 0){
		resetExec();
	}
	else  if(strcmp(cmd,HELP) == 0){
		printf("bfi - execute brainfuck programs\n");
		printf("this help is for interactive shell:\n");
		printf("\tfor bfi help run bhi -h o man bfi\n");
		printf("Known commands:\n");
		printf("\trun file [args] - run program from file,args are CLI arguments\n");
		printf("\tcl - clears interpreter memory\n");
		printf("\texit - exits bfi shell (equivalent to EOF)\n");
		printf("\thelp - show this help\n");
		printf("\tcd dir - change working directory to dir\n");
		printf("\tpwd - print current working directory\n");
		printf("\tls - list current directory content\n");
		printf("Every other string is consider brainfuck code and execute\n");
	}
	else  if(strcmp(cmd,CHDIR) == 0){
		if(ncmd == NULL)
			warn("in which directory should I go?\n");

		else if(cd(ncmd))
			warn(getChdirErrMsg(),ncmd);
	}
	else  if(strcmp(cmd,PWD) == 0){
		printCWD();
	}
	else  if(strcmp(cmd,LIST) == 0){
		listDir();
	}
	else{
		if(tail != NULL){
			int offset = (tail - cmd -1);
			cmd[offset] = ' ';
		}
		exe(cmd);
	}

    if(used)
    	release(ncmd);

    return out;
}


void startConsole(){

    char work = TRUE;
    while(work){

        char* cmd = readline(PROMPT);
        if(cmd != NULL){
        	void* p = cmd;
        	cmd = trim(cmd);
        	if(*cmd){
				add_history(cmd);
				work = runCommand(cmd);
        	}
            free(p);
        }
        else{
            work = FALSE;
        }

        
    }
    printf("\nGoodbye\n");
}
