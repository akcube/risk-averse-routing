#include "../include/heaps.h"
#include<stdio.h>
#include<stdlib.h>

//Util functions
inline int getRight(int i){	return (i<<1)+2; }
inline int getLeft(int i){ return (i<<1)+1; }
inline int getParent(int i){ return ((i-1)>>1)*(i!=0); }
inline int max(int a, int b){ return (a>b)?a:b; }
inline int min(int a, int b){ return (a<b)?a:b; }
void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int getTop(Heap *heap){
	return (heap->arr[0]);
}

//Max Heap Functions
void maxHeapify(int id, Heap *heap){
	while(heap->arr[getParent(id)] < heap->arr[id]){
		swap(&(heap->arr[getParent(id)]), &(heap->arr[id]));
		id = getParent(id);
	}
}

void maxInsert(int val, Heap *heap){
	if(heap->size==heap->table_size){
		heap->table_size <<= 1;
		heap->arr = realloc(heap->arr, ((heap->size)<<1)*sizeof(int));
	}
	heap->arr[heap->size] = val;
	maxHeapify(heap->size, heap);
	heap->size = heap->size+1;
}

void maxSiftDown(int id, Heap *heap){

	int ma;
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

int maxPop(Heap *heap){
	if(heap->size==0) return -1;
	int top = getTop(heap);
	swap(&(heap->arr[0]), &(heap->arr[heap->size-1]));
	heap->size--;
	maxSiftDown(0, heap);
	return top;
}

//Min Heap Functions
void minHeapify(int id, Heap *heap){
	while(heap->arr[getParent(id)] > heap->arr[id]){
		swap(&(heap->arr[getParent(id)]), &(heap->arr[id]));
		id = getParent(id);
	}
}

void minInsert(int val, Heap *heap){
	if(heap->size==heap->table_size){
		heap->table_size <<= 1;
		heap->arr = realloc(heap->arr, ((heap->size)<<1)*sizeof(int));
	}
	heap->arr[heap->size] = val;
	minHeapify(heap->size, heap);
	heap->size = heap->size+1;
}

void minSiftDown(int id, Heap *heap){
	
	int mi;
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

int minPop(Heap *heap){
	if(heap->size==0) return -1;
	int top = getTop(heap);
	swap(&(heap->arr[0]), &(heap->arr[heap->size-1]));
	heap->size--;
	minSiftDown(0, heap);
	return top;
}


void createHeap(int n, int max, Heap *heap){
	heap->arr = (int*) malloc(sizeof(int)*n);
	heap->size = 0;
	heap->table_size = n;
	heap->max = max;
	if(max){
		heap->insert = maxInsert;
		heap->pop = maxPop;
	}
	else{
		heap->insert = minInsert;
		heap->pop = minPop;
	}
	heap->getTop = getTop;
}

void deleteHeap(Heap *heap){
	free(heap->arr);
	heap->size = 0;
}
