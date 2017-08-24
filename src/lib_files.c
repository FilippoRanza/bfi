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

#include "lib_files.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include "lib-ttycolor.h"
#include "err_lib.h"

#define CWD "."
#define DEF_EXT ".bf"

#define DEF_SPACE "  "
#define DEF_LEN 2


static int endsWith(char* str,char* tail){

	char* endS = str;
	while(*endS)
		endS++;

	char*endT = tail;
	while(*endT)
		endT++;

	while(endS >= str && endT >= tail && *endS == *endT){
		endS--;
		endT--;
	}

	return endT < tail;

}

int listDir(){

	int cols = atoi(getenv("COLUMNS"));
	int used = 0;

	DIR* cpd = opendir(CWD);
	if(cpd ==  NULL)
		warn("Can't open Current Directory\n");
	struct dirent* entry;


	while((entry = readdir(cpd)) != NULL){

		int len = strlen(entry->d_name) + DEF_LEN;

		if((len + used) >= cols){
			putchar('\n');
			used = len;
		}
		else{
			used += len;
		}


		if(entry->d_type == DT_DIR){
			cprintf(BLUE,"%s%s",entry->d_name,DEF_SPACE);
		}
		else if(endsWith(entry->d_name,DEF_EXT)){
			cprintf(PURPLE,"%s%s",entry->d_name,DEF_SPACE);
		}
		else{
			printf("%s%s",entry->d_name,DEF_SPACE);
		}

	}
	putchar('\n');

	return 0;

}

int printCWD(){

	char* dir = getcwd(NULL,0);
	printf("%s\n",dir);
	free(dir);

	return 0;

}

int cd(char *next){
	if(chdir(next) == -1)
		return errno;
	return 0;
}







