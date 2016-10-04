#include "stdio.h"
#include "stdlib.h"
#include "utilities.h"

typedef struct heap{
	int lastIndex;
	int maxSize;
	int* hElem;
} tHeap;


/* Working Version
int heapDelete(tHeap* heap, int index){
	int ret,i,min_Index;	
	ret = heap->hElem[index];
	heap->hElem[index] = heap->hElem[heap->lastIndex];
	(heap->lastIndex)--;

	for(i=index;i<=(heap->lastIndex-2)/2;i=min_Index){
		if(heap->hElem[2*i+1]<heap->hElem[2*i+2])
			min_Index=2*i+1;
		else
			min_Index=2*i+2;
		if(heap->hElem[i]>heap->hElem[min_Index])
			arraySwap(&(heap->hElem),i,min_Index);
		else
			return ret;
	}

// The following routine counts the case of uncomplete trees
// The last root with children, will only have one, so the previous FOR loop
// won't consider this root (will only count until the previous one, with two children)
// The following if sentence, evaluate the existence (or not) of a single parent.

	if((2*i+1)==heap->lastIndex)		
		if(heap->hElem[i+1]>heap->hElem[2*i+1])
			arraySwap(&(heap->hElem),i,2*i+1);
	return ret;
}
*/

int bubbleDown(tHeap* heap, int index){
	int min_Index;
	if(2*index+2 <= heap->lastIndex){
		if(heap->hElem[2*index+1]<heap->hElem[2*index+2])
			min_Index=2*index+1;
		else
			min_Index=2*index+2;
		if(heap->hElem[index]>heap->hElem[min_Index]){
			arraySwap(&(heap->hElem),index,min_Index);
			bubbleDown(heap,min_Index);
		}
	}
	else if(2*index+1 == heap->lastIndex){
		if(heap->hElem[index]>heap->hElem[2*index+1]){
			arraySwap(&(heap->hElem),index,2*index+1);
		}
	}
	return 0;
}
int heapDelete(tHeap* heap, int index){
	int ret,i,min_Index;	
	ret = heap->hElem[index];
	heap->hElem[index] = heap->hElem[heap->lastIndex];
	(heap->lastIndex)--;

	bubbleDown(heap,index);
	return ret;
}

int heapGet(tHeap* heap){
	return heapDelete(heap,0);
}

int heapInsert(tHeap* heap, int new){
	int i;
	(heap->lastIndex)++;
	heap->hElem[heap->lastIndex] = new;

	for(i=heap->lastIndex;i>=1;i=(i-1)/2){
		if(heap->hElem[i]<heap->hElem[(i-1)/2])
			arraySwap(&(heap->hElem),i,(i-1)/2);
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

int main(int argc, char const *argv[])
{
	tHeap test;
	int array[11],i;

	/*array[0]=10;
	array[1]=9;
	array[2]=8;
	array[3]=7;
	array[4]=6;
	array[5]=5;
	array[6]=4;
	array[7]=3;
	array[8]=2;
	array[9]=11;
	array[10]=1;*/
	
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
	test.lastIndex=10;
	test.hElem = array;

	heapify(&test);
	printf("All Elements:");
	for(i=0;i<=test.lastIndex;i++)
		printf(" %d ", test.hElem[i]);
	printf("\n");

	printf("min Elem (1) : %d\n", heapGet(&test));
	printf("min Elem (2) : %d\n", heapGet(&test));
	printf("min Elem (3) : %d\n", heapGet(&test));
	printf("min Elem (4) : %d\n", heapGet(&test));
	printf("min Elem (5) : %d\n", heapGet(&test));

	printf("Remaining Elements:");
	for(i=0;i<=test.lastIndex;i++)
		printf(" %d ", test.hElem[i]);
	printf("\n");

	heapInsert(&test,16);
	printf("Remaining Elements:");
	for(i=0;i<=test.lastIndex;i++)
		printf(" %d ", test.hElem[i]);
	printf("\n");

	heapInsert(&test,4);
	printf("Remaining Elements:");
	for(i=0;i<=test.lastIndex;i++)
		printf(" %d ", test.hElem[i]);
	printf("\n");

	printf("min Elem (6) : %d\n", heapGet(&test));
	printf("min Elem (7) : %d\n", heapGet(&test));
	printf("min Elem (8) : %d\n", heapGet(&test));
	printf("min Elem (9) : %d\n", heapGet(&test));
	printf("min Elem (10) : %d\n", heapGet(&test));

	printf("Remaining Elements:");
	for(i=0;i<=test.lastIndex;i++)
		printf(" %d ", test.hElem[i]);
	printf("\n");
	
	return 0;
}