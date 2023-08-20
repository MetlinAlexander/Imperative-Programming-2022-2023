#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
typedef struct Node{
    struct Node *prev, *next;
    double value;
} Node;
//создаёт пустой список
//возвращает указатель на value в голове списка (вспом. узел)
double *initList(){
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->next = temp;
    temp->prev = temp;
    temp->value = 12345432.123;
    return &temp->value;
}
//полностью освобождает память списка
//принимает указатель на value голове списка (вспом. узел)
void freeList(double *head){
    Node* temp = ( (Node*) ((char*) head - (char*)  offsetof(Node, value)) );
    Node* cur_ind = temp->next;
    for(int i=0; ; i++){
        cur_ind = cur_ind->next;
        free(cur_ind->prev);
        if(cur_ind == temp){
            break;
        }
    }
}
//определяет следующий элемент после заданного
//(для вспом. узла возвращает первый элемент)
double *getNext(double *curr){
    Node* temp = ( (Node*) ((char*) curr - (char*)  offsetof(Node, value)) );
    return &(temp->next)->value;
}
//определяет предыдущий элемент перед заданным
//(для вспом. узла возвращает последний элемент)
double *getPrev(double *curr){
    Node* temp = ( (Node*) ((char*) curr - (char*)  offsetof(Node, value)) );
    return &(temp->prev)->value;
}
//создаёт и вставляет узел со значением newval сразу после узла where
double *addAfter(double *where, double newval){
    Node* new_elem = (Node*) malloc(sizeof(Node));
    Node* node_where = ( (Node*) ((char*) where - (char*)  offsetof(Node, value)) );
    new_elem->value = newval; // write value
    new_elem->next = node_where->next; // update new element
    (node_where->next)->prev = new_elem;// update next element
    new_elem->prev = node_where; // update new element
    node_where->next  = new_elem; // update prev element
    return &new_elem->value;
    
}
//создаёт и вставляет узел со значением newval сразу перед узлом where
double *addBefore(double *where, double newval){
    Node* new_elem = (Node*) malloc(sizeof(Node));
    Node* node_where = ( (Node*) ((char*) where - (char*)  offsetof(Node, value)) );
    new_elem->value = newval; // write value
    new_elem->next = node_where; // update new element
    new_elem->prev = node_where->prev; // update new element
    (node_where->prev)->next = new_elem;// update prev element
    node_where->prev  = new_elem; // update next element
    return &new_elem->value;
}
//удаляет и освобождает заданный узел
void erase(double *what){
    Node* node= ( (Node*) ((char*) what - (char*)  offsetof(Node, value)) );
    (node->prev)->next = node->next;// update prev
    (node->next)->prev = node->prev;// update next
    free(node); // delete node
}

int main(){
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan how many tests
    int tests; fscanf(in, "%d", &tests); 
    //variables for every test
    int q, n;
    int action, index;
    int size = 100002;
    double* head;
    double new_elem;
    int real_len;
    //solving every test
    for(int t=0; t<tests; t++){
        n=0;
        real_len=0;
        //scan colovo of operations
        fscanf(in, "%d", &q); 
        //make list of index
        double** mass = (double**) malloc(size*sizeof(double*));
        //init head
        head = initList();
        mass[0] = head;
        n++;
        //operations with list and print operations results
        for(int i=0; i<q; i++){
            //scan var for operations
            fscanf(in, "%d", &action); // scan action
            if(action==1){ // add new element after - 1
                fscanf(in, "%d %lf", &index, &new_elem); // scan arguments
                index++; // update index
                mass[n] = addAfter(mass[index], new_elem); // add elem
                n++; // update n
                real_len++; // update len
            }else
            if(action==0){ // delete element - 0
                fscanf(in, "%d", &index); // scan arguments
                index++; // update index
                fprintf(out, "%0.3lf\n", *mass[index]); // print del element
                erase(mass[index]);
                real_len--;
            }else
            if(action==(-1)){ // add new element behind - (-1)
                fscanf(in, "%d %lf", &index, &new_elem); // scan arguments
                index++; // update index
                mass[n] = addBefore(mass[index], new_elem); // add elem
                n++; // update n
                real_len++; // update len
            }
        }
        //print ===
        fprintf(out, "===\n");

        //print whole list
        double* cur_value = getNext(mass[0]);
        for(int i=0; i<real_len; i++){
            fprintf(out, "%0.3lf\n", *cur_value);
            cur_value = getNext(cur_value);
        }
        //print ===
        fprintf(out, "===\n");
        //clean cur list
        freeList(head);
        free(mass);
        //clean head

    }
    fclose(in);
    fclose(out);
    return 0;
}

/*
2
5
1 -1 4283
-1 0 2718
1 0 5000
-1 1 1111
1 1 3141
9
1 -1 0
1 -1 1000
-1 -1 2000
1 1 3000
-1 0 4000
0 2
1 0 9876.543
0 1
0 3
*/