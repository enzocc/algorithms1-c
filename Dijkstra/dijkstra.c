#include "stdlib.h"
#include "stdio.h"
#include "utilities.h"

int printGraph(tVERTEX *graph, int vertexCount){
	int i;
	tEDGE *e;
    for(i=0;i<vertexCount;i++)
    {
        printf("%d (%d)",graph[i].vertexID, graph[i].numbOfEdges);
        e=graph[i].vtx
        ;
        while(e){
            printf("->%d,%d",e->vertex->vertexID, e->length);
            e=e->next;
        }
       	printf("\n");
    }
    return 0;
}

int addVertex(tVERTEX* graph, int headVertex, int tailVertex, int length){
	tEDGE *e,*e1;

	e=graph[headVertex-1].vtx;
	while(e && e->next)
		e=e->next;

	e1=malloc(sizeof(tEDGE));
	e1->vertex=&graph[tailVertex-1];
	e1->length=length;
	e1->next=NULL;
	if(e)
		e->next=e1;
	else
		graph[headVertex-1].vtx=e1;

	(graph[headVertex-1].numbOfEdges)++;
	
	return 0;
}

int readGraph(FILE *fp,tVERTEX** graph, int* vertexNumber){
	int i=0, j, arrayNumber[LINE_MAX_SIZE_CHAR], numbersInLine;
	char line[LINE_MAX_SIZE_INT];

	// ------- Find number of vertex in the Graph -------
	while(fgets(line,sizeof(line),fp)!=NULL){
		getNumbersFromString(line,arrayNumber);
		(*vertexNumber)++;
	}
	(*graph)=(tVERTEX*)malloc((*vertexNumber)*sizeof(tVERTEX));

	// ------- Add vertex to the Graph -------
	for(i=0;i<(*vertexNumber);i++){
		(*graph)[i].vertexID=i+1;
		(*graph)[i].explored=FALSE;
		(*graph)[i].key=100000;
		(*graph)[i].numbOfEdges=0;
		(*graph)[i].vtx=NULL;
	}

	// ------- Add vertex to the Graph -------
	rewind(fp);
	while(fgets(line,sizeof(line),fp)!=NULL){
		numbersInLine=getNumbersFromString(line,arrayNumber);
		for(j=1;j<numbersInLine;j=j+2){
			addVertex(*graph,arrayNumber[0],arrayNumber[j],arrayNumber[j+1]);
		}
	}

	return 0;
}
int updateNeighbors(tVERTEX *vertex){


}

int dijkstraPath(tVERTEX* graph, int vertexNumber, int startIndex){
	tVERTEX *X[vertexNumber],*V[vertexNumber];
	int i=0,j,Xsize=0, Vsize=vertexNumber,newEntryNumEdges;
	tEDGE *tempEdge;

	X[i]=&graph[startIndex];
	newEntryNumEdges=graph[startIndex].numbOfEdges;

	/* Explore all the edges connected to new edge */
	tempEdge=X[i]->vtx;
	for(j=0;j<newEntryNumEdges;j++){
		updateNeighbors(tempEdge->vertex);
		tempEdge=tempEdge->next;
	}

}

int main(int argc, char const *argv[])
{
	FILE *fp;
	char fileName[50];
	int vertexNumber=0, i;
	tVERTEX* graph, **expN,**unexpN;

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

	printGraph(graph,vertexNumber);

	return 0;
}