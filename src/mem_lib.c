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
#include "mem_lib.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "brainfuck.h"
#include "err_lib.h"



map*  heap = NULL;

list* l = NULL;
static int init = FALSE;

static void initNode(node* n,int sz){
 
    n->buff = allocmem(sz,sizeof(int8_t));
    
}

static void addNode(list* l, node* n){
    
    n->prev = l->last;
    l->last = n;
    
}

void initialize(){

    map* mtmp  = (map*)  malloc(HEAP_SZ * sizeof(map));
    list* ltmp = (list*) malloc(sizeof(list));
    if(mtmp == NULL || ltmp == NULL)
        die(MEM_ERROR,"can't allocate memory");
    
    heap = mtmp;
    l = ltmp;
  
    for(int i = 0;i < HEAP_SZ;i++){
        
        mtmp->ptr  = NULL;
        mtmp->memb = 0;
        mtmp->sz   = 0;
        
        mtmp++;
        
    }

    node* ctmp = (node*) allocmem(1,sizeof(node));
    
    if(ctmp == NULL)
       die(MEM_ERROR,"can't allocate memory");
    
    initNode(ctmp,BASE_MEM);
    
    l->first = ctmp;
    l->curr  = ctmp;
    l->available = FRAMES;
    l->nsz = BASE_MEM;
    
    
    addNode(l,ctmp);
  
    init = TRUE;
    
}

static node* makeNode(list* l){
    
    node* out = (node*) allocmem(1,sizeof(node));
    initNode(out,l->nsz);
    addNode(l,out);
    
    return out;
    
}

int8_t* check(int8_t* p){
    node* c = l->curr;
    int8_t* out = p; 
    
    int delta = p - c->buff;
    if(delta < 0){
         
        if(c->prev != NULL){
           
            l->curr = c->prev;
            c = c->prev;
            out =  c->buff + l->nsz  - delta;
        }
        else{
           goto EXIT;
        }
        
    }
    else if(delta > l->nsz){
        delta -= l->nsz;
        if(l->available){
           
            l->available--;
            c =  makeNode(l);
            l->curr = c;
            out = c->buff + delta;
        }
        else{
            goto EXIT;
        }
    }
    
    return out;
    EXIT:
         return NULL;
}

int8_t* getInitial(){
    return l->curr->buff;
}

void* allocmem(size_t numb,size_t sz){
    
    void* tmp = NULL;
    for(int i = 0;i < HEAP_SZ;i++){
        if(heap[i].ptr == NULL){
            
            heap[i].ptr  = calloc(numb,sz);
            heap[i].memb = numb;
            heap[i].sz   = sz;
            
            tmp = heap[i].ptr;
            
            break;
        }
    }
    
    if(tmp == NULL)
       die(MEM_ERROR,"can't allocate memory");
    
    return tmp;
        
    
}

void release(void* p){
    
    free(p);
    
    for(int i = 0;i < HEAP_SZ;i++){
        if(heap[i].ptr == p){
            
            heap[i].ptr  = NULL;
            heap[i].memb = 0;
            heap[i].sz   = 0;
            
        }
    }
}


void releaseAll(){
    if(!init)
        return;
    for(int i = 0;i < HEAP_SZ;i++)
        if(heap[i].ptr != NULL){
           
            free(heap[i].ptr);
            heap[i].ptr  = NULL;
            heap[i].memb = 0;
            heap[i].sz   = 0;
        
        }

    free(heap);
    free(l);

}

void clear(){

	node* n = l->first;

	while(n != NULL){
		memset(n->buff,0,l->nsz);
		n = n->next;
	}

	l->curr = l->first;


}
