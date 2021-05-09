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