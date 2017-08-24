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
#include "warn_lib.h"

#include "err_lib.h"

#include <stdio.h>

#define READ_WARN 2
#define LOOP_WARN 4 
#define CODE_WARN 8

static int _warn;

void enableCodeWarn(){
    _warn |= CODE_WARN;
}

void checkExec(command* prg){

    int loop   = FALSE;
    int status = FALSE;
    
    while(prg->cmd != END_PRG){
                 
        if(prg->cmd == READ){
            _warn |= READ_WARN;
        }
        else if(prg->cmd == JUMP_A){
            loop = TRUE;
            status  = TRUE;
        }
        else if(prg->cmd == JUMP_B){
            loop = FALSE;
            if(status)
                _warn |= LOOP_WARN;
        }
        
        if(loop && prg->cmd != PRINT && !(isJumpC(prg->cmd))){
            status = FALSE;
        }
        
        prg++;
        
    }
    
}

void showWarn(){
    
    if(_warn & READ_WARN)
        warn("WARNING: Multiple write into same memory block\n");
    
    if(_warn & LOOP_WARN)
        warn("WARNING: Possible endless loop\n");
    
    if(_warn & CODE_WARN)
        warn("WARNING: Embedded comments into code\n");
    
}

