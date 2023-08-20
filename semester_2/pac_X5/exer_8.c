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

typedef struct Edge_s{
    int a;
    int b;
}Edge;

int INF = 2000000000;

int* dist;
int* parent;
char* mark;

void dijkstra(int s, int n, int** matrix){
    for(int i=0; i<n+1;i++){
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[s] = 0;
    mark[s] = 'g';
    int u, min;
    while(1){
        min = INF;
        u = 0;
        for(int i=1; i<n+1;i++){
            if(mark[i]=='g' && dist[i]<min){
                u = i;
                min = dist[i];
            }
        }
        if(u==0 || min == INF) break;
        mark[u] = 'b';
        for(int i=1; i<n+1; i++){
            if(matrix[u][i]!=INF){
                if(dist[i] > (dist[u]+matrix[u][i]) ){
                    dist[i]=dist[u]+matrix[u][i];
                    parent[i] = u;
                    mark[i] = 'g';
                }
            }
        }
    }
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan data
    int n, m, k; fscanf(in, "%d %d %d", &n, &m, &k);
    //scan vova's friends
    Edge requests[25];
    for(int i=0; i<k; i++){
        fscanf(in, "%d %d", &requests[i].a, &requests[i].b);
    }
    //create adjacency matrix and scan edges
    int** matrix = (int**) malloc(sizeof(int*)*(n+1));
    for(int i=1; i<n+1; i++){
        matrix[i] = (int*) malloc(sizeof(int)*(n+1));
        for(int j=1; j<n+1;j++){
            if(i==j){
                matrix[i][j] = 0;
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
        }
    }

    //solve
    dist = (int*) malloc(sizeof(int)*(n+1));
    parent = (int*)  malloc(sizeof(int)*(n+1));
    mark = (char*) malloc(sizeof(char)*(n+1));
    //print anwsers
    int len;
    int* way = (int*) malloc(sizeof(int)*(m+1));
    for(int i=0; i<k;i++){
        for(int j=0; j<n+1; j++){
            mark[j] = 'w';
        }
        dijkstra(requests[i].a, n, matrix);
        for(int j=1; j<n+1; j++){
            printf("%lld ", dist[j]);
        }
        printf("\n");
        if(dist[requests[i].b]==INF){
            fprintf(out, "NO\n");
            continue;
        }
        fprintf(out, "YES ");
        fprintf(out, "%d ", dist[requests[i].b]);
        //recreate way
        len=0;
        for(int j=requests[i].b; j!=-1; j=parent[j]){
            way[len] = j;
            len++;
        }
        fprintf(out, "%d ", len);
        for(int j=len-1; j>=0;j--){
            fprintf(out, "%d ", way[j]);
        }
        fprintf(out, "\n");
    }
    //free
    for(int i=1; i<n+1;i++){
        free(matrix[i]);
    }
    free(matrix);
    free(dist);
    free(parent);
    free(mark); 
    free(way);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}