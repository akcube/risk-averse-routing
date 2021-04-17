#ifndef __INCL_HEAPS
#define __INCL_HEAPS

#include<stdlib.h>

static const int MAXHEAP = 1;
static const int MINHEAP = 0;

typedef struct Heap{
	int *arr;
	int size;
	int table_size;
	int max;
	void (*insert)(int val, struct Heap *heap);
	int (*getTop)(struct Heap *heap);
	int (*pop)(struct Heap *heap);
} Heap;

int getRight(int);
int getLeft(int);
int getParent(int);
int max(int, int);
int min(int, int);

void createHeap(int n, int max, Heap *heap);
void deleteHeap(Heap *heap);

#endif