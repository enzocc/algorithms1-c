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

int mergeSort(int* C,int* A, int* B,int size){
	int i=0,j=0,k;
	for(k=0;k<size;k++){
		if( ((i<size/2) && (A[i]<=B[j])) || (j==size-size/2) ){
			C[k]=A[i];
			i++;
		}
		else if( ((j<size-size/2) && (B[j]<=A[i])) || (i==size/2) ){
			C[k]=B[j];
			j++;
		}
	}
	return 0;
}

int divideArray(int size,int* array){
	int i;
	int *leftHalf, *rightHalf;
	if(size>1){
		leftHalf = malloc(size/2*sizeof(int));
		rightHalf = malloc((size-size/2)*sizeof(int));
		for(i=0;i<size/2;i++){
			leftHalf[i]=array[i];
		}

		for(i=0;i<size-size/2;i++){
			rightHalf[i]=array[i+size/2];
		}
		divideArray(size/2,leftHalf);
		divideArray(size-size/2,rightHalf);
		mergeSort(array,leftHalf,rightHalf,size);
	}
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

int main(int argc, char const *argv[])
{
	int i, arraySize = 0; 
	int* array;
	FILE *fp;
	char fileName[50];

	if(argc!=2){
		printf("ERROR : This function only takes as parameter the name of the file to analyze - max 50 characters\n");
		return 1;
	}
		
	sprintf(fileName,"%s",argv[1]);
	if(!(fp = fopen(fileName,"r"))){
		printf ("ERROR : File doens´t exist\n");
		return 2;
	}

	readArray(fp,&arraySize, &array);

	printArray(arraySize,array,"Unsorted Array");

	divideArray(arraySize,array);

	printArray(arraySize,array,"Sorted Array");

	return 0;
}