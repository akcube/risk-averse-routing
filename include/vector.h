#ifndef __VECTOR
#define __VECTOR

#include <stdlib.h>
typedef struct vector vector;

struct vector{
	void** arr;
	int cur_size;
	int table_size;

	void (*push_back)(vector*, void*);
	int (*size)(vector*);
	void (*pop_back)(vector*);
	void (*resize)(vector*, int);
	void* (*getElem)(vector*, int);
	void (*setElem)(vector*, void* data, int);
	void (*delElem)(vector*, int);

};

void createVector(vector* v, int n);
void deleteVector(vector* v);

#endif
