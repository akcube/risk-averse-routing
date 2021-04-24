#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#ifndef DATA_TYPE
	//#error Requires DATA_TYPE to be defined 
    #define DATA_TYPE int
#endif

#define _CAT2(x,y) x##y
#define CAT2(x,y) _CAT2(x,y)
#define CAT3(x,y,z) CAT2(x,CAT2(y,z))

#ifndef HEAP
	#define HEAP CAT2(heap_, DATA_TYPE)
	#define __HEAPGETTOP CAT3(__, DATA_TYPE, __heap__gettop)
	//#define __HEAPINSERT CAT3(__, DATA_TYPE, __heap__insert)
	#define __HEAPMINPOP CAT3(__, DATA_TYPE, __heap__minpop)
	#define __HEAPMAXPOP CAT3(__, DATA_TYPE, __heap__maxpop)
	#define createheap CAT3(create_, DATA_TYPE, _heap)
	#define destroyheap CAT3(destroy_, DATA_TYPE, _heap)
#endif

typedef struct HEAP{
	DATA_TYPE *arr;
	u_int32_t size;
	u_int32_t table_size;
	int max;
	void (*insert)(DATA_TYPE val, struct HEAP *heap);
	DATA_TYPE (*getTop)(struct HEAP *heap);
	DATA_TYPE (*pop)(struct HEAP *heap);
} HEAP;

void createHeap(uint32_t n, int max, HEAP *heap);
void deleteHeap(HEAP *heap);

//Util functions
inline int getRight(int i){	return (i<<1)+2; }
inline int getLeft(int i){ return (i<<1)+1; }
inline int getParent(int i){ return ((i-1)>>1)*(i!=0); }
inline int max(int a, int b){ return (a>b)?a:b; }
inline int min(int a, int b){ return (a<b)?a:b; }

void swap(DATA_TYPE *a, DATA_TYPE *b){
	DATA_TYPE temp = *a;
	*a = *b;
	*b = temp;
}

DATA_TYPE __HEAPGETTOP(HEAP *heap){
	return (heap->arr[0]);
}

//Max Heap Functions
void maxHeapify(int id, HEAP *heap){
	while(heap->arr[getParent(id)] < heap->arr[id]){
		swap(&(heap->arr[getParent(id)]), &(heap->arr[id]));
		id = getParent(id);
	}
}

void maxInsert(DATA_TYPE val, HEAP *heap){
	if(heap->size==heap->table_size){
		heap->table_size <<= 1;
		heap->arr = (DATA_TYPE*)realloc(heap->arr, ((heap->size)<<1)*sizeof(DATA_TYPE));
	}
	heap->arr[heap->size] = val;
	maxHeapify(heap->size, heap);
	heap->size = heap->size+1;
}

void maxSiftDown(int id, HEAP *heap){

	DATA_TYPE ma;
	if(getLeft(id) >= heap->size) return;
	else if(getRight(id) >= heap->size) {
		ma = heap->arr[getLeft(id)];
		if(ma > heap->arr[id])
			swap(&(heap->arr[id]), &(heap->arr[getLeft(id)]));
		return;
	}

	ma = max(heap->arr[getRight(id)], heap->arr[getLeft(id)]);
	while(ma > heap->arr[id]){
		if(heap->arr[getRight(id)] > heap->arr[getLeft(id)])
			swap(&(heap->arr[id]), &(heap->arr[getRight(id)]));
		else
			swap(&(heap->arr[id]), &(heap->arr[getLeft(id)]));
		
		if(getLeft(id) >= heap->size) break;
		else if(getRight(id) >= heap->size) {
			ma = heap->arr[getLeft(id)];
			if(ma > heap->arr[id])
				swap(&(heap->arr[id]), &(heap->arr[getLeft(id)]));
			break;
		}

		ma = max(heap->arr[getRight(id)], heap->arr[getLeft(id)]);
	}
}

DATA_TYPE __HEAPMAXPOP(HEAP *heap){
	if(heap->size==0) return -1;
	DATA_TYPE top = __HEAPGETTOP(heap);
	swap(&(heap->arr[0]), &(heap->arr[heap->size-1]));
	heap->size--;
	maxSiftDown(0, heap);
	return top;
}

//Min Heap Functions
void minHeapify(int id, HEAP *heap){
	while(heap->arr[getParent(id)] > heap->arr[id]){
		swap(&(heap->arr[getParent(id)]), &(heap->arr[id]));
		id = getParent(id);
	}
}

void minInsert(DATA_TYPE val, HEAP *heap){
	if(heap->size==heap->table_size){
		heap->table_size <<= 1;
		heap->arr = (DATA_TYPE*)realloc(heap->arr, ((heap->size)<<1)*sizeof(DATA_TYPE));
	}
	heap->arr[heap->size] = val;
	minHeapify(heap->size, heap);
	heap->size = heap->size+1;
}

void minSiftDown(int id, HEAP *heap){
	
	DATA_TYPE mi;
	if(getLeft(id) >= heap->size) return;
	else if(getRight(id) >= heap->size) {
		mi = heap->arr[getLeft(id)];
		if(mi < heap->arr[id])
			swap(&(heap->arr[id]), &(heap->arr[getLeft(id)]));
		return;
	}

	mi = min(heap->arr[getRight(id)], heap->arr[getLeft(id)]);
	while(mi < heap->arr[id]){
		if(heap->arr[getRight(id)] < heap->arr[getLeft(id)])
			swap(&(heap->arr[id]), &(heap->arr[getRight(id)]));
		else
			swap(&(heap->arr[id]), &(heap->arr[getLeft(id)]));
		
		if(getLeft(id) >= heap->size) break;
		else if(getRight(id) >= heap->size) {
			mi = heap->arr[getLeft(id)];
			if(mi < heap->arr[id])
				swap(&(heap->arr[id]), &(heap->arr[getLeft(id)]));
			break;
		}

		mi = min(heap->arr[getRight(id)], heap->arr[getLeft(id)]);
	}
}

DATA_TYPE __HEAPMINPOP(HEAP *heap){
	if(heap->size==0) return -1;
	DATA_TYPE top = __HEAPGETTOP(heap);
	swap(&(heap->arr[0]), &(heap->arr[heap->size-1]));
	heap->size--;
	minSiftDown(0, heap);
	return top;
}

void createHeap(uint32_t n, int max, HEAP *heap){
	heap->arr = (DATA_TYPE*) malloc(sizeof(DATA_TYPE)*n);
	heap->size = 0;
	heap->table_size = n;
	heap->max = max;
	if(max){
		heap->insert = maxInsert;
		heap->pop = __HEAPMAXPOP;
	}
	else{
		heap->insert = minInsert;
		heap->pop = __HEAPMINPOP;
	}
	heap->getTop = __HEAPGETTOP;
}

void deleteHeap(HEAP *heap){
	free(heap->arr);
	heap->size = 0;
}

#undef DATA_TYPE
#undef HEAP