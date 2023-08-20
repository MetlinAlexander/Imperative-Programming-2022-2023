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
    if(temp==NULL){
        myGraph->adjLists[from-1]->next = (node*) malloc(sizeof(node));
        myGraph->adjLists[from-1]->next->vertex = to;
        myGraph->adjLists[from-1]->next->next = temp;
    }else
    if(temp->next==NULL){
        if(temp->vertex>to){
            temp->next = (node*) malloc(sizeof(node));
            temp->next->vertex = to;
            temp->next->next = NULL;
        }else{
            myGraph->adjLists[from-1]->next = (node*) malloc(sizeof(node));
            myGraph->adjLists[from-1]->next->vertex = to;
            myGraph->adjLists[from-1]->next->next = temp;
        }
    }
    else{
        node* prev = temp;
        node* after = temp->next;
        while(1){
            if(prev->vertex > to & after->vertex < to){
                prev->next = (node*) malloc(sizeof(node));
                prev->next->vertex = to;
                prev->next->next = after;
                return ;
            }
            prev = prev->next;
            after = after->next;
            if(after == NULL){
                prev->next = (node*) malloc(sizeof(node));
                prev->next->vertex = to;
                prev->next->next = after;
                return ;
            }
        }
    }
    return ;
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

typedef struct Queue_s{
    int value;
    struct Queue_s* next;
}Queue;

void addToQueue(Queue* head, int * in_queue, int vertex){
    Queue* temp;
    
    if(*in_queue==0){
        head->next = (Queue*) malloc(sizeof(Queue));
        head->next->value = vertex;
        head->next->next = NULL;
    }else
    if(*in_queue==1){
        if(head->next->value>vertex){
            temp = head->next;
            head->next = (Queue*) malloc(sizeof(Queue));
            head->next->value = vertex;
            head->next->next = temp;
        }else{
            head->next->next = (Queue*) malloc(sizeof(Queue));
            head->next->next->value = vertex;
            head->next->next->next = NULL;
        }
    }else{
        
        if(head->next->value>vertex){
            temp = head->next;
            head->next = (Queue*) malloc(sizeof(Queue));
            head->next->value = vertex;
            head->next->next = temp;
            (*in_queue)++;
            return ;
        }
        Queue* prev = head->next;
        Queue* after = prev->next;
        while(1){
            if(prev->value < vertex & after->value > vertex){
                prev->next = (Queue*) malloc(sizeof(Queue));
                prev->next->value = vertex;
                prev->next->next = after;
                break;
            }
            prev = prev->next;
            after = after->next;
            if(after == NULL){
                prev->next = (Queue*) malloc(sizeof(Queue));
                prev->next->value = vertex;
                prev->next->next = after;
                break;
            }
        }
    }
    (*in_queue)++;
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
    int in_queue = 0, in_graph = n;
    //scan and add all edges
    int from, to;
    for(int i=0; i<m; i++){
        fscanf(in, "%d %d", &from, &to);
        addEdges(&myGraph, from, to);
        counter[to]++;
    }
    //update queue
    Queue head; head.value = 0; head.next=NULL;
    for(int i=n-1; i>=0; i--){
        if(counter[i+1]==0){
            addToQueue(&head, &in_queue, i+1);
        }
    }
    //topological sort
    Queue* temp;
    int cur_vertex;
    node* cur_node;
    int* ans = (int*) malloc(sizeof(int)*n);
    int* in_ans = (int*) calloc(n, sizeof(int));
    for(int i=0; i<n; i++){
        //if exist cycle
        if(in_queue<=0){
            fprintf(out, "bad course");
            //free spases
            freeGraph(&myGraph);
            free(counter);
            free(ans);
            return 0;
        }
        //otherwise
        cur_vertex = head.next->value;
        temp = head.next;
        head.next = temp->next;
        free(temp);
        in_queue--;
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
                addToQueue(&head, &in_queue, cur_node->vertex);
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
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}