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


#include <stddef.h>
#include <stdint.h>
#include <ctype.h>

#include "brainfuck.h"
#include "compress.h"
#include "err_lib.h"
#include "mem_lib.h"
#include "warn_lib.h"

#define REVERSE -1

static command* cmds;
static int errors;
static char comment;

static uint8_t convert(uint8_t c){
    
	//out will be always initialized
	//by switch,however it is initialized now
	//suppress the warnings
    uint8_t out = 0;
    switch(c){
        
        case ADD_C:
        case SUB_C:
            out = VAL;
            break;
        
        case PTR_I_C:
        case PTR_D_C:
            out = MEM;
            break;
            
        case PRINT_C:
            out = PRINT;
            break;
            
        case READ_C:
            out = READ;
            break;
            
        case JUMP_A_C:
            out = JUMP_A;
            break;
            
        case JUMP_B_C:
            out = JUMP_B;
            break;
        
        case DBG_C:
            out = DBG;
            break;
    }

    return out;
    
}

static long count(char* in){
    
    size_t out = 0;
    char* tmp = in;
    uint8_t prev = NONE;
    uint8_t c;
    
    int count = 0;
    
    while(*tmp){
        
        c = convert(*tmp++);
        
        if(c != prev) 
            out++;
        
        if(c == JUMP_A){
            prev = NONE;
            count++;
        }
        else if(c == JUMP_B){
            prev = NONE;
            count--;
        }
        else{
            prev = c;
        }
        
    }
    
    //for end program
    out++;
    
    if(count > 0){
    	errors = count;
    	return UNCLOSED_JUMP;
    }
    else if(count < 0){
    	errors = -count;
    	return UNOPENED_JUMP;
    }

    
    return out;
    
}

static void resolveJumps(command* cmd){
    
    int c = 0;
    while(cmd->cmd != END_PRG){
        
        if(cmd->cmd == JUMP_A){
            
            c++;
            command* tmp = cmd + 1;
            
            while(c){
                
                if(tmp->cmd == JUMP_A)
                    c++;
                else if(tmp->cmd == JUMP_B)
                    c--;
        
                tmp++;
            }
    
            tmp--;
            int32_t a = tmp - cmd; 
            
            cmd->val =  a;
            tmp->val = -a;
        }

        cmd++;
    }
    
}

static size_t tokenizer(char* code,uint8_t* out,int32_t* val,size_t* offset){
    
    char* tmp = code;
    *out = convert(*tmp);
    *val = 0;
    
    while(*tmp && *out == convert(*tmp)){
        
        *val += (isSub(*tmp)) ? -1 : 1;
        tmp++;
        
        if(isJumpC(*out))
            break;
        
    }

    *offset = tmp - code;
  
    return (*code);
    
}

static char store(char c,int mode){

    if(c == CMT)
        comment = TRUE;
    else if(c == '\n')
        comment = FALSE;

    if(comment)
        return FALSE;

    if(isBf(c) || ((mode & DEBUG_CODE) && (c == DBG_C) ) )
        return TRUE;

    else if((mode & WARNING_CODE) && !isspace(c))
        enableCodeWarn();


    return FALSE;

}

static size_t length(char* str,int mode){

	size_t out = 0;
	char c;

	while((c = *str++))
		if(store(c,mode))
			out++;


	return out;

}

static char* filter(char* code,int mode){

	char* buff = (char*) allocmem(length(code,mode) + 1,sizeof(char));
	char* out  = buff;

	char c;
	while((c = *code++))
		if(store(c,mode))
			*buff++ = c;

	return out;
}

int setCode(char* in,int mode){

	in = filter(in,mode);

	long tokens = count(in);
	if(tokens < 0)
		return tokens;

    command* out = (command*) allocmem(tokens,sizeof(command));

    command* tmp = out;
    char* tbuff = in;
    
    uint8_t cmd;
    int32_t val;
    
    size_t offset;
    
    while(tokenizer(tbuff,&cmd,&val,&offset)){
        
        tbuff += offset;
    
        if((val == 0) && (!isJump(cmd)))
            continue;
            
        tmp->cmd = cmd;
        tmp->val = val;
        
        tmp++;
        
    }
    
    tmp->cmd = END_PRG;

    resolveJumps(out);

    cmds = out;
    release(in);

    return OK;

}

command* getCommand(){
	return cmds;
}

int getJumps(){
	return errors;
}



