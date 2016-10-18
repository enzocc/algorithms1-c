#ifndef LIBDEF
	#define LIBDEF
	#include "stdio.h"
	#include "stdlib.h"
	#include "utilities.h"
	#include "heap.h"
#endif

int bubbleDown(tHeap* heap, int index, bool LOW_HEAP){
	int min_Index, max_Index;
	if(LOW_HEAP){
		if(2*index+2 <= heap->lastIndex){
			if(heap->hElem[2*index+1]<heap->hElem[2*index+2])
				min_Index=2*index+1;
			else
				min_Index=2*index+2;
			if(heap->hElem[index]>heap->hElem[min_Index]){
				arraySwap(&(heap->hElem),index,min_Index);
				bubbleDown(heap,min_Index,LOW_HEAP);
			}
		}
		else if(2*index+1 == heap->lastIndex){
			if(heap->hElem[index]>heap->hElem[2*index+1])
				arraySwap(&(heap->hElem),index,2*index+1);
		}
	}
	else{
		if(2*index+2 <= heap->lastIndex){
			if(heap->hElem[2*index+1]>heap->hElem[2*index+2])
				max_Index=2*index+1;
			else
				max_Index=2*index+2;
			if(heap->hElem[index]<heap->hElem[max_Index]){
				arraySwap(&(heap->hElem),index,max_Index);
				bubbleDown(heap,max_Index,LOW_HEAP);
			}
		}
		else if(2*index+1 == heap->lastIndex){
			if(heap->hElem[index]>heap->hElem[2*index+1])
				arraySwap(&(heap->hElem),index,2*index+1);
		}
	}
	return 0;
}
int heapDelete(tHeap* heap, int index, bool LOW_HEAP){
	int ret,i,min_Index;	
	ret = heap->hElem[index];
	heap->hElem[index] = heap->hElem[heap->lastIndex];
	(heap->lastIndex)--;

	bubbleDown(heap,index, LOW_HEAP);
	return ret;
}

int heapGet(tHeap* heap, bool LOW_HEAP){
	return heapDelete(heap,0, LOW_HEAP);
}

int heapInsert(tHeap* heap, int new, bool LOW_HEAP){
	int i;
	(heap->lastIndex)++;
	heap->hElem[heap->lastIndex] = new;

	if(LOW_HEAP){
		for(i=heap->lastIndex;i>=1;i=(i-1)/2){
			if(heap->hElem[i]<heap->hElem[(i-1)/2])
				arraySwap(&(heap->hElem),i,(i-1)/2);
			else
				return 0;
		}	
	} 
	else{
		for(i=heap->lastIndex;i>=1;i=(i-1)/2){
			if(heap->hElem[i]>heap->hElem[(i-1)/2])
				arraySwap(&(heap->hElem),i,(i-1)/2);
			else
				return 0;
		}
	}
	
	return 0;
}

int heapify(tHeap* heap, bool LOW_HEAP){
	int i,i_max;
	if(heap->lastIndex%2==0)
		i_max=(heap->lastIndex-2)/2;
	else
		i_max=(heap->lastIndex-1)/2;

	for(i=i_max;i>=0;i--)
		bubbleDown(heap,i,LOW_HEAP);

	return 0;
}