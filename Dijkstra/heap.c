#include "stdio.h"
#include "stdlib.h"
#include "utilities.h"

typedef struct heap{
	int lastIndex;
	int maxSize;
	int* hElem;
} tHeap;

int heapGet(tHeap* heap){
	int ret,i,min_Index;	
	ret = heap->hElem[0];
	heap->hElem[0] = heap->hElem[heap->lastIndex-1];
	(heap->lastIndex)--;

	for(i=0;i<=(heap->lastIndex-3)/2;i=min_Index){
		if(heap->hElem[2*i+1]<heap->hElem[2*i+2])
			min_Index=2*i+1;
		else
			min_Index=2*i+2;

		if(heap->hElem[i]>heap->hElem[min_Index])
			arraySwap(&(heap->hElem),i,min_Index);
		else
			return ret;
	}
	return ret;
}

int heapInsert(tHeap* heap, int new){
	int i;
	heap->hElem[heap->lastIndex] = new;
	(heap->lastIndex)++;

	for(i=heap->lastIndex-1;i>=3;i=(i-1)/2){
		if(heap->hElem[i]<heap->hElem[(i-1)/2])
			arraySwap(&(heap->hElem),i,(i-1)/2);
		else
			return 0;
	}

	if(heap->hElem[i]<heap->hElem[0])
		arraySwap(&(heap->hElem),i,0);

	return 0;
}

int heapify(tHeap* heap){
	int i;
	
	for(i=heap->lastIndex-1;i>=3;i--)
		if(heap->hElem[i]<heap->hElem[(i-1)/2])
			arraySwap(&(heap->hElem),i,(i-1)/2);
	if(heap->hElem[2]<heap->hElem[0])
		arraySwap(&(heap->hElem),2,0);
	if(heap->hElem[1]<heap->hElem[0])
		arraySwap(&(heap->hElem),1,0);
	
	return 0;
}

int heapDelete(tHeap* heap, int index){

	return 0;
}

int main(int argc, char const *argv[])
{
	tHeap test;
	int array[11],i;

/*	array[0]=2;
	array[1]=4;
	array[2]=3;
	array[3]=6;
	array[4]=9;
	array[5]=5;
	array[6]=7;*/
	
	array[0]=8;
	array[1]=12;
	array[2]=9;
	array[3]=7;
	array[4]=22;
	array[5]=3;
	array[6]=26;
	array[7]=14;
	array[8]=11;
	array[9]=15;
	array[10]=22;

	test.maxSize=11;
	test.lastIndex=11;
	test.hElem = array;

	heapify(&test);
	printf("All Elements:");
	for(i=0;i<test.lastIndex;i++)
		printf(" %d ", test.hElem[i]);
	printf("\n");

	printf("min Elem (1) : %d\n", heapGet(&test));
	printf("min Elem (2) : %d\n", heapGet(&test));
	printf("min Elem (3) : %d\n", heapGet(&test));
	printf("min Elem (4) : %d\n", heapGet(&test));
	printf("min Elem (5) : %d\n", heapGet(&test));

	printf("Remaining Elements:");
	for(i=0;i<test.lastIndex;i++)
		printf(" %d ", test.hElem[i]);
	printf("\n");

	heapInsert(&test,4);

	printf("Remaining Elements:");
	for(i=0;i<test.lastIndex;i++)
		printf(" %d ", test.hElem[i]);
	printf("\n");

	heapInsert(&test,1);

	printf("Remaining Elements:");
	for(i=0;i<test.lastIndex;i++)
		printf(" %d ", test.hElem[i]);
	printf("\n");
	
	return 0;
}