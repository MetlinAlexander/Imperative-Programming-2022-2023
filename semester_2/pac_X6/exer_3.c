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
int INF = 2100000000;
//  c(u, v) --- пропускная способность трубы из u в v (0 если трубы нет)
//   f(u, v) --- величина потока по трубе из u в v
int** c;
int** f;
int* parent;
char* mark;
int* queue;
int cur=0, put=0;
int answer_flow=0;

void max_flow(int s, int t, int n, int k){
    int flow=0;
    for(int i=0; i<n+1; i++){
        parent[i]=-1;
    }
    mark = (char*) malloc(sizeof(char)*(n+1));
    queue = (int*) malloc(sizeof(int)*(100000));
    int u, v;
    int CP;
    int x, y;
    while(1){
        for(int i=0; i<n+1; i++){
            mark[i]='f';
        }
        cur=0, put=0;
        mark[s] = 't';
        queue[put] = s;
        put++;
       
        while (cur<put){
            //извлекаем вершину из начала очереди
            u = queue[cur];
            cur++;
            for(v=1; v<n+1; v++){
                if(c[u][v]==0) continue;
                if( c[u][v] - f[u][v] > 0){// проверяем cf(uv) -- остаточную проп. спос-сть
                    if (mark[v]=='f'){
                        mark[v] = 't';
                        queue[put] = v;
                        put++;
                        parent[v] = u;
                    }  
                }
                if(v==t) break;      
            }
        }
        if (mark[t]=='f'){ // нет дополняющего пути
            break;
        }
        // part 2: how much?
        CP = INF;
        x = t;
        while(x!=s){  // восстанавливаем путь P первый раз
            y = parent[x];
            CP = MIN(CP, c[y][x]- f[y][x]);
            x = y;
        }
         // part 3: push flow
        x = t;
        while( x != s){               // восстанавливаем путь P второй раз
            y = parent[x];
            f[y][x] += CP;
            f[x][y] -= CP;               // не забываем поменять поток по обратному ребру!
            x = y;
        }
        answer_flow += CP;
    }
    free(mark);
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan data
    int n, k; fscanf(in, "%d %d", &n, &k);
    // init
    c = (int**) malloc(sizeof(int*) * (n+1));
    f = (int**) malloc(sizeof(int*) * (n+1));
    for(int i=0; i<n+1; i++){
        c[i] = (int*) malloc(sizeof(int)*(n+1));
        f[i] = (int*) malloc(sizeof(int)*(n+1));
        for(int j=0; j<n+1; j++){
            c[i][j] =0;
            f[i][j] =0;
        }
    }
    parent = (int*) malloc(sizeof(int)*(n+1));
    //scan graph
    int from, to, flow_cap;
    for(int i=0; i<k; i++){
        fscanf(in, "%d %d %d", &from , &to , &flow_cap);
        c[from][to] = flow_cap;
        c[to][from] = flow_cap;
    }
    //find max flow
    max_flow(1, n, n, k);
    fprintf(out, "%d\n", answer_flow);
    //free
    for(int i=0; i<n+1; i++){
        free(c[i]);
        free(f[i]);
    }
    free(c);
    free(f);
    free(parent);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}