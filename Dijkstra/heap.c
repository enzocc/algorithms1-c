#include "stdio.h"
#include "utilities.h"

typedef struct heap{
	int lastIndex;
	int maxSize;
	tVERTEX** hElem;
} tHeap;

int bubbleDown(tHeap* heap, int index){
	int min_Index;
	if(2*index+2 <= heap->lastIndex){
		if(heap->hElem[2*index+1]->key<heap->hElem[2*index+2]->key)
			min_Index=2*index+1;
		else
			min_Index=2*index+2;
		if(heap->hElem[index]->key>heap->hElem[min_Index]->key){
			arraySwap(heap->hElem,index,min_Index);
			bubbleDown(heap,min_Index);
		}
	}
	else if(2*index+1 == heap->lastIndex){
		if(heap->hElem[index]->key>heap->hElem[2*index+1]->key){
			arraySwap(heap->hElem,index,2*index+1);
		}
	}
	return 0;
}
tVERTEX* heapDelete(tHeap* heap, int index){
	int i,min_Index;	
	tVERTEX* ret;
	ret = heap->hElem[index];
	heap->hElem[index] = heap->hElem[heap->lastIndex];
	(heap->lastIndex)--;

	bubbleDown(heap,index);
	return ret;
}

tVERTEX* heapGet(tHeap* heap){
	return heapDelete(heap,0);
}

int heapInsert(tHeap* heap, tVERTEX* new){
	int i;
	(heap->lastIndex)++;
	heap->hElem[heap->lastIndex] = new;

	for(i=heap->lastIndex;i>=1;i=(i-1)/2){
		if(heap->hElem[i]->key<heap->hElem[(i-1)/2]->key)
			arraySwap(heap->hElem,i,(i-1)/2);
		else
			return 0;
	}
	return 0;
}

int heapify(tHeap* heap){
	int i,i_max;
	if(heap->lastIndex%2==0)
		i_max=(heap->lastIndex-2)/2;
	else
		i_max=(heap->lastIndex-1)/2;

	for(i=i_max;i>=0;i--)
		bubbleDown(heap,i);
	return 0;
}