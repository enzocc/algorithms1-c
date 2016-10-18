#ifndef LIBDEF
	#define LIBDEF
	#include "stdio.h"
	#include "stdlib.h"
	#include "utilities.h"
	#include "heap.h"
#endif

int main(int argc, char const *argv[])
{
	char fileName[50];
	int arraySize=0, *lowHalfArray, *highHalfArray,i,temp,medianSum=0;
	FILE* fp;

	tHeap lowHalf, highHalf;

	if (argc!=2){
		printf("ERROR : This function only takes as parameter the name of the file to analyze - max 50 characters\n");
		return 1;
	}
	sprintf(fileName,"%s",argv[1]);

	if(!(fp=fopen(fileName,"r"))){
		printf("ERROR : File doesn't exists\n");
		return 1;
	}

	arraySize=getLinesInFile(fp);
	
	lowHalfArray = (int*) malloc(arraySize/2*sizeof(int));
	highHalfArray = (int*) malloc((arraySize - arraySize/2)*sizeof(int));

	lowHalf.lastIndex = 0;
	lowHalf.maxSize = arraySize/2;
	lowHalf.hElem = lowHalfArray;

	highHalf.lastIndex = 0;
	highHalf.maxSize = arraySize - arraySize/2;
	highHalf.hElem = highHalfArray;

	medianSum=getNumFromFile(fp); 	//First number is the first median
	temp=getNumFromFile(fp);			//Get second number

	if(medianSum < temp){		//The second median is the lower of both (first and second number)
		lowHalf.hElem[0]= medianSum;
		highHalf.hElem[0]=temp;
		medianSum = 2*medianSum;
	}
	else {
		lowHalf.hElem[0]= temp;
		highHalf.hElem[0]=medianSum;
		medianSum = medianSum + temp;
	}

	for(i=2;i<arraySize;i++){
		temp=getNumFromFile(fp);				//Get new number
		if (temp>highHalf.hElem[0])		//If the new number is bigger than the first element (lower) of highHeap
			heapInsert(&highHalf,temp,TRUE);	//Insert new number to highHeap
		else
			heapInsert(&lowHalf,temp,FALSE);	//Insert new number to lowHeap

		// Reorganize heaps
		if((lowHalf.lastIndex-highHalf.lastIndex)==2){			//If lowHeap has two more elements than highHeap
			heapInsert(&highHalf,heapGet(&lowHalf,FALSE),TRUE);	//Move one element from lowHeap to highHeap
			medianSum=medianSum+lowHalf.hElem[0];				//Add first element (higher) of lowHeap to median
		}
		else if((lowHalf.lastIndex-highHalf.lastIndex)==1){		//If lowHeap has one more element than highHeap
			medianSum=medianSum+lowHalf.hElem[0];				//Add first element (higher) of lowHeap to median
		}
		else if((highHalf.lastIndex-lowHalf.lastIndex)==2){		//If highHeap has two more elements than lowHeap
			heapInsert(&lowHalf,heapGet(&highHalf,TRUE),FALSE);	//Move one element from highHeap to lowHeap
			medianSum=medianSum+lowHalf.hElem[0];				//Add first element (higher) of lowHeap to median
		}
		else if((highHalf.lastIndex-lowHalf.lastIndex)==1){		//If highHeap has one more element than lowHeap
			medianSum=medianSum+highHalf.hElem[0];				//Add first element (lower) of highHeap to median
		}
		else													//If highHeap and lowHeap has equal number of elements
			medianSum=medianSum+lowHalf.hElem[0];				//Add first element (higher) of lowHeap to median
	}

	printf("Total Count: %u\n", medianSum);

	return 0;
}