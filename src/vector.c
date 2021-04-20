#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>

void vecResize(vector* v, int tab_size){
    v->arr = realloc(v->arr, (tab_size)*(sizeof(void*)));
    v->table_size = tab_size;
}

void vecAdd(vector* v, void* data){
    if(v->cur_size == v->table_size){
        vecResize(v, (v->table_size<<1));
    }
    v->arr[v->cur_size++] = data;
}

int vecSize(vector* v){
    return v->cur_size;
}

void* vecElemAtI(vector* v, int i){
    if(i>=0 && i<v->cur_size){
        return v->arr[i];
    }
}

void vecSetElemAtI(vector* v, void* data, int i){
    if(i>=0 && i<v->cur_size){
        v->arr[i] = data;
    }
}

void vecDelElemAtI(vector* v, int ind){
    for(int i=ind;i<v->cur_size-1;i++){
        v->arr[i] = v->arr[i+1];
    }
    v->cur_size--;
    if(v->cur_size == v->table_size/4){
        vecResize(v, v->table_size>>1);
    }
}

void vecPopBack(vector* v){
    if(v->cur_size==0) return;
    vecDelElemAtI(v, v->cur_size-1);
}

void createVector(vector* v, int n){
    v->arr = (void*)malloc(sizeof(void*)*n);
    v->cur_size = 0;
    v->table_size = n;

    v->size = vecSize;
    v->resize = vecResize;
    v->push_back = vecAdd;
    v->getElem = vecElemAtI;
    v->setElem = vecSetElemAtI;
    v->delElem = vecDelElemAtI;
    v->pop_back = vecPopBack;
}