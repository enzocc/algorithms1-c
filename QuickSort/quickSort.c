#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "utilities.h"

int selectPivot1(int**array, int minIndex, int maxIndex){ //Pivot is the left most element of the array
	return minIndex;
}

int selectPivot2(int**array, int minIndex, int maxIndex){//Pivot is the right most element of the array
	return maxIndex;
}

int selectPivot3(int**array, int minIndex, int maxIndex){//Pivot is the median of the right, left and medium elements of the array
	int a=(*array)[minIndex],b=(*array)[(minIndex+maxIndex)/2],c=(*array)[maxIndex];
	if((a<b) && (b<c))
		return (minIndex+maxIndex)/2;
	if((c<b) && (b<a))
		return (minIndex+maxIndex)/2;
	if((b<a) && (a<c))
		return minIndex;
	if((c<a) && (a<b))
		return minIndex;
	if((a<c) && (c<b))
		return maxIndex;
	if((b<c) && (c<a))
		return maxIndex;
	else 
		return -1;
}

int organize(int** array, int minIndex, int maxIndex){
	int i=minIndex+1,j=minIndex+1,pivotIndex;
	int count=maxIndex-minIndex;		//Number of comparisons: Pivot with (arraySize -1) elements
	
	if(maxIndex==minIndex){ 			//Base case: Array of one element
		return 0;
	}
	if((pivotIndex=selectPivot2(array,minIndex,maxIndex))!=minIndex)
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

int main(int argc, char const *argv[])
{
	char fileName[50];
	int arraySize=0, *array, count;

	FILE* fp;

	if (argc!=2){
		printf("ERROR : This function only takes as parameter the name of the file to analyze - max 50 characters\n");
		return 1;
	}
	sprintf(fileName,"%s",argv[1]);

	if(!(fp=fopen(fileName,"r"))){
		printf("ERROR : File doesn't exists\n");
		return 1;
	}

	readArray(fp,&arraySize,&array);
	printArray(arraySize,array,"Normal Array: ");
	count=organize(&array,0,arraySize-1);
	printArray(arraySize,array,"Sorted Array: ");

	printf("Total Count: %u\n", count);

	return count;
}