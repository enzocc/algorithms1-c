#include "stdio.h"
#include "stdlib.h"
#include "utilities.h"

typedef struct dEDGE
{
	struct dVERTEX headV;
	struct dVERTEX tailV;
	struct dEDGE* nextEdge;
} tEDGE;

typedef struct dVERTEX
{
	int vertexID;
	bool explored;
	int numbOfEdges;
	struct dEDGE* firstEdge;
} tVERTEX;

int addEdge(tVERTEX* graph, int vertexA, int vertexB){
	tEDGE *e,*e1,*e2;

	e=graph[vertexA-1].firstEdge; //Select first edge connected to the vertexA-1 in the Graph
	while(e && e->nextEdge){	//Check if this egde exists or not, as well as if there is another edge connected to the original vertexA
		e=e->nextEdge;	//If it does exist, verify the following edge. The objective is to find the last edge in the array
	}
	e1=malloc(sizeof(tEDGE));
	e1->vertexID=vertexB;
	e1->nextEdge=NULL;
	if(e)
		e->nextEdge=e1;		//Connect the edge vertexA/vertexB to the last part of the array of vertexA
	else
		graph[vertexA-1].firstEdge=e1;	//Connect the edge vertexA/vertexB as the first edge of the array of vertexA

	e=graph[vertexB-1].firstEdge; //Select first edge connected to the vertexB-1 in the Graph
	while(e && e->nextEdge){	//Check if this egde exists or not, as well as if there is another edge connected to the original vertexB
		e=e->nextEdge;	//If it does exist, verify the following edge. The objective is to find the last edge in the array
	}
	e2= malloc(sizeof(tEDGE));
	e2->vertexID=vertexA;
	e2->nextEdge=NULL;
	if(e)
		e->nextEdge=e2;		//Connect the edge vertexA/vertexB to the last part of the array of vertexA
	else
		graph[vertexB-1].firstEdge=e2;	//Connect the edge vertexA/vertexB as the first edge of the array of vertexA

	graph[vertexA-1].numberEdges++;
	graph[vertexB-1].numberEdges++;
	return 0;

}

int readGraph(FILE *fp, tVERTEX **graph, int* vertexNumber){
	int i, j, numbersInLine, arrayNumber[LINE_MAX_SIZE_CHAR];
	char *ret1, line[LINE_MAX_SIZE_INT];

	while(fgets(line,sizeof(line),fp)!=NULL){
		getNumbersFromString(line,arrayNumber);
	}

	while(fgets(line,sizeof(line),fp)!=NULL){
		(*vertexNumber)++;
		getNumbersFromString(line,arrayNumber);
	}

	(*graph)=(tVERTEX* )malloc((*vertexNumber)*sizeof(tVERTEX));

	// ------- Add vertex to the Graph -------
	rewind(fp);
	i=0;
	while(fgets(line,sizeof(line),fp)!=NULL){
		numbersInLine=getNumbersFromString(line,arrayNumber);
		(*graph)[i].vertexID=arrayNumber[0];
		(*graph)[i].enable=TRUE;
		(*graph)[i].numberEdges=0;
		(*graph)[i].firstEdge=NULL;
		i++;
	}
	// ------- Add edges to the Graph -------
	rewind(fp);
	while(fgets(line,sizeof(line),fp)!=NULL){
		numbersInLine=getNumbersFromString(line,arrayNumber);
		for(j=1;j<numbersInLine;j++){
			//printf("arrayNumber[0]=%d; arrayNumber[%d]=%d\n", arrayNumber[0],j,arrayNumber[j]);
			if(!checkEdgeExist(*graph,arrayNumber[0],arrayNumber[j]))
				addEdge(*graph, arrayNumber[0],arrayNumber[j]);
		}
	}

	return 0;
}

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

	readGraph(fp,&graph,&vertexNumber);

	return 0;
}