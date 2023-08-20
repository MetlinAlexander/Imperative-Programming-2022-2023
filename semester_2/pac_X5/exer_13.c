#include <stdio.h>
#include <stdlib.h>

typedef struct Edge_s{
    int a;
    int b;
    long long cost;
    int num;
}Edge;

//Рассщиряющийся массив-----------
# define TYPE Edge
# define NAME array_Edge

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
long long int* dist;
// heap
typedef struct Node_s{         //тип вершины бинарного дерева 
    int value;
}Node;

void swap(Node** heap, int ind_a, int ind_b);

// dist[ ]

void SiftUp(Node** heap, int index){
    //if this root
    if(index==0) return ;
    //parent == root
    if((index-1)<= 1){
        if(dist[heap[0]->value] > dist[heap[index]->value]){ //--------------------------------
            swap(heap, 0, index);
        }
        return ;
    }
    //otherwise
    int p_ind = (index-1)/2;
    // printf("%d %d\n", heap[p_ind]->value, heap[index]->value);
    if(dist[heap[p_ind]->value] > dist[heap[index]->value]){ //--------------------------------
        swap(heap, p_ind, index);
        SiftUp(heap, p_ind);
    }

}

void Add_to_Heap(int elem, Node** heap, int* lenHeap, int* parall_mass){
    heap[*lenHeap] = (Node*) malloc(sizeof(Node));
    heap[*lenHeap]->value = elem;
    parall_mass[elem] = *lenHeap;
    (*lenHeap)+=1;
    //siftup ...
    SiftUp(heap, (*lenHeap)-1);
}

void SiftDown(Node** heap, int index, int max_index){
    //index of sons
    int l_son = 2*index+1;
    int r_son = 2*index+2;
    // if no sons
    if(r_son >= max_index && l_son >= max_index){
        return ;
    }
    //if onlu left
    if(r_son >= max_index){
        if(dist[heap[l_son]->value]< dist[heap[index]->value]){ //--------------------------------
            swap(heap, l_son, index);
            SiftDown(heap, l_son, max_index);
        }
        return ;
    }
    //if only right
    if(l_son >= max_index){
        if(dist[heap[r_son]->value] < dist[heap[index]->value]){ //--------------------------------
            swap(heap, r_son, index);
            SiftDown(heap, r_son, max_index);
        }
        return ;
    }
    //otherwise
    int min;
    if(dist[heap[r_son]->value] < dist[heap[l_son]->value]){ //--------------------------------
        min = r_son;
    }else{
        min = l_son;
    }
    if(dist[heap[min]->value] < dist[heap[index]->value]){ //--------------------------------
        swap(heap, min, index);
        SiftDown(heap, min, max_index);
    }

}

void ExtractMin(Node** heap, int* len_of_heap){
    if(*len_of_heap==1){
        free(heap[0]);
        (*len_of_heap) -=1;
        return ;
    }
    //корень всегда имеет номер 0
    (*len_of_heap)-=1;
    swap(heap, 0, *len_of_heap); //меняем корень с самым правым листом (он является последним
    //удаляем этот лист
    free(heap[*len_of_heap]);
    //инвариант от корня к сыновьям может нарушаться, запускаем просеивание вниз
    SiftDown(heap, 0, (*len_of_heap)); 
}

//------------------------------------------------------------

long long INF = 900000000000000;

// Техническая проблема: при улучшении по ребру нужно уметь определять номер в куче для заданной вершины.
// Чтобы это делать, следует хранить взаимное соответствие позиций в куче и вершин графа:
int* heap2vert;           //heap2vert[k] --- номер вершины, расположенной на позиции k в куче
Node** vert2heap;           //vert2heap[v] --- позиция вершины v в куче
// Когда в куче элементы меняются местами, нужно сделать swap в обоих этих массивах.
void swap(Node** heap, int ind_a, int ind_b){
    int temp = heap[ind_a]->value;
    heap[ind_a]->value = heap[ind_b]->value;
    heap[ind_b]->value = temp;
    temp = heap2vert[heap[ind_a]->value];
    heap2vert[heap[ind_a]->value] = heap2vert[heap[ind_b]->value];
    heap2vert[heap[ind_b]->value] = temp;
}

// *** Алгоритм Дейкстры с кучей:
//   D[*] = +inf, D[s] = 0
//   H = {все вершины}                     //изначально кладём все вершины в кучу
//   while H is not empty:
//     u = H.extractmin                    //берём вершину из корня кучи и удаляем её
//     mark[u] = T
//     for uv in E:
//       if D[v] > D[u] + w(uv):
//         D[v] = D[u] + w(uv)
//         F[v] = u
//         siftUp(vert2heap[v])            //т.к. D[v] уменьшилось, просеиваем кучу вверх от v

Edge** parent;

void dijkstra(int s, int n, array_Edge* insides_list){
    for(int i=0; i<n+1;i++){
        dist[i] = INF;
        parent[i] = NULL;
    }
    dist[s] = 0;
    //create heap
    Node** vert2heap = (Node**) calloc((n+1), sizeof(Node*));  //массив элементов, в котором хранится куча
    int len = 0;
    //изначально кладём все вершины в кучу
    for(int i=1; i<n+1; i++){
        Add_to_Heap(i, vert2heap, &len, heap2vert);
    }
    //run until heap is not empty
    int u, v;
    while(len>0){
        //take min vertex
        u = vert2heap[0]->value;
        ExtractMin(vert2heap, &len);
        if(dist[u]==INF) break;
        for(int i=0; i<insides_list[u].n; i++){
            v = insides_list[u].arr[i].b;
            if(dist[v]> dist[u] + (long long int)(insides_list[u].arr[i].cost)){
                dist[v] = dist[u] + (long long int)(insides_list[u].arr[i].cost);
                parent[v] = &(insides_list[u].arr[i]);
                SiftUp(vert2heap, heap2vert[v]);
            }
        }
    }
    free(vert2heap);
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan data
    int n, m, k; fscanf(in, "%d %d %d", &n, &m, &k);
    //scan requests
    Edge requests[25];
    for(int i=0; i<k; i++){
        fscanf(in, "%d %d", &requests[i].a, &requests[i].b);
    }
    //scan edges
    array_Edge* insides_list = (array_Edge*) malloc(sizeof(array_Edge)*(n+1));
    for(int i=1; i<n+1; i++){
        array_Edge_init(&insides_list[i]);
    }
    int from, to;
    long long weith;
    Edge temp;
    for(int i=1; i<m+1;i++){
        fscanf(in, "%d %d %lld", &from, &to, &weith);
        if(from==to) continue;
        temp.a = from;
        temp.b = to;
        temp.cost = weith;
        temp.num = i;
        array_Edge_push(&insides_list[from], temp);
    }
    //solve
    dist = (long long int*) malloc(sizeof(long long int)*(n+1));
    parent = (Edge**) malloc(sizeof(Edge*)*(n+1));
    heap2vert = (int*) malloc(sizeof(int)*(n+1));
    //print anwsers
    int len;
    Edge* temp_edge;
    int* way = (int*) malloc(sizeof(int)*(m+1));
    for(int i=0; i<k; i++){
        dijkstra(requests[i].a, n, insides_list);
        if(dist[requests[i].b]==INF){
            fprintf(out, "DOOMED\n");
            continue;
        }
        fprintf(out, "quarantine ");
        fprintf(out, "%lld ", dist[requests[i].b]);
        //recreate way
        len=0;
        temp_edge = parent[requests[i].b];
        while(1){
            if(temp_edge==NULL) break;
            way[len] = (*temp_edge).num;
            len++;
            temp_edge = parent[(*temp_edge).a];
        }
        fprintf(out, "%d ", len);
        for(int j=len-1; j>=0;j--){
            fprintf(out, "%d ", way[j]);
        }
        fprintf(out, "\n");
    }
    //free
    for(int i=1; i<n+1;i++){
        array_Edge_destroy(&insides_list[i]);
    }
    free(dist);
    free(parent);
    free(heap2vert);
    free(insides_list);
    free(way);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}