#define MAXLIST 10

typedef char String[21];

int Search(String key, String A[], int nElem);
int setUnion(String *A, String *B, String *C, int nElemA, int nElemB);
int intersect(String A[], String B[], String C[], int nElemA, int nElemB);
int setDiff(String A[], String B[], String C[], int nElemA, int nElemB);
int substringList(String key, String B[], String C[], int nElemB);