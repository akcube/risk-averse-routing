//!No idempotency guards on purpose

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#ifndef DATA_TYPE
	#error Requires DATA_TYPE to be defined 
    #define DATA_TYPE int
#endif

#include "macro_utils.h"

#ifndef HEAP
	#define HEAP CAT2(heap_, DATA_TYPE)
	#define __HEAPGETTOP CAT3(__, DATA_TYPE, __heap__top)
	#define __HEAPPUSH CAT3(__, DATA_TYPE, __heap__push)
	#define __HEAPPOP CAT3(__, DATA_TYPE, __heap__pop)
	#define __HEAPIFY CAT3(__, DATA_TYPE, __heapify)
	#define __swap CAT3(__, DATA_TYPE, __swap)
	#define __HEAP_SIFTDOWN CAT3(__, DATA_TYPE, __heap__siftdown)
	#define __heapInv CAT3(__, DATA_TYPE, __invariant)
	#define createHeap CAT3(create_, DATA_TYPE, _heap)
	#define destroyHeap CAT3(destroy_, DATA_TYPE, _heap)
#endif

#ifndef __HEAP_UTIL_FUNCS
#define __HEAP_UTIL_FUNCS
	
	int getRight(int);
	int getLeft(int);
	int getParent(int);
	int max(int, int);
	int min(int, int);

	inline int getRight(int i){	return (i<<1)+2; }
	inline int getLeft(int i){ return (i<<1)+1; }
	inline int getParent(int i){ return ((i-1)>>1)*(i!=0); }
	inline int max(int a, int b){ return (a>b)?a:b; }
	inline int min(int a, int b){ return (a<b)?a:b; }

#endif

typedef struct HEAP{
	DATA_TYPE *arr;
	uint32_t size;
	uint32_t table_size;
	void (*push)(DATA_TYPE val, struct HEAP *heap);
	bool (*cmpfunc)(DATA_TYPE a, DATA_TYPE b);
	DATA_TYPE (*getTop)(struct HEAP *heap);
	DATA_TYPE (*pop)(struct HEAP *heap);
} HEAP;

void createHeap(uint32_t n, bool (*cmpfunc)(DATA_TYPE, DATA_TYPE), HEAP *heap);
void destroyHeap(HEAP *heap);

void __swap(DATA_TYPE *a, DATA_TYPE *b){
	DATA_TYPE temp = *a;
	*a = *b;
	*b = temp;
}

DATA_TYPE __HEAPGETTOP(HEAP *heap){
	assert(heap->size >= 0);
	return (heap->arr[0]);
}

DATA_TYPE __heapInv(DATA_TYPE a, DATA_TYPE b, HEAP *h){
	return (h->cmpfunc(a, b))?a:b;
}

void __HEAPIFY(int id, HEAP *h){
	while(h->cmpfunc(h->arr[id], h->arr[getParent(id)])){
		__swap(&(h->arr[getParent(id)]), &(h->arr[id]));
		id = getParent(id);
	}
}

void __HEAPPUSH(DATA_TYPE val, HEAP *heap){
	if(heap->size == heap->table_size){
		heap->table_size <<= 1;
		heap->arr = (DATA_TYPE*)realloc(heap->arr, ((heap->size)<<1)*sizeof(DATA_TYPE));
	}
	heap->arr[heap->size] = val;
	__HEAPIFY(heap->size++, heap);
}

void __HEAP_SIFTDOWN(int id, HEAP *h){

	DATA_TYPE ma;
	if(getLeft(id) >= h->size) return;
	else if(getRight(id) >= h->size) {
		ma = h->arr[getLeft(id)];
		if(h->cmpfunc(ma, h->arr[id]))
			__swap(&(h->arr[id]), &(h->arr[getLeft(id)]));
		return;
	}

	ma = __heapInv(h->arr[getRight(id)], h->arr[getLeft(id)], h);
	
	while(h->cmpfunc(ma, h->arr[id])){
		if(h->cmpfunc(h->arr[getRight(id)], h->arr[getLeft(id)])){
			__swap(&(h->arr[id]), &(h->arr[getRight(id)]));
			id = getRight(id);
		}
		else{
			__swap(&(h->arr[id]), &(h->arr[getLeft(id)]));
			id = getLeft(id);
		}
		
		if(getLeft(id) >= h->size) break;
		else if(getRight(id) >= h->size) {
			ma = h->arr[getLeft(id)];
			if(h->cmpfunc(ma, h->arr[id]))
				__swap(&(h->arr[id]), &(h->arr[getLeft(id)]));
			break;
		}

		ma = __heapInv(h->arr[getRight(id)], h->arr[getLeft(id)], h);
	}
}

DATA_TYPE __HEAPPOP(HEAP *heap){
	if(heap->size==0) return -1;
	DATA_TYPE top = __HEAPGETTOP(heap);
	__swap(&(heap->arr[0]), &(heap->arr[heap->size-1]));
	heap->size--;
	__HEAP_SIFTDOWN(0, heap);
	return top;
}

void createHeap(uint32_t n, bool (*cmpfunc)(DATA_TYPE, DATA_TYPE), HEAP *heap){
	heap->arr = (DATA_TYPE*) malloc(sizeof(DATA_TYPE)*n);
	heap->size = 0;
	heap->table_size = n;
	heap->push = __HEAPPUSH;
	heap->pop = __HEAPPOP;
	heap->getTop = __HEAPGETTOP;
	heap->cmpfunc = cmpfunc;
}

void destroyHeap(HEAP *heap){
	free(heap->arr);
	heap->size = 0;
}

#undef DATA_TYPE
#undef HEAP