#ifndef LIBDEF
	#define LIBDEF
	#include "stdio.h"
	#include "stdlib.h"
	#include "utilities.h"
	#include "time.h"
#endif

int selectPivot(int**array, int minIndex, int maxIndex){//Pivot is a random number between maxIndex and minIndex
	return rand()%(maxIndex-minIndex) + minIndex;
}

int organize(int** array, int minIndex, int maxIndex){
	int i=minIndex+1,j=minIndex+1,pivotIndex;
	int count=maxIndex-minIndex;		//Number of comparisons: Pivot with (arraySize -1) elements
	
	if(maxIndex==minIndex){ 			//Base case: Array of one element
		return 0;
	}
	if((pivotIndex=selectPivot(array,minIndex,maxIndex))!=minIndex)
		arraySwap(array,pivotIndex,minIndex);

	for(j=minIndex+1;j<=maxIndex;j++){
		if((*array)[j]<(*array)[minIndex]){
			arraySwap(array,j,i);
			i++;
		}
	}

	arraySwap(array,minIndex,i-1);
	
	if((i-minIndex)!=1){				//If there is an element smaller than the pivot.
		count+=organize(array,minIndex,i-2);
	}
	if((i-maxIndex)!=1){				//If there is an element bigger than the pivot.
		count+=organize(array,i,maxIndex);
	}
	return count;
}

bool binarySearch(int* array, int arraySize, int lookingFor){
	if((lookingFor>array[arraySize-1])||(lookingFor<array[0]))
		return FALSE;

	if(arraySize == 1){
		if((*array)!=lookingFor)
			return FALSE;
		else{
			return TRUE;
		}
	}

	if(array[arraySize/2]==lookingFor){
		return TRUE;
	}
	else if(array[arraySize/2]<lookingFor){
		return binarySearch(&array[arraySize/2+1], arraySize - arraySize/2-1, lookingFor);//binarySearch(&array[arraySize/2], arraySize - arraySize/2, lookingFor);//
	}
	else if(array[arraySize/2]>lookingFor){
		return binarySearch(array, arraySize/2, lookingFor);
	}
}

int main(int argc, char const *argv[])
{
	int arraySize = 0, *array,*array_noDup,size_noDup, count=0,i,j,toLook;
	bool exit;
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
	srand(time(NULL));

	readArray(fp,&arraySize, &array);
	organize(&array,0,arraySize-1);

	array_noDup=malloc(arraySize*sizeof(int));

	array_noDup[0]=array[0];
	size_noDup=1;
	for(i=1;i<arraySize;i++){
		if(array[i]!=array[i-1]){
			array_noDup[size_noDup]=array[i];
			size_noDup++;
		}
		//else
			//printf("equal!: %d\n", array[i]);
	}
	//printArray(size_noDup,array_noDup, "Ordered Array, without duplicates");
	printf("Size of noDup:%d\n",size_noDup);

	for(j=-10000;j<10001;j++){
		i=0;
		exit=FALSE;
		while(exit==FALSE){
			toLook=j-array_noDup[i];
			//printf("suma=%d => Current element: %d, looking for: %d\n",j,array[i],toLook);
			if(array_noDup[i]==toLook){
				exit=TRUE;
			}
			else if(binarySearch(array_noDup,size_noDup,toLook)){
				count++;
				exit = TRUE;
				//printf("Target SUM: %d, Evaluating: %d\n", j, array[i]);
			}
			i++;
			if(i==size_noDup)
				exit=TRUE;
		}
	}
	printf("%d\n", count);

	return 0;
}