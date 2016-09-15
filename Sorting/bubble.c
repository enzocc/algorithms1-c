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

int bubbleSort(int size,int* array){
	int i,ready_flag,temp;
	do{
		ready_flag=0;
		for (int i = 0; i < size-1; ++i)
		{
			if(array[i]>array[i+1]){
				temp=array[i];
				array[i]=array[i+1];
				array[i+1]=temp;
				ready_flag=1;
			}
		}
	} while(ready_flag);
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

	bubbleSort(arraySize,array);

	printArray(arraySize,array,"Sorted Array");

	return 0;
}