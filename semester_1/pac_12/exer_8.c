#include <stdio.h>
#include <stdlib.h>

int global_rez = 1;
// struct for every node
typedef struct node_s{
    int vertex;
    struct node_s* next;
}node;

//struct for whole graph 
typedef struct Graph_s{
    int numVertices;
    node** adjLists;
}Graph;

//init graph
void init_Graph ( Graph * myGraph ){
    for(int i=0; i<myGraph->numVertices; i++){
        myGraph->adjLists[i] = (node*) malloc(sizeof(node));
        myGraph->adjLists[i]->vertex = i+1;
        myGraph->adjLists[i]->next = NULL;
    }
}
// add new edges to the adj list
void addEdges(Graph * myGraph, int from, int to){
    node* temp = myGraph->adjLists[from-1]->next;
    myGraph->adjLists[from-1]->next = (node*) malloc(sizeof(node));
    myGraph->adjLists[from-1]->next->vertex = to;
    myGraph->adjLists[from-1]->next->next = temp;
}
    
//print graph
void printGraph(Graph myGraph){
    node* cur_node;
    for(int i=0; i<myGraph.numVertices; i++){
        printf("vertex %d : ", myGraph.adjLists[i]->vertex);
        cur_node = myGraph.adjLists[i]->next;
        while(cur_node){
            printf("%d -> ", cur_node->vertex);
            cur_node = cur_node->next;
        }
        printf("\n");
    }
}

void freeGraph(Graph * myGraph){
    node* cur_node; node* prev;
    for(int i=0; i<myGraph->numVertices; i++){
        // printf("vertex %d : ", myGraph.adjLists[i]->vertex);
        cur_node = myGraph->adjLists[i]->next;
        while(cur_node){
            prev = cur_node;
            cur_node = cur_node->next;
            free(prev);
        }
    }
    free(myGraph->adjLists);
}

typedef struct Node_s{         //тип вершины бинарного дерева 
    int value;
}Node;

void swap(Node** heap, int ind_a, int ind_b){
    int temp = heap[ind_a]->value;
    heap[ind_a]->value = heap[ind_b]->value;
    heap[ind_b]->value = temp;
}

void SiftUp(Node** heap, int index){
    //if this root
    if(index==0) return ;
    //parent == root
    if((index-1)<= 1){
        if(heap[0]->value > heap[index]->value){
            swap(heap, 0, index);
        }
        return ;
    }
    //otherwise
    int p_ind = (index-1)/2;
    if(heap[p_ind]->value > heap[index]->value){
        swap(heap, p_ind, index);
        SiftUp(heap, p_ind);
    }

}

void Add_to_Heap(int elem, Node** heap, int* lenHeap){
    heap[*lenHeap] = (Node*) malloc(sizeof(Node));
    heap[*lenHeap]->value = elem;
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
        if(heap[l_son]->value < heap[index]->value){
            swap(heap, l_son, index);
            SiftDown(heap, l_son, max_index);
        }
        return ;
    }
    //if only right
    if(l_son >= max_index){
        if(heap[r_son]->value < heap[index]->value){
            swap(heap, r_son, index);
            SiftDown(heap, r_son, max_index);
        }
        return ;
    }
    //otherwise
    int min;
    if(heap[r_son]->value < heap[l_son]->value){
        min = r_son;
    }else{
        min = l_son;
    }
    if(heap[min]->value < heap[index]->value){
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

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan len and graphs
    int n, m; fscanf(in, "%d %d", &n, &m);
    //init graph and other helpful things
    Graph myGraph;
    myGraph.numVertices = n;
    myGraph.adjLists = (node**) malloc(sizeof(node*)*n);
    init_Graph(&myGraph);
    int* counter = (int*) calloc(n+1, sizeof(int));
    //scan and add all edges
    int from, to;
    for(int i=0; i<m; i++){
        fscanf(in, "%d %d", &from, &to);
        addEdges(&myGraph, from, to);
        counter[to]++;
    }
    //update queue
    Node** heap = (Node**) calloc((n+1), sizeof(Node*));  //массив элементов, в котором хранится куча
    int len = 0; //текущий размер кучи    
    for(int i=n-1; i>=0; i--){
        if(counter[i+1]==0){
            Add_to_Heap(i+1, heap, &len);
        }
    }
    //topological sort
    int cur_vertex;
    node* cur_node;
    int* ans = (int*) malloc(sizeof(int)*n);
    int* in_ans = (int*) calloc(n, sizeof(int));
    for(int i=0; i<n; i++){
        //if exist cycle
        if(len<=0){
            fprintf(out, "bad course");
            //free spases
            freeGraph(&myGraph);
            free(counter);
            free(ans);
            free(heap);
            return 0;
        }
        //otherwise
        cur_vertex = heap[0]->value;
        ExtractMin(heap, &len);
        // free(temp);
        ans[i] = cur_vertex;
        in_ans[cur_vertex-1] = 1;
        cur_node = myGraph.adjLists[cur_vertex-1]->next;
        while(cur_node){
            if(in_ans[cur_node->vertex-1]==1){
                cur_node = cur_node->next;
                continue;
            }
            if(counter[cur_node->vertex]==0){
                cur_node = cur_node->next;
                continue;
            } 
            counter[cur_node->vertex]--;
            if(counter[cur_node->vertex]==0){
                Add_to_Heap(cur_node->vertex, heap, &len);
            }
            cur_node = cur_node->next;
        }
    }
    //print answer
    for(int i=0; i<n; i++){
        fprintf(out, "%d ", ans[i]);
    }
    //free spases
    freeGraph(&myGraph);
    free(counter);
    free(ans);
    free(heap);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}