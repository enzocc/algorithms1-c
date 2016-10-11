#define NUMBER_MAX_DIGIT 50
#define LINE_MAX_SIZE_CHAR 10000
#define LINE_MAX_SIZE_INT 10000

typedef int bool;
#define	TRUE	1
#define	FALSE	0

typedef struct dEDGE
{
	struct dVERTEX* vertex;
	int length;
	struct dEDGE* next;
} tEDGE;

typedef struct dVERTEX
{
	int vertexID;
	int numbOfEdges;
	bool explored;
	int key;
	int order;
	struct dEDGE* vtx;
} tVERTEX;

int printArray(int,int*, char*);
int readArray(FILE*, int*, int**);
int arraySwap(tVERTEX**, int, int);
int getNumbersFromString(char*, int *);