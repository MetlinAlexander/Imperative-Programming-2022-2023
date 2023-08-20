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
int INF = 1000000000;


int time;
int* t_in;
int* fun_up;
char* mark;
array_int* list_of_num_edges;

int num_edges=0;
char* is_articulation_edge;

void DFS(int v, int parent, array_int* graph){
    mark[v] = 'b';
    t_in[v] = time;
    fun_up[v] = time;
    time++;
	int to, count;
    for(int i=0; i<graph[v].n; i++){
        to = graph[v].arr[i];
        if(to==parent) continue;
        if(mark[to]=='b'){
            if(fun_up[v]>t_in[to]){
                fun_up[v] = t_in[to];
            }
        }else{
            DFS(to, v, graph);
            if(fun_up[v]>fun_up[to]){
                fun_up[v] = fun_up[to];
            }
            if(fun_up[to]>t_in[v]){
                if(is_articulation_edge[list_of_num_edges[v].arr[i]]=='f'){
                    count=0;
                    for(int j=0; j<graph[v].n; j++){
                        if(graph[v].arr[j]==to) count++;
                    }
                    if(count>1) continue;
                    is_articulation_edge[list_of_num_edges[v].arr[i]] = 't';
                    num_edges++;
                }
            }
        }
    }
    if(parent!=-1 && t_in[v]==fun_up[v]){
        count=0;
        for(int j=0; j<graph[parent].n; j++){
            if(graph[parent].arr[j]==v) count++;
        }
        if(count>1) return;
        for(int j=0; j<graph[parent].n; j++){
            if(graph[parent].arr[j]==v){
                is_articulation_edge[list_of_num_edges[parent].arr[j]] = 't';
                num_edges++;
            }
        }
        
    }
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan data
    int n, m; fscanf(in, "%d %d", &n, &m);
    //create adjacency list and scan edges
    array_int* adj_list = (array_int*) malloc(sizeof(array_int)*(n+1));
    list_of_num_edges = (array_int*) malloc(sizeof(array_int)*(n+1));
    for(int i=1; i<=n; i++){
        array_int_init(&adj_list[i]);
        array_int_init(&list_of_num_edges[i]);
    }
    int from, to;
    for(int i=1; i<m+1;i++){
        fscanf(in, "%d %d", &from, &to);
        if(from==to) continue;
        array_int_push(&adj_list[from], to);
        array_int_push(&adj_list[to], from);
        array_int_push(&list_of_num_edges[from], i);
        array_int_push(&list_of_num_edges[to], i);
        // arr
        // printf("%d <-> %d\n", from, to);
    }
    //solve
    time =0;
    t_in = (int*) malloc(sizeof(int)*(n+1));
    fun_up = (int*) malloc(sizeof(int)*(n+1));
    mark = (char*) malloc(sizeof(char)*(n+1));
    is_articulation_edge = (char*) malloc(sizeof(char)*(m+1));
    for(int i=1;i<n+1;i++){
        mark[i] = 'w';
        is_articulation_edge[i] = 'f';
        t_in[i] = INF;
        fun_up[i] =INF;
    }
    int v;
    for(int i=1; i<n+1; i++){
        v = i;
        if(mark[v]=='w'){
            DFS(v, -1, adj_list);
        }
    }
    //print answer
    fprintf(out, "%d\n", num_edges);
    for(int i=1; i<n+1; i++){
        if(is_articulation_edge[i]=='t') 
            fprintf(out, "%d ", i);
    }
    //free
    for(int i=1; i<=n;i++){
        array_int_destroy(&adj_list[i]);
        array_int_destroy(&list_of_num_edges[i]);
    }
    free(list_of_num_edges);
    free(adj_list);
    free(t_in);
    free(fun_up);
    free(mark);
    free(is_articulation_edge);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}