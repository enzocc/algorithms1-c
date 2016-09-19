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
	struct dVERTEX* leader;
	struct dEDGE* fwd;	//List of vertex in direct order
	struct dEDGE* bwd;	//List of vertex in reverse order
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

int DFS(tVERTEX* node,int* globalTime, tVERTEX* leader, tVERTEX **orderArray, bool reverse){
	tEDGE* e;

	node->explored=TRUE;
	node->leader=leader;
	if(reverse)
		e=node->bwd;
	else
		e=node->fwd;
	while(e){//For all the edges
		if(!(e->vertex->explored)){//if nor explored
			DFS(e->vertex,globalTime,leader,orderArray,reverse);//Recurse DFS
		}
		e=e->next;
	}
	
	(*globalTime)++;	// During the reverse execution, it indicates the ending order.
						// In the direct execution, it counts the number of items belonging to the leader
	if(reverse)
		orderArray[*globalTime-1]=node;//Only write in the orderArray, if we are executing in reverse mode

	return 0;
}

int DFS_Loop(tVERTEX* graph, int vertexNumber, tVERTEX **orderArray, bool reverse){
	int globalEndTime=0,i;
	tVERTEX* leader=NULL;

	if(reverse){
		for(i=vertexNumber-1;i>=0;i--)
			if(!graph[i].explored){
				leader=&graph[i];
				DFS(&graph[i],&globalEndTime,leader,orderArray,reverse);
			}
	}
	else{
		for(i=vertexNumber-1;i>=0;i--)
			if(!orderArray[i]->explored){
				leader=orderArray[i];
				globalEndTime=0;	//Restart to zero before discovering the nodes belonging to the leader.
				DFS(orderArray[i],&globalEndTime,leader,orderArray,reverse);
				//The following condition is used to print the biggest groups of nodes (minimum 150 elements)
				if(globalEndTime>150)
					printf("Leader: %d - Number Nodes: %d\n", leader->vertexID,globalEndTime);
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
	tVERTEX* graph, **orderArray;

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

	orderArray=(tVERTEX**) malloc(vertexNumber*sizeof(tVERTEX*));

	// ------- Launch routine in reverse order -------
	DFS_Loop(graph,vertexNumber,orderArray,TRUE);

	// ------- Restart all nodes as Non-Explored -------
	for(i=0;i<vertexNumber;i++)
		orderArray[i]->explored=FALSE;
	
	// ------- Launch routine in direct order -------
	DFS_Loop(graph,vertexNumber,orderArray,FALSE);

//	printGraph(graph, vertexNumber);

/*	printf("Order Array: ");
	for(i=0;i<vertexNumber;i++){
		printf("%d ", orderArray[i]->vertexID);
	}
	printf("\n");*/

	return 0;
}