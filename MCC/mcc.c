#include "stdio.h"
#include "stdlib.h"
#include "utilities.h"

typedef struct dEDGE
{
	struct dVERTEX* headVertex;
	struct dVERTEX* tailVertex;
	struct dEDGE* nextEdge;
} tEDGE;

typedef struct dVERTEX
{
	int vertexID;
	bool explored;
	int numbOfEdges;
	int finishTime;
	struct dVERTEX* leader;
	struct dEDGE* firstEdge;
} tVERTEX;

int printGraph(tVERTEX *graph, int vertexCount){
	int i;
	tEDGE *e;
    for(i=0;i<vertexCount;i++)
    {
        printf("%d (%d)",graph[i].vertexID, graph[i].numbOfEdges);
        e=graph[i].firstEdge;
        while(e)
        {
            printf("->%d",e->tailVertex->vertexID);
            e=e->nextEdge;
        }
       	printf("\n");
    }
    return 0;
}

int DFS(tVERTEX* node,int* globalTime, tVERTEX* leader){
	tEDGE* e;

	node->explored=TRUE;
	node->leader=leader;
	e=node->firstEdge;
	while(e){
		if(!(e->tailVertex->explored)){
			DFS(e->tailVertex,globalTime,leader);
		}
		e=e->nextEdge;
	}
	(*globalTime)++;
	node->finishTime=(*globalTime);

	return 0;
}

int DFS_Loop(tVERTEX* graph, int vertexNumber){
	int globalEndTime=0,i;
	tVERTEX* leader=NULL;

	for(i=vertexNumber-1;i>=0;i--){
		if(!graph[i].explored){
			leader=&graph[i];
			DFS(&graph[i],&globalEndTime,leader);
		}
	}
	return 0;
}

/* The following function add the edge edgeID
 * to the vertex vertexID in the graph
 */
int addVertex(tVERTEX* graph, int vertexID, int edgeID){
	tEDGE *e,*e1;

	e=graph[vertexID-1].firstEdge;
	while(e && e->nextEdge)
		e=e->nextEdge;

	e1=malloc(sizeof(tEDGE));
	e1->headVertex=&graph[vertexID-1];
	e1->tailVertex=&
	graph[edgeID-1];
	e1->nextEdge=NULL;
	if(e)
		e->nextEdge=e1;
	else
		graph[vertexID-1].firstEdge=e1;

	graph[vertexID-1].numbOfEdges++;
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
		(*graph)[i].firstEdge=NULL;
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
	printGraph(graph, vertexNumber);

	return 0;
}