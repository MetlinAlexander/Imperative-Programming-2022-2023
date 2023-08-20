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
        vec->arr = realloc(vec->arr, (vec->camp)*sizeof(TYPE));
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
    for(int i=1; i<=n;i++){
        for(int j=0; j<adj_list[i].n;j++){
        }
    }
    //solve
    int* length = (int*) malloc(sizeof(int)*(n+1));
    for(int i=0; i<n+1; i++){
        length[i] = -1;
    }
    int* queue = (int*) malloc(sizeof(int)*n);
    int cur=0, put=0;
    //bfs
    length[1] = 0; 
    queue[0] = 1;
    put = 1;
    int u, v;
    while(cur<put){
        //извлекаем вершину из начала очереди
        u = queue[cur];
        cur++;
        for(int i=0; i<adj_list[u].n;i++){
            v = adj_list[u].arr[i];
            if(length[v]==-1) { //будем считать, что dist == -1 для непосещённых вершин
                queue[put] = v;
                put++;
                length[v] = length[u]+1;
            }
        }
    }
    //print answer
    for(int i=1; i<n+1;i++){
        fprintf(out, "%d\n", length[i]);
    }
    //free space
    for(int i=1; i<=n;i++){
        array_int_destroy(&adj_list[i]);
    }
    free(adj_list);
    free(length);
    free(queue);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}