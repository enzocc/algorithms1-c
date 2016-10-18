typedef struct heap{
	int lastIndex;
	int maxSize;
	int* hElem;
} tHeap;

int bubbleDown(tHeap*, int, bool);
int heapDelete(tHeap*, int, bool);
int heapGet(tHeap*, bool);
int heapInsert(tHeap*, int, bool);
int heapify(tHeap*, bool);