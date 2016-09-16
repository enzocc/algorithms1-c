#include "stdio.h"
#include "stdlib.h"
#include "utilities.h"

typedef struct dEDGE
{
	int edgeID;
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
	tVERTEX* v;
	tEDGE* e;

	(*graph)=(tVERTEX*)malloc(sizeof(tVERTEX));
	v=*graph;

	if(fgets(line,sizeof(line),fp)!=NULL){
		getNumbersFromString(line,arrayNumber);
		v->vertexID = arrayNumber[0];
		v->explored = FALSE;
		v->numbOfEdges=1;
		v->nextVertex=NULL;
		e=v->firstEdge;
		e=(tEDGE*) malloc(sizeof(tEDGE));
		e->edgeID = arrayNumber[1];
		e->headVertex = v;
		e->nextEdge = NULL;
		(*vertexNumber)++;
	}

	while(fgets(line,sizeof(line),fp)!=NULL){
		getNumbersFromString(line,arrayNumber);

		if(v->vertexID == arrayNumber[0]){
			(v->numbOfEdges)++;
			e=e->nextEdge;		
		}
		else{
			(*vertexNumber)++;
			v=v->nextVertex;
			v=(tVERTEX*) malloc(sizeof(tVERTEX));
			v->vertexID = arrayNumber[0];
			v->explored = FALSE;
			v->numbOfEdges=1;
			v->nextVertex=NULL;
			printf("--VertexID %d\n", v->vertexID);

			e=v->firstEdge;	
		}

		e=(tEDGE*) malloc(sizeof(tEDGE));
		e->edgeID = arrayNumber[1];
		e->headVertex = v;
		e->nextEdge = NULL;
	}
	printf("%d\n\n",(*graph)->vertexID);

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

	printf("primer - %d\n", graph->vertexID);
	printf("segundo - %d\n", graph->nextVertex->vertexID);

	//printGraph(&graph);

	return 0;
}