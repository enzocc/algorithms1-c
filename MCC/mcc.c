#include "stdio.h"
#include "stdlib.h"
#include "utilities.h"

typedef struct dEDGE
{
	//int edgeID;
	struct dVERTEX* tailVertex;
	struct dVERTEX* headVertex;
	struct dEDGE* nextEdge;
} tEDGE;

typedef struct dVERTEX
{
	int vertexID;
	bool explored;
	int numbOfEdges;
	struct dEDGE* firstEdge;
	struct dVERTEX* nextVertex;
} tVERTEX;

int printGraph(tVERTEX **graph){
	int i;
	tVERTEX *v;
	tEDGE *e;
	v=*graph;
    while(v)
    {
       	printf("%d (%d)",v->vertexID, v->numbOfEdges);
       	e=v->firstEdge;
       	while(e)
       	{
           	printf("->%d",e->edgeID);
           	e=e->nextEdge;
       	}
   		printf("\n");
   		v=v->nextVertex;
    }
    return 0;
}

int readGraph(FILE *fp, tVERTEX **graph, int* vertexNumber){
	int i, j, numbersInLine, arrayNumber[LINE_MAX_SIZE_CHAR];
	char *ret1, line[LINE_MAX_SIZE_INT];
	tVERTEX *v,*v1;
	tEDGE *e;

	if(fgets(line,sizeof(line),fp)!=NULL){
		(*graph)=(tVERTEX*)malloc(sizeof(tVERTEX));
		v=*graph;

		getNumbersFromString(line,arrayNumber);
		(*vertexNumber)++;
		v->vertexID = arrayNumber[0];
		v->explored = FALSE;
		v->numbOfEdges=1;

		v1==(tVERTEX*)malloc(sizeof(tVERTEX));
		v->nextVertex=v1;
		v->vertexID = arrayNumber[1];
		v->explored = FALSE;
		v->numbOfEdges=0;
		(*vertexNumber)++;

		e=(tEDGE*) malloc(sizeof(tEDGE));
		e->headVertex = v;
		e->tailVertex = v1;
		e->nextEdge = NULL;
		v->firstEdge=e;
	}

	while(fgets(line,sizeof(line),fp)!=NULL){
		getNumbersFromString(line,arrayNumber);
		v=*graph;
		v1=NULL;
		while(v->nextVertex!=NULL){
			if(v->vertexID == arrayNumber[0]){
				(v->numbOfEdges)++;



				
				if(v1!=NULL){
					e->nextEdge=(tEDGE*) malloc(sizeof(tEDGE));
					e->nextEdge->headVertex = v;
					e->nextEdge->headVertex = v1;
					e->nextEdge->nextEdge = NULL;
					e=e->nextEdge;
				}
				break;
			}
			if(v->vertexID == arrayNumber[1]){
				v1=v;
			}
			v=v->nextVertex;
		}		




		if(v->vertexID == arrayNumber[0]){
			(v->numbOfEdges)++;

			e->nextEdge=(tEDGE*) malloc(sizeof(tEDGE));
			e->nextEdge->edgeID = arrayNumber[1];
			e->nextEdge->headVertex = v;
			e->nextEdge->nextEdge = NULL;
			e=e->nextEdge;
		}
		else{
			(*vertexNumber)++;
			v->nextVertex=(tVERTEX*) malloc(sizeof(tVERTEX));
			v->nextVertex->vertexID=arrayNumber[0];
			v->nextVertex->explored=FALSE;
			v->nextVertex->numbOfEdges=1;
			v->nextVertex->nextVertex=NULL;
			v=v->nextVertex;

			e=(tEDGE*) malloc(sizeof(tEDGE));
			e->edgeID = arrayNumber[1];
			e->headVertex = v;
			e->nextEdge = NULL;
			v->firstEdge=e;	
		}
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	FILE *fp;
	char fileName[50];
	int vertexNumber=0, activeVertexNumber=0, twiceEdgesNumber=0,randVertexA,randVertexB,i,min_Cut;
	tVERTEX* graph,*ini;

	if(argc!=2){
		printf("ERROR : This function only takes as parameter the name of the file to analyze - max 50 characters\n");
		return 1;
	}
	sprintf(fileName,"%s",argv[1]);
	
	if(!(fp=fopen(fileName,"r"))){
		printf("ERROR: File doesn't exists\n");
		return 1;
	}


	
	readGraph(fp, &graph,&vertexNumber);

	printGraph(&graph);

	return 0;
}