#include "stdio.h"
#include "stdlib.h"

int printArray(int size,int* array, char* message){
	printf("%s: ", message);
	for (int i=0;i<size;i++){
		printf("%d ", array[i]);
	}
	printf("\n");
	return 0;
}

int selectionSort(int size,int* array){
	int i,j,minIndex,temp;
	for(i=0;i<size;i++){
		minIndex=i;
		for(j=i+1;j<size;j++)
			if(array[minIndex]>array[j])
				minIndex=j;
		if(minIndex!=i){
			temp=array[minIndex];
			array[minIndex]=array[i];
			array[i]=temp;
		}
	}
	return 0;
}

int main(int argc, char const *argv[])
{

	int i,arraySize = argc-1; 
	int* array = malloc(arraySize*sizeof(int));

	for(i=0;i<arraySize;i++){
		array[i]=atoi(argv[i+1]);
	}

	printArray(arraySize,array,"Unsorted Array");

	selectionSort(arraySize,array);

	printArray(arraySize,array,"Sorted Array");

	return 0;
}