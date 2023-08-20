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
int* parent;
array_int cycle_list;
//return 1 if cycle
int DFS(int u, array_int* graph) {
    mark[u] = 'g';
    int v;
    for(int i=0; i<graph[u].n; i++){
        v = graph[u].arr[i];
        if(mark[v] == 'w'){
            parent[v] = u;
            if(DFS(v, graph)==1){
                return 1;
            }
        }else
        if(mark[v] == 'g'){
            return 1;
        }
    }
    mark[u] = 'b';
    top_sort[index_in_top_sort] = u;
    index_in_top_sort--;
    return 0;
  }


int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan data
    int n, m; fscanf(in, "%d %d", &n, &m);
    //create adjacency list and scan edges
    array_int* adj_list = (array_int*) malloc(sizeof(array_int)*(n+1));
    for(int i=1; i<=n; i++){
        array_int_init(&adj_list[i]);
    }
    int from, to;
    for(int i=0; i<m;i++){
        fscanf(in, "%d %d", &from, &to);
        array_int_push(&adj_list[from], to);
    }
    //start dfs
    mark = (char*) malloc(sizeof(int)*(n+1));
    parent = (int*) malloc(sizeof(int)*(n+1));
    for(int i=1; i<n+1;i++){
        mark[i] = 'w';
        parent[i] = -1;
    }
    index_in_top_sort = n-1;
    top_sort = (int*) malloc(sizeof(int)*n);
    int cycle=0;
    for(int i=1; i<n+1;i++){
        if(mark[i]=='w'){
            if(DFS(i, adj_list)==1){
                //find cycle
                cycle=1;
                break;
            }
        }
    }
    if(cycle==1){
        fprintf(out, "NO\n", cycle_list.n);
        array_int_destroy(&cycle_list);
    }else{
        int* answer = (int*) malloc(sizeof(int)*(n+1));
        fprintf(out, "YES\n");
        for(int i=0; i<n;i++){
            answer[top_sort[i]] = i+1;
            // printf("%d ", top_sort[i]);
        }
        for(int i=1; i<n+1;i++){
            fprintf(out, "%d ", answer[i]);
        }
        free(answer);
    }
    //free space
    for(int i=1; i<=n;i++){
        array_int_destroy(&adj_list[i]);
    }
    free(adj_list);
    free(top_sort);
    free(parent);
    
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}