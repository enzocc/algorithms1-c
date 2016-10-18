#ifndef LIBDEF
	#define LIBDEF
	#include "stdio.h"
	#include "stdlib.h"
	#include "utilities.h"
	#include "heap.h"
#endif

int printArray(int size,int* array, char* message){
	printf("%s: ", message);
	for (int i=0;i<size;i++){
		printf("%d ", array[i]);
	}
	printf("\n");
	return 0;
}

int getNumbersFromString(char* arrayChar, int *arrayNumber){
	int i=0;
	char *temp,*ret1;
	temp=arrayChar;
	while((arrayNumber[i]=(unsigned int) strtol(temp,&ret1,10))!=0){
		temp=ret1;
		i++;
	}
	return i;	//Number of elements in the string
}

int arraySwap(int **array, int indexA, int indexB){
	int temp=(*array)[indexA];
	(*array)[indexA]=(*array)[indexB];
	(*array)[indexB]= temp;
	return 0;
}

int getLinesInFile(FILE* fp){
	int i=0;
	char temp[NUMBER_MAX_DIGIT];
	
	do{
		i++;
	} while(fgets(temp,sizeof(temp),fp)!=NULL);
	i--;
	rewind(fp);
	return i;
}

int getNumFromFile(FILE* fp){
	int i=0;
	char temp[NUMBER_MAX_DIGIT];

	return atoi(fgets(temp,sizeof(temp),fp));;
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