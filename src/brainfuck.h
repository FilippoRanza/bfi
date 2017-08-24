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
#ifndef BRAINFUCK_H
#define BRAINFUCK_H
#include <stdint.h>
#include <stddef.h>
/*
 * Brainfuck commands
 */

#define ADD_C '+'
#define SUB_C '-'

#define PTR_I_C '>'
#define PTR_D_C '<'

#define PRINT_C '.'
#define READ_C  ','

#define JUMP_A_C '['
#define JUMP_B_C ']'

/*
 * non standard brainfuck extension
 * comment and debug
 */
#define CMT '#'
#define DBG_C '?'

/*
 * Compressed code commands
 */
#define NONE -1

#define VAL 0
#define MEM 1

#define READ  2
#define PRINT 3

#define JUMP_A 4
#define JUMP_B 5

#define END_PRG 6

#define DBG 7

/*
 * Test macros
 */

#define isBf(c) (c == ADD_C) || (c == SUB_C) || (c == PTR_I_C) || (c == PTR_D_C) || \
    (c == PRINT_C) || (c == READ_C) || (c == JUMP_A_C) || (c == JUMP_B_C) 
            
#define isJump(c) (c == JUMP_A_C) || (c == JUMP_B_C)
    
#define isJumpC(c) (c == JUMP_A) || (c == JUMP_B)
    

#define isSub(c) (c == SUB_C) || (c == PTR_D_C)

#define TRUE  1
#define FALSE 0    


typedef struct{
    
    uint8_t cmd;
    int32_t val;
    
}command;


#endif
