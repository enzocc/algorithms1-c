#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main(int argc, char const *argv[])
{
	int i, outType, numElements, maxValue;
	FILE *genFile;
	char fileName[100];

	if(argc!=1){
		return 1;
	}
	else{
		printf("1. Array\n2. Two dimension pair\n");
		printf("------------------------------\n");
		printf("Enter type of output: ");
		if(scanf("%d",&outType)){
			printf("Enter number of elements: ");
			if(scanf("%d",&numElements)){
				printf("Enter Max Value: ");
				scanf("%d",&maxValue);
				printf("Enter File Name: ");
				scanf("%s",fileName);
				genFile=fopen(fileName,"w");

				srand(time(NULL));
				switch(outType){
					case 1:
						for(i=0;i<numElements;i++){
							fprintf(genFile, "%d\n", rand()%numElements);
						}
						fclose(genFile);
						break;
					case 2:
						for(i=0;i<numElements;i++){
							fprintf(genFile, "%d,%d\n", rand()%maxValue, rand()%maxValue);
						}
						fclose(genFile);						
						break;
					default:
						printf("Error - Selection non available\n");
						break;
				}
			}
		}
	}
	return 0;
}