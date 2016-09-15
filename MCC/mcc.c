#include "stdio.h"
#include "stdlib.h"
#include "utilities.h"

typedef struct dEDGE
{
	int vertexID;
	bool explored;
	struct EDGE *nextEdge;
} tEDGE;

typedef struct dVERTEX
{
	int vertexID;
	bool explored;
	int numbOfEdges;
	struct EDGE* firstEdge;
} tVERTEX;

int main(int argc, char const *argv[])
{
	FILE *fp;
	char fileName[50];
	int vertexNumber=0, activeVertexNumber=0, twiceEdgesNumber=0,randVertexA,randVertexB,i,min_Cut;
	tVERTEX *graph;

	if(argc!=2){
		printf("ERROR : This function only takes as parameter the name of the file to analyze - max 50 characters\n");
		return 1;
	}
	sprintf(fileName,"%s",argv[1]);
	
	if(!(fp=fopen(fileName,"r"))){
		printf("ERROR: File doesn't exists\n");
		return 1;
	}

	return 0;
}