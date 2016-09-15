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

int insertionSort(int size,int* array){
	int i,j,k,temp;
	for(i=1;i<size;i++){
		for(j=0;j<i;j++){
			if(array[i]<array[j]){
				temp = array[i];
				for(k=i;k>j;k--)
					array[k]=array[k-1];
				array[j]=temp;
			}
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

	insertionSort(arraySize,array);

	printArray(arraySize,array,"Sorted Array");

	return 0;
}