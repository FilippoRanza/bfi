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
#ifndef MEM_LIB_H
#define MEM_LIB_H

/*
 * 2 = input buffer,command 
 * 100 = nodes
 * 100 = buffers inside nodes
 */

#define HEAP_SZ 202

#define BASE_MEM 10000
#define FRAMES   99
    

#include <stdint.h>
#include <stddef.h>

typedef struct{
    
    void* ptr;
    size_t memb;
    size_t sz;
    
}map;

typedef struct node{
    
    int8_t* buff;
    struct node* prev;
    struct node* next;
    
}node;

typedef struct{
    
    int available;
    size_t nsz;
    
    node* first;
    node* last;
    node* curr;
    
}list;


void initialize();

void* allocmem(size_t numb,size_t sz);

int8_t* check(int8_t* p);
int8_t* getInitial();

void clear();

void release(void *ptr);
void releaseAll();


#endif
