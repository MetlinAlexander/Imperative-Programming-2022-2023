#define REALLYCONCAT(P, S) P##S
#define CONCAT(Prefix, Suffix) REALLYCONCAT(Prefix, Suffix)

// #define LIST CONCAT(List_, TYPE)

typedef struct NAME{
    int n;     // number of elements in array
    TYPE *arr; // points to the array of elements
    // any other members can be added here
    int camp; // how many space we have at all  
} NAME;


void CONCAT(NAME, _init)(NAME *vec);
void CONCAT(NAME, _destroy)(NAME *vec);
int CONCAT(NAME, _push)(NAME *vec, TYPE value);
TYPE CONCAT(NAME, _pop)(NAME *vec);
void CONCAT(NAME, _reserve)(NAME *vec, int capacity);
void CONCAT(NAME, _resize)(NAME *vec, int newCnt, TYPE fill);
void CONCAT(NAME, _insert)(NAME *vec, int where, TYPE *arr, int num);
void CONCAT(NAME, _erase)(NAME *vec, int where, int num);
