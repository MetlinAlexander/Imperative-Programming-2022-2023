#include <stdio.h>
#include <stdlib.h>



//Рассщиряющийся массив-----------
# define TYPE int
# define NAME array_int

#define REALLYCONCAT(P, S) P##S
#define CONCAT(Prefix, Suffix) REALLYCONCAT(Prefix, Suffix)

typedef struct NAME{
    int n;     // number of elements in array
    TYPE *arr; // points to the array of elements
    // any other members can be added here
    int camp; // how many space we have at all  
} NAME;

// initializes members of [vec] structure for empty array
void CONCAT(NAME, _init)(NAME *vec){
    vec->n = 0;
    vec->camp = 2;
    vec->arr = (TYPE*) malloc(sizeof(TYPE)*vec->camp);
}

// makes array [vec] empty and frees its array buffer [vec->arr]
// note: this function can be called many times
void CONCAT(NAME, _destroy)(NAME *vec){
    if(vec->arr != NULL){
        vec->n = 0;
        vec->camp = 0;
        free(vec->arr);
        vec->arr = NULL;
    }
}

// adds element [value] to the end of array [vec]
// returns index of the added element
int CONCAT(NAME, _push)(NAME *vec, TYPE value){
    //if arr wasnt allocate
    if(vec->camp == 0){
        CONCAT(NAME, _init)(vec);
    }
    //check if enough space in arr
    if(vec->n == vec->camp){
        //otherwise
        vec->camp *= 2;
        vec->arr = (TYPE*) realloc(vec->arr, (vec->camp)*sizeof(TYPE));
    }
    vec->arr[vec->n] = value;
    vec->n += 1;
    return vec->n - 1;
}

// removes the last element from array [vec]
// returns removed element
TYPE CONCAT(NAME, _pop)(NAME *vec){
    vec->n -= 1;
    TYPE temp = vec->arr[vec->n];
    return temp;
}
//------------------------------------------------------------

// int INF = 2147483646;
int INF = 2000000000;

int** next;

void floyd(int n, int** matrix){
    for(int i=1; i<n+1;i++){
        for(int u=1; u<n+1; u++){
            for(int v=1; v<n+1; v++){
                if(u==v){
                    continue;
                }
                if(matrix[u][i]!=INF && matrix[i][v]!=INF && matrix[u][v]!=0){
                    if( (matrix[u][i]+matrix[i][v]) < matrix[u][v]){
                        matrix[u][v] = matrix[u][i]+matrix[i][v];
                        next[u][v] = next[u][i];
                    }
                }
                    
            }
        }
    }
}

array_int* way;
//return len u -> v
int getshortest_len(int u, int v, int** matrix){
    // между вершинами u и v нет пути
    if(matrix[u][v]==INF){
        return INF ;
    }
    // если путь есть возвращаем длину пути
    return matrix[u][v];
}
//return way u -> v
void getshortestpath(int u, int v, int** matrix, array_int* way){
    // если путь есть возвращаем длину пути и кладем в way путь
    int c=u;
    while (c!=v){
        array_int_push(way, c);
        c = next[c][v];
    }
    array_int_push(way, v);
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //input data
    int n, m; // N-vertex; M- edges
    int p, k; // P - requests for min road ; K - request for min time
    fscanf(in, "%d %d %d %d", &n, &m, &p, &k);
    //create adjacency matrix and scan edges
    int** matrix = (int**) malloc(sizeof(int*)*(n+1));
    next = (int**) malloc(sizeof(int*)*(n+1));
    for(int i=1; i<n+1; i++){
        matrix[i] = (int*) malloc(sizeof(int)*(n+1));
        next[i] = (int*) malloc(sizeof(int)*(n+1));
        for(int j=1; j<n+1;j++){
            if(i==j){
                matrix[i][j] = 0;
                next[i][j] = i;
                continue;
            }
            matrix[i][j] = INF;
        }
    }
    
    int from, to, weith;
    for(int i=0; i<m;i++){
        fscanf(in, "%d %d %d", &from, &to, &weith);
        if(weith<matrix[from][to]){
            matrix[from][to] = weith;
            matrix[to][from] = weith;
            next[from][to] = to;
            next[to][from] = from;
        }
    }
    //run floud algo
    floyd(n, matrix);
    //solve request p
    array_int way; 
    for(int i=0; i<p;i++){
        fscanf(in, "%d %d", &from, &to);
        fprintf(out, "%d ", getshortest_len(from, to, matrix));

        array_int_init(&way);
        
        getshortestpath(from, to, matrix, &way);
        fprintf(out, "%d ", way.n);
        for(int j=0; j<way.n;j++){
            fprintf(out, "%d ", way.arr[j]);
        }
        fprintf(out, "\n");
        array_int_destroy(&way);
    }
    //solve request k
    for(int i=0; i<k;i++){
        fscanf(in, "%d %d", &from, &to);
        fprintf(out, "%d\n", getshortest_len(from, to, matrix));
    }
    //free
    for(int i=1; i<n+1;i++){
        free(next[i]);
        free(matrix[i]);
    }
    free(matrix);
    free(next);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}