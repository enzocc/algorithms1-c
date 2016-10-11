typedef struct heap{
	int lastIndex;
	int maxSize;
	tVERTEX** hElem;
} tHeap;

int bubbleDown(tHeap*, int);
tVERTEX* heapDelete(tHeap*, int);
tVERTEX* heapGet(tHeap*);
int heapInsert(tHeap*, tVERTEX*);
int heapify(tHeap*);