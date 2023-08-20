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


int index_in_top_sort=0;
char* mark;
int* top_sort;
//for topological sort
void DFS_for_toplogical_sort(int u, array_int* graph) {
    mark[u] = 'g';
    int v;
    for(int i=0; i<graph[u].n; i++){
        v = graph[u].arr[i];
        if(mark[v] == 'w'){
            DFS_for_toplogical_sort(v, graph);

        }
    }
    mark[u] = 'b';
    top_sort[index_in_top_sort] = u;
    index_in_top_sort--;
}

int cur_componet=0;
int* components;
//for topological sort
void DFS_for_componet(int u, array_int* graph) {
    mark[u] = 'g';
    components[u] = cur_componet;
    // printf("%d %d\n", components[u], u);
    int v;
    for(int i=0; i<graph[u].n; i++){
        v = graph[u].arr[i];
        if(mark[v] == 'w'){
            DFS_for_componet(v, graph);

        }
    }
    mark[u] = 'b';
}


int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan data
    int n, m; fscanf(in, "%d %d", &n, &m);
    //create adjacency list and scan edges
    array_int* adj_list = (array_int*) malloc(sizeof(array_int)*(n+1));
    array_int* trans_graph = (array_int*) malloc(sizeof(array_int)*(n+1));
    for(int i=1; i<=n; i++){
        array_int_init(&adj_list[i]);
        array_int_init(&trans_graph[i]);
    }
    int from, to;
    for(int i=0; i<m;i++){
        fscanf(in, "%d %d", &from, &to);
        array_int_push(&adj_list[from], to);
        array_int_push(&trans_graph[to], from);
    }
    //toplogical sort on graph
    mark = (char*) malloc(sizeof(int)*(n+1));
    for(int i=1; i<n+1;i++){
        mark[i] = 'w';
    }
    index_in_top_sort = n-1;
    top_sort = (int*) malloc(sizeof(int)*n);
    for(int i=1; i<n+1;i++){
        if(mark[i]=='w'){
            DFS_for_toplogical_sort(i, adj_list);
        }
    }
    //find componets using trans graph
    components = (int*) malloc(sizeof(int)*(n+1));
    for(int i=1; i<n+1;i++){
        mark[i] = 'w';
    }
    for(int i=0; i<n;i++){
        if(mark[top_sort[i]]=='w'){
            cur_componet++;
            DFS_for_componet(top_sort[i], trans_graph);
        }
    }
    //print answer
    fprintf(out, "%d\n", cur_componet);
    for(int i=1; i<n+1; i++){
        fprintf(out, "%d ", components[i]);
    }
    //free space
    for(int i=1; i<=n;i++){
        array_int_destroy(&adj_list[i]);
        array_int_destroy(&trans_graph[i]);
    }
    free(adj_list);
    free(top_sort);
    free(components);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}