#include "sol.h"
#include <stdlib.h>
#include <string.h>
int N = 6;
Edge* test;
int cur_edge=0;
int edge_cn=7;
// Example 
//     A -- B -- C
//    |    |    |
//    D -- E -- F
// Список ребер: AB, AD, BE, BC, DE, EF, CF.

// Список инцидентности:

// A: AB, AD
// B: AB, BE, BC
// C: BC, CF
// D: AD, DE
// E: BE, DE, EF
// F: EF, CF
// typedef struct
// {
//     int from, to;
//     int weight;
// } Edge;
//==============================================
// call these functions to get the graph data:
// returns N –- the number of vertices in the graph
int getVerticesCount(){
    return N;
}
// reads the next edge from the edge list
// if there is next edge, returns 1 and stores that edge to *oEdge
// if there is no next edge, returns 0 without touching pointer
int readEdge(Edge *oEdge){
    if(cur_edge>=edge_cn) return 0;
    cur_edge++;
    memcpy(oEdge, test, sizeof(Edge));
    return 1;
}
//==============================================
//data struct to save info about graph

// struct for every node
typedef struct node_s{
    Edge* edge;
    struct node_s* next;
}node;

typedef struct incident_list_s{
    int EdgesCount;
    node* vertex_edge_incident;
}incident_list;

incident_list** list;

// implement these functions in your solution:
// this function is called first to initialize graph
// you are expected to read graph here and fill internal data structures
void init(){
    int n = getVerticesCount();
    list = (incident_list**) malloc(sizeof(incident_list*)*n);
    //fill data
    for(int i=0; i<n; i++){
        list[i] = (incident_list*) malloc(sizeof(incident_list));
        list[i]->EdgesCount=0;
        list[i]->vertex_edge_incident = NULL;
    }
    Edge* cur_edge = (Edge*) malloc(sizeof(Edge));
    node* temp;
    int vert_temp;
    while(readEdge(cur_edge)!=0){
        //add to first vertix list
        temp = list[cur_edge->from]->vertex_edge_incident;
        list[cur_edge->from]->vertex_edge_incident = (node*) malloc(sizeof(node));
        list[cur_edge->from]->vertex_edge_incident->next = temp;
        list[cur_edge->from]->vertex_edge_incident->edge = (Edge*) malloc(sizeof(Edge));
        memcpy(list[cur_edge->from]->vertex_edge_incident->edge, cur_edge, sizeof(Edge));
        //update edge count
        list[cur_edge->from]->EdgesCount +=1;
        //add to second vertix list
        temp = list[cur_edge->to]->vertex_edge_incident;
        list[cur_edge->to]->vertex_edge_incident = (node*) malloc(sizeof(node));
        list[cur_edge->to]->vertex_edge_incident->next = temp;
        list[cur_edge->to]->vertex_edge_incident->edge = (Edge*) malloc(sizeof(Edge));
        memcpy(list[cur_edge->to]->vertex_edge_incident->edge, cur_edge, sizeof(Edge));
        vert_temp = list[cur_edge->to]->vertex_edge_incident->edge->from;
        list[cur_edge->to]->vertex_edge_incident->edge->from = list[cur_edge->to]->vertex_edge_incident->edge->to;
        list[cur_edge->to]->vertex_edge_incident->edge->to = vert_temp;
        //update edge count
        list[cur_edge->to]->EdgesCount +=1;
    }

}
// returns number of edges indicent to vertex iVertex
int getEdgesCount(int iVertex){
    return list[iVertex]->EdgesCount;
}
// returns iIndex-th edge incident to the vertex iVertex
// it must have .from == Vertex and .to denoting the other end
Edge getIncidentEdge(int iVertex, int iIndex){
    node* cur = list[iVertex]->vertex_edge_incident;
    for(int i=0; i<iIndex;i++){
        cur = cur->next;
    }
    return *(cur->edge);
    // Edge temp;
    // return temp;
}

//gcc my_sol.c -shared -fPIC -o my_sol.so