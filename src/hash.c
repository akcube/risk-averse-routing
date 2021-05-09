#include "../include/hash.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t hash(void *data, uint32_t size){
    
    uint64_t hash = 5381;
    uint8_t *byte_data = (uint8_t*) data;

    for (int i = 0; i < size; i++)
        hash = ((hash << 5) + hash) + (*byte_data++); 

    return hash;
}

bool insert(Hashtable *self, void *key, uint32_t size, int val)
{
    uint64_t hashval;
    hashval = hash(key, size) & (self->table_size-1);

    for(int k=0; ; k++){
        uint64_t index = (hashval + k*k) & (self->table_size-1);
        if(!self->buff[index].key){
            self->buff[index].key = calloc(1, 32);
            memcpy(self->buff[index].key, key, size);
            self->buff[index].value = val;
            return true;
        }
    }
    return false;
}

int get(Hashtable *self, void *key, uint32_t size){
    uint64_t hashval;
    hashval = hash(key, size) & (self->table_size-1);

    for(int k=0; ; k++){
        uint64_t index = (hashval + k*k) & (self->table_size-1);
        if(!self->buff[index].key) 
            return -1;
        if(memcmp(self->buff[index].key, key, size)==0)
            return self->buff[index].value;
    }
}

int delete(Hashtable *self, void *key, uint32_t size){
    uint64_t hashval;
    hashval = hash(key, size) & (self->table_size-1);

    for(int k=0; ; k++){
        uint64_t index = (hashval + k*k) & (self->table_size-1);
        if(!self->buff[index].key) 
            return -1;
        if(memcmp(self->buff[index].key, key, size)==0){
            free(self->buff[index].key);
            self->buff[index].key = NULL;
            return 0;
        }
    }
}

void create_hash_table(Hashtable *self, uint32_t table_size){
    table_size = (1 << (32 - __builtin_clz (table_size - 1)));
    self->table_size = table_size;
    self->buff = (node*) calloc(1, sizeof(node)*table_size);
    self->element_count = 0;

    self->get = get;
    self->insert = insert;
    self->erase = delete;
}

void destroy_hash_table(Hashtable *self){
    free(self->buff);
    self->element_count = 0;
    self->table_size = 0;
}