#ifndef __HASH
#define __HASH

#include<stdint.h>
#include<stdbool.h>

typedef struct node{
	void *key;
    int value;
} node;

typedef struct Hashtable{
	node *buff;
	uint32_t table_size;
	uint32_t element_count;
	bool (*insert)(struct Hashtable *self, void *key, uint32_t size, int val);
	int (*get)(struct Hashtable *self, void *key, uint32_t size);
	int (*erase)(struct Hashtable *self, void *key, uint32_t size);
} Hashtable;

void create_hash_table(Hashtable *self, uint32_t table_size);
void destroy_hash_table(Hashtable *self);

#endif