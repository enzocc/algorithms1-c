#include "stdio.h"
#include "stdlib.h"
#include "utilities.h"

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
		if(*temp==',')
			(temp)++;
		i++;
	}
	return i;	//Number of elements in the string
}

int arraySwap(tVERTEX **array, int indexA, int indexB){
	tVERTEX* temp=array[indexA];
	array[indexA]=array[indexB];
	array[indexB]= temp;
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