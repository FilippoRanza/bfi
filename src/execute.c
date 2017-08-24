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

#include "execute.h"

#include <stdint.h>
#include <stddef.h>


#include "mem_lib.h"
#include "err_lib.h"


static FILE* input;
static FILE* output;

static int8_t* array;
static int8_t* ptr;
static int offset;



static size_t sz;

void init(FILE* i,FILE *o){
    array = getInitial();
    sz = DEF_SZ;
    
    ptr = array;

    input = i;
    output = o;

}


static int8_t* copy(int8_t* buff,int8_t* src){
    
    while((*buff++ = *src++));
    
    return buff;
    
}


void setArgs(int8_t** args,int c){
    
    int8_t* tmp = array;
    
    for(int i = 0; i < c;i++){
        tmp = copy(tmp,*args++);
    }
    
}

static void printDebug(int8_t* p,int offset){
    printf("\n---DEBUG---\n");
    printf("Value:\n");
    printf("\t%x\n",*p);
    printf("\t%d\n",*p);
    printf("Location:\n");
    printf("\t%d\n",offset);
    printf("----END----\n");
}

int debugger(command* cmd,int mode){

    int c;
    char mem = FALSE;
    
    while(cmd->cmd != END_PRG){
    
        
        switch(cmd->cmd){
            
            case VAL:
                *ptr += cmd->val;
                break;
            case MEM:
                mem = TRUE;
                ptr    += cmd->val;
                offset += cmd->val;
                break;
            case READ:
                c = cmd->val;
                while(c--)
                    *ptr = (int8_t)fgetc(input);
                break;
            case PRINT:
                c = cmd->val;
                while(c--)
                	if(*ptr)
                		fputc(*ptr,output);
                break;
            case JUMP_A:
                if(!*ptr)
                    cmd += cmd->val;
                break;
            case JUMP_B:
                if(*ptr)
                    cmd += cmd->val;
                break;
            case DBG:
                printDebug(ptr,offset);
                if(mode == WAIT_DEBUG){
                	getchar();

                }

                break;
        }
        cmd++; 
       
        if(mem){
            mem = FALSE;
            ptr = check(ptr);
            if(ptr == NULL)
            	return MEM_ERR;
        }

    }
    return OK;
}

int execute(command* cmd){
    
    
    int c;
    char mem = FALSE;
    
    while(cmd->cmd != END_PRG){
    
        switch(cmd->cmd){
            
            case VAL:
                *ptr += cmd->val;
                break;
            case MEM:
                mem = TRUE;
                ptr    += cmd->val;
                break;
            case READ:
                c = cmd->val;
                while(c--)
                	*ptr = (int8_t)fgetc(input);
                break;
            case PRINT:
                c = cmd->val;
                while(c--)
                	if(*ptr)
                		fputc(*ptr,output);
                break;
            case JUMP_A:
                if(!*ptr)
                    cmd += cmd->val;
                break;
            case JUMP_B:
                if(*ptr)
                    cmd += cmd->val;
                break;
        }
        cmd++; 
       
        if(mem){
            mem = FALSE;
            ptr = check(ptr);
            if(ptr == NULL)
            	return MEM_ERR;
        }

    }
    return OK;
}


void resetExec(){

    ptr = array;
    offset = 0;
    clear();

}
