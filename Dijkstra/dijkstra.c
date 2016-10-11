#ifndef LIBDEF
	#define LIBDEF
	#include "stdio.h"
	#include "stdlib.h"
	#include "utilities.h"
	#include "heap.h"
#endif

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
		(*graph)[i].key=100000;
		(*graph)[i].explored=FALSE;
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

int dijkstraPath(tVERTEX* graph, int vertexNumber){
	tVERTEX *X[vertexNumber], *V[vertexNumber-1], *tempVertex;
	tHeap vertexHeap;
	int i=0,j,Xsize=0, newEntryNumEdges;
	tEDGE *tempEdge;

	/* Copy graph[0] to array X (explored) */
	X[i]=&graph[0];
	X[i]->key=0;
	X[i]->explored=TRUE;
	newEntryNumEdges=graph[0].numbOfEdges;
	/* Copy other vertex addresses to array V (unexplored) */
	for(j=0;j<vertexNumber-1;j++){
		V[j]=&graph[j+1];
		V[j]->order=j;
	}

	/* Explore all the edges connected to new edge and update key*/
	tempEdge=X[i]->vtx;
	while(tempEdge!=NULL){
		tempEdge->vertex->key = tempEdge->length;
		tempEdge=tempEdge->next;
	}
	/* Create a heap */
	vertexHeap.lastIndex=vertexNumber-2;
	vertexHeap.maxSize=vertexNumber-1;
	vertexHeap.hElem=V;
	heapify(&vertexHeap);
	// ------------------------------
	for(i=1;i<vertexNumber;i++){
		X[i] = heapGet(&vertexHeap);
		X[i]->explored=TRUE;
		/* Explore all the edges connected to new edge and update key*/
		tempEdge=X[i]->vtx;
		while(tempEdge!=NULL){
			if(tempEdge->vertex->explored==FALSE){
				tempVertex=heapDelete(&vertexHeap,tempEdge->vertex->order);
				if(tempVertex->key>X[i]->key+tempEdge->length)
					tempVertex->key=X[i]->key+tempEdge->length;
				heapInsert(&vertexHeap,tempVertex);
			}
			tempEdge=tempEdge->next;
		}
	}

	printf("Distance of 7 is %d\n", graph[6].key);
	printf("Distance of 37 is %d\n", graph[36].key);
	printf("Distance of 59 is %d\n", graph[58].key);
	printf("Distance of 82 is %d\n", graph[81].key);
	printf("Distance of 99 is %d\n", graph[98].key);
	printf("Distance of 115 is %d\n", graph[114].key);
	printf("Distance of 133 is %d\n", graph[132].key);
	printf("Distance of 165 is %d\n", graph[164].key);
	printf("Distance of 188 is %d\n", graph[187].key);
	printf("Distance of 197 is %d\n", graph[196].key);
	return 0;
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

	//printGraph(graph,vertexNumber);
	dijkstraPath(graph,vertexNumber);

	return 0;
}