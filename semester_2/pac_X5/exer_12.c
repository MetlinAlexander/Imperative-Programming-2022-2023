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

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct Edge_s{
    int a;
    int b;
    long long int cost;
}Edge;

long long int INF = 6000000000000000001;

long long int* dist;
int* parents;
char* negative_cycles;

void find_neg_cycles(int s, Edge* graphs, int n, int m){
    for(int i=1; i<n+1;i++){
        dist[i] = INF;
        parents[i]=-1;
        negative_cycles[i] = 'f';
    }
    dist[s] =0;
    //run Belman Ford algoritm
    for(int i=0; i<n-1; i++){
        for(int j=0; j<m;j++){
            if(dist[graphs[j].a]!=INF){
                if(dist[graphs[j].b] > (dist[graphs[j].a] + graphs[j].cost)){
                    dist[graphs[j].b] = MAX(-INF, dist[graphs[j].a] + graphs[j].cost);
                    parents[graphs[j].b] = graphs[j].a;
                }
            }
        }
    }
    //check for negative cycles
    int v, u;
    for(int j=0; j<m;j++){
        if(dist[graphs[j].b] > (dist[graphs[j].a] + graphs[j].cost)){
            v= graphs[j].b;
            for(int i=0; i<n-1; i++){
                v = parents[v];
                if(v==-1) break;
            }
            if(v==-1) continue;
            u = v;
            while(u!=parents[v]){
                dist[v] = -INF;
                negative_cycles[v] = 't';
                v = parents[v];
                if(v==-1) break;
            }
        }
    }
}

char* mark;
//check vertex that can be reached from hegative cycles
void DFS(int u, array_int* graph){
    mark[u] = 'g';
    negative_cycles[u] = 't';
    int v;
    for(int i=0; i<graph[u].n; i++){
        v = graph[u].arr[i];
        if(mark[v] == 'w'){
            DFS(v, graph);
        }
    }
    mark[u] = 'b';
}


int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan data
    int n, m, start; fscanf(in, "%d %d %d", &n, &m, &start);
    //scan edges
    Edge* roads = (Edge*) malloc(sizeof(Edge)*m);
    array_int* adj_list = (array_int*) malloc(sizeof(array_int)*(n+1));
    for(int i=1; i<=n; i++){
        array_int_init(&adj_list[i]);
    }
    for(int i=0; i<m; i++){
        fscanf(in, "%d %d %lld", &roads[i].a, &roads[i].b, &roads[i].cost);
        array_int_push(&adj_list[roads[i].a], roads[i].b);
    }
    //find cycles negative
    dist = (long long int*) malloc(sizeof(long long int)*(n+1));
    parents = (int*) malloc(sizeof(int)*(n+1));
    negative_cycles = (char*) malloc(sizeof(char)*(n+1));
    find_neg_cycles(start, roads, n, m);
    //find vertex witn -INF 
    mark = (char*) malloc(sizeof(char)*(n+1));
    for(int i=1; i<n+1; i++){
        mark[i] = 'w';
    }
    for(int i=1; i<n+1; i++){
        if(negative_cycles[i]=='t' && mark[i]=='w'){
            DFS(i, adj_list);
        }
    }
    //print anwsers
    for(int i=1; i<n+1;i++){
        if( dist[i]==-INF || negative_cycles[i]=='t'){
            fprintf(out, "-\n", dist[i]);
            continue;
        }
        if(dist[i]==INF){
            fprintf(out, "*\n", dist[i]);
            continue;
        }
        fprintf(out, "%lld\n", dist[i]);
    }
    //free
    for(int i=1; i<=n;i++){
        array_int_destroy(&adj_list[i]);
    }
    free(adj_list);
    free(roads);
    free(dist);
    free(parents);
    free(negative_cycles);
    free(mark);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}