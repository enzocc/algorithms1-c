#include "stdio.h"
#include "stdlib.h"

typedef struct heap{
	int data;
	int ID;
	struct heap *next;
} tHeap:


*tHeap heap_gotoIndex(tHeap* heap, int pos){
	tHeap *h;
	h = heap;
	while(count=!pos){
		h=h->next;
	}
	return h;
}

int heap_moveLasttoFirst(tHeap** heap, int index){
	tHeap *h, *h1;
	h = heap_gotoIndex(*heap,index-2);		//Runs un O(n) time
	h1 = *heap;

	*heap = h->next;
	free(h1);
	h->next=NULL;
	return 0;
}

int heap_getSize(tHeap heap){
	tHeap *h;
	int count=0;

	h = heap;
	while(h){
		h = h->next;
		count ++;
	}

	return count;
}

int heap_getMin(tHeap** heap){
	tHeap *h;
	int ret,size;
	
	h = *tHeap;
	ret=h->data;

	size = heap_getSize(*heap);
	
	heap_moveLasttoFirst(heap);
	
	

	return ret;
}