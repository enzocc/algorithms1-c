#include "stdio.h"
#include "stdlib.h"

#define NUMBER_MAX_DIGIT 50

int printArray(int size,int* array, char* message){
	printf("%s: ", message);
	for (int i=0;i<size;i++){
		printf("%d ", array[i]);
	}
	printf("\n");
	return 0;
}

int arraySwap(int **array, int indexA, int indexB){
	int temp=(*array)[indexA];
	(*array)[indexA]=(*array)[indexB];
	(*array)[indexB]= temp;
	return 0;
}

int readArray(FILE* fp, int* arraySize, int** array){
	int i;
	char temp[NUMBER_MAX_DIGIT];
	
	do{
		(*arraySize)++;
	} while(fgets(temp,sizeof(temp),fp)!=NULL);
	
	(*arraySize)--;
	*array= malloc((*arraySize)*sizeof(int));
	rewind(fp);

	for(i=0;i<(*arraySize);i++){
		(*array)[i]=atoi(fgets(temp,sizeof(temp),fp));
	}
	
	return 0;
}