#include "stdio.h"
#include "stdlib.h"
#include "utilities.h"

typedef struct dEDGE
{
	struct dVERTEX* vertex;
	struct dEDGE* next;
} tEDGE;

typedef struct dVERTEX
{
	int vertexID;
	bool explored;
	int numbOfEdges;
	int finishTime;
	struct dVERTEX* leader;
	struct dEDGE* fwd;
	struct dEDGE* bwd;
} tVERTEX;

int printGraph(tVERTEX *graph, int vertexCount){
	int i;
	tEDGE *e;
    for(i=0;i<vertexCount;i++)
    {
        printf("%d (%d)",graph[i].vertexID, graph[i].numbOfEdges);
        e=graph[i].fwd;
        while(e)
        {
            printf("->%d",e->vertex->vertexID);
            e=e->next;
        }
       	printf("\n");
    }
    return 0;
}

int DFS(tVERTEX* node,int* globalTime, tVERTEX* leader, bool reverse){
	tEDGE* e;

	node->explored=TRUE;
	node->leader=leader;
	if(reverse)
		e=node->bwd;
	else
		e=node->fwd;
	while(e){
		if(!(e->vertex->explored)){
			DFS(e->vertex,globalTime,leader,reverse);
		}
		e=e->next;
	}
	(*globalTime)++;
	node->finishTime=(*globalTime);

	return 0;
}

int DFS_Loop(tVERTEX* graph, int vertexNumber, bool reverse){
	int globalEndTime=0,i;
	tVERTEX* leader=NULL;

	for(i=vertexNumber-1;i>=0;i--){
		if(!graph[i].explored){
			leader=&graph[i];
			DFS(&graph[i],&globalEndTime,leader,reverse);
		}
	}
	return 0;
}

/* The following function add the edge edgeID to the
 * fwd list of the vertex vertexID and the  vertex vertexID 
 * to the bwd list of the vertex edgeID
 */
int addVertex(tVERTEX* graph, int headVertex, int tailVertex){
	tEDGE *e,*e1;

	e=graph[headVertex-1].fwd;
	while(e && e->next)
		e=e->next;

	e1=malloc(sizeof(tEDGE));
	e1->vertex=&graph[tailVertex-1];
	e1->next=NULL;
	if(e)
		e->next=e1;
	else
		graph[headVertex-1].fwd=e1;
	
	e=graph[tailVertex-1].bwd;

	while(e && e->next)
		e=e->next;
	e1=malloc(sizeof(tEDGE));
	e1->vertex=&graph[headVertex-1];
	e1->next=NULL;
	if(e)
		e->next=e1;
	else
		graph[tailVertex-1].bwd=e1;

	graph[headVertex-1].numbOfEdges++;
	return 0;
}

int readGraph(FILE *fp, tVERTEX **graph, int* vertexNumber){
	int i=0, j, temp=0, arrayNumber[LINE_MAX_SIZE_CHAR];
	char *ret1, line[LINE_MAX_SIZE_INT];

	// ------- Find number of vertex in the Graph -------
	while(fgets(line,sizeof(line),fp)!=NULL){
		getNumbersFromString(line,arrayNumber);
		if(temp<arrayNumber[0])
			temp=arrayNumber[0];
		if(temp<arrayNumber[1])
			temp=arrayNumber[1];
	}
	(*vertexNumber)=temp;

	(*graph)=(tVERTEX*)malloc((*vertexNumber)*sizeof(tVERTEX));

	// ------- Add vertex to the Graph -------
	for(i=0;i<temp;i++){
		(*graph)[i].vertexID=i+1;
		(*graph)[i].explored=FALSE;
		(*graph)[i].numbOfEdges=0;
		(*graph)[i].finishTime=0;;
		(*graph)[i].leader=NULL;
		(*graph)[i].fwd=NULL;
		(*graph)[i].bwd=NULL;
	}

	// ------- Add vertex to the Graph -------
	rewind(fp);
	while(fgets(line,sizeof(line),fp)!=NULL){
		getNumbersFromString(line,arrayNumber);
		addVertex(*graph,arrayNumber[0],arrayNumber[1]);
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	FILE *fp;
	char fileName[50];
	int vertexNumber=0, i;
	tVERTEX* graph;

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

	DFS_Loop(graph,vertexNumber,TRUE);

//	printGraph(graph, vertexNumber);

	printf("Finish Time: ");
	for(i=0;i<vertexNumber;i++){
		printf("%d ", graph[i].finishTime);
	}
	printf("\n");
	
	return 0;
}