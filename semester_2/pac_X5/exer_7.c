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
    int cost;
}Edge;

int INF = 2000000000;

int* dist;
int* parent;

void fordBellman(int s, Edge* graphs, int n, int m){
    for(int i=1; i<n+1;i++){
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[s] = 0;
    for(int i=0; i<n-1; i++){
        for(int j=0; j<m;j++){
            if(dist[graphs[j].b] > (dist[graphs[j].a] + graphs[j].cost)){
                dist[graphs[j].b] = dist[graphs[j].a] + graphs[j].cost;
                parent[graphs[j].b] = graphs[j].a;
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
    int friends[55];
    for(int i=0; i<k; i++){
        fscanf(in, "%d", &friends[i]);
    }
    //scan edges
    Edge* roads = (Edge*) malloc(sizeof(Edge)*m);
    for(int i=-0; i<m; i++){
        fscanf(in, "%d %d %d", &roads[i].a, &roads[i].b, &roads[i].cost);
    }
    //solve
    dist = (int*) malloc(sizeof(int)*(n+1));
    parent = (int*) malloc(sizeof(int)*(n+1));
    fordBellman(1, roads, n, m);
    array_int way;
    //print anwsers
    for(int i=0; i<k;i++){
        fprintf(out, "%d ", dist[friends[i]]);
        array_int_init(&way);

        //recreate way
        for(int j=friends[i]; j!=-1; j=parent[j]){
            array_int_push(&way, j);
        }
        fprintf(out, "%d ", way.n);
        for(int j=way.n-1; j>=0;j--){
            fprintf(out, "%d ", way.arr[j]);
        }
        fprintf(out, "\n");
        array_int_destroy(&way);
    }
    //free
    free(roads);
    free(dist);
    free(parent);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}