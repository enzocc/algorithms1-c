#define NUMBER_MAX_DIGIT 50
#define LINE_MAX_SIZE_CHAR 10000
#define LINE_MAX_SIZE_INT 10000

int printArray(int,long long*, char*);
int readArray(FILE*, int*, long long**);
int arraySwap(long long**, int, int);
int getNumbersFromString(char*, int *);
int getLinesInFile(FILE*);
int getNumFromFile(FILE*);


typedef int bool;
#define	TRUE	1
#define	FALSE	0