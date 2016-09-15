#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "limits.h"

#include "utilities.h"

struct VERTEX;

typedef struct EDGE
{
	int vertexID;
	struct EDGE *nextEdge;
} tEDGE;

typedef struct VERTEX
{
	int vertexID;
	bool enable;
	int numberEdges;
	struct EDGE* firstEdge;
} tVERTEX;

int printGraph(tVERTEX *graph, int vertexCount){
	int i;
	tEDGE *e;
    for(i=0;i<vertexCount;i++)
    {
    	if(graph[i].enable){
        	printf("%d (%d)",graph[i].vertexID, graph[i].numberEdges);
        	e=graph[i].firstEdge;
        	while(e)
        	{
            	printf("->%d",e->vertexID);
            	e=e->nextEdge;
        	}
       		printf("\n");
       	}
    }
    return 0;
}

int selectRandomEdge(tVERTEX* graph, int doubleTotalEdges, int* vertexA, int* vertexB){
	int i=0,j=0,k, remaining=0, vertexToMerge=rand()%doubleTotalEdges;
	tEDGE* e;
	
	// In case vertexToMerge is Zero
	while(!graph[j].enable){
		j++;
	}
	*vertexA=graph[j].vertexID;
	*vertexB=graph[j].firstEdge->vertexID;

	while(i!=vertexToMerge){
		if(graph[j].enable){
			if((i+graph[j].numberEdges)<vertexToMerge){
				i=i+graph[j].numberEdges;
				j++;
			}
			else{
				remaining=vertexToMerge-i;
				*vertexA=graph[j].vertexID;
				e=graph[j].firstEdge;

				for(k=1;k<remaining;k++){
					e=e->nextEdge;
				}
				*vertexB=e->vertexID;
				i=i+remaining;
			}
		}
		else
			j++;
	}

	return vertexToMerge;
}

int countActiveVertex(tVERTEX* graph, int totalVertex){
	int i, count=0;
	for(i=0;i<totalVertex;i++){
		if(graph[i].enable)
			count++;
	}
	return count;
}

// Returns the total number of edges in the Graph array, or twice the total
// number of edges in the graph
int countDoubleEdges(tVERTEX* graph,int totalVertex){
	int i,count=0;
	for(i=0;i<totalVertex;i++){
		if(graph[i].enable){
			count=count+graph[i].numberEdges;
		}
	}
	return count;
}

int updateVertexName(tVERTEX *graph, int vertexCount, int oldValue, int newValue){
	int i;
	tEDGE *e;
    for(i=0;i<vertexCount;i++)
    {
    	if(graph[i].enable){
        	e=graph[i].firstEdge;
        	while(e){
        		if(e->vertexID == oldValue)
            		e->vertexID = newValue;
            	e=e->nextEdge;
        	}
       	}
    }
	return 0;    
}

int removeSelfLoop(tVERTEX *vertexToCheck){
	tEDGE *e;

	while(vertexToCheck->firstEdge->vertexID==vertexToCheck->vertexID){
		vertexToCheck->numberEdges--;//=vertexToCheck->numberEdges-1;
		vertexToCheck->firstEdge = vertexToCheck->firstEdge->nextEdge;
	}
	e=vertexToCheck->firstEdge;
	while(e && e->nextEdge){
		if(e->nextEdge->vertexID==vertexToCheck->vertexID){
			vertexToCheck->numberEdges--;//=vertexToCheck->numberEdges-1;
			e->nextEdge = e->nextEdge->nextEdge;
		}
		else
			e=e->nextEdge;
	}
	return 0;
}

int mergeVertex(tVERTEX *graph, int graphSize, int vertexA, int vertexB){
	tEDGE *eA;
	eA=graph[vertexA-1].firstEdge;
	while(eA && eA->nextEdge)		//Find the last element of the vertex array 
		eA=eA->nextEdge;

	eA->nextEdge=graph[vertexB-1].firstEdge;
	graph[vertexA-1].numberEdges=graph[vertexA-1].numberEdges+graph[vertexB-1].numberEdges;

	graph[vertexB-1].enable=FALSE;

	updateVertexName(graph, graphSize, vertexB, vertexA);
	removeSelfLoop(&graph[vertexA-1]);

	return 0;
}

int checkEdgeExist(tVERTEX* graph, int vertexA, int vertexB){
	tEDGE *e;
	e=graph[vertexA-1].firstEdge;
	while(e){
		if(e->vertexID==vertexB)
			return 1;
		e=e->nextEdge;
	}
	return 0;
}

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
	srand(time(NULL));

	min_Cut=INT_MAX;

	for(i=0;i<200;i++){
		readGraph(fp,&graph,&vertexNumber);
		//printGraph(graph, vertexNumber);

		activeVertexNumber=countActiveVertex(graph,vertexNumber);
		twiceEdgesNumber=countDoubleEdges(graph,vertexNumber);

		while(activeVertexNumber!=2){
			selectRandomEdge(graph,twiceEdgesNumber,&randVertexA,&randVertexB);
			mergeVertex(graph,vertexNumber,randVertexA,randVertexB);
			activeVertexNumber=countActiveVertex(graph,vertexNumber);
			twiceEdgesNumber=countDoubleEdges(graph,vertexNumber);
		}
		//printf("++++++ Final array:\n");
		//printGraph(graph, vertexNumber);
		free(graph);
		if(min_Cut>twiceEdgesNumber/2)
			min_Cut=twiceEdgesNumber/2;
	}
	printf("Min Cut has %d edges\n", min_Cut);

	return 0;
}