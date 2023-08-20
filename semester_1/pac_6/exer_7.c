#include <stdio.h>
#include <stdlib.h>
typedef struct Node_s {
    struct Node_s * prev , * next ;
    void * value ;
} Node ;
//List –- вспомогательный узел, являющийся головой списка
typedef Node List ;
//инициализирует поля структуры *list значениями для пустого списка
void initList ( List * list ){
    // list->value = malloc(sizeof(int));
    // list->value = (void *) 0;
    list->next = list;
    list->prev = list;
};
//создаёт новый узел со значением ptr и вставляет его после узла node
//возвращает указатель на созданный узел
Node * addAfter ( Node * node , void * ptr ){
    Node* new_elem = (Node*) malloc(sizeof(Node)); // give memory for new elem
    new_elem->value = ptr; // write value
    new_elem->next = node->next; // update new element
    (node->next)->prev = new_elem;// update next element
    new_elem->prev = node; // update new element
    node->next  = new_elem; // update prev element
    return new_elem;
}; // 1
//создаёт новый узел со значением ptr и вставляет его перед узлом node
//возвращает указатель на созданный узел
Node * addBefore ( Node * node , void * ptr ){
    Node* new_elem = (Node*) malloc(sizeof(Node)); // give memory for new elem
    new_elem->value = ptr; // write value
    new_elem->next = node; // update new element
    new_elem->prev = node->prev; // update new element
    (node->prev)->next = new_elem;// update prev element
    node->prev  = new_elem; // update next element
    return new_elem;
}; // -1
//удаляет заданный узел, возвращая значение, которое в нём лежало
void * erase ( Node * node ){
    void* temp= node->value;
    (node->prev)->next = node->next;// update prev
    (node->next)->prev = node->prev;// update next
    free(node); // delete node
    return temp;
}; //0


int main(){
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan how many tests
    int tests; fscanf(in, "%d", &tests);
    //variables for every test
    int q, n, real_len;
    int action, index;
    void* new_elem= NULL;
    int size = 100002;
    Node **mass = NULL; // massive of index
    List *head = NULL;
    //solving every test
    for(int t=0; t<tests; t++){
        real_len = 0;
        n=0;
        //scan colovo of operations
        fscanf(in, "%d", &q);
        //make list of index
        mass = (Node**) malloc(size*sizeof(Node*));
        //init head
        head = (List*) malloc(sizeof(List));
        initList(head);
        mass[0] = head;
        n++;
        //operations with list and print operations results
        for(int i=0; i<q; i++){
            //scan var for operations
            fscanf(in, "%d", &action); // scan action
            // printf("%d-actions: %d\n", i+1, action);
            if(action==1){ // add new element in front - 1
                void* new_elem = (void*) malloc(sizeof(int));
                fscanf(in, "%d %d", &index, new_elem); // scan arguments
                index++; // update index
                // printf("%d\n", *((int*) new_elem));
                mass[n] = addAfter(mass[index], new_elem); // add elem
                n++; // update n
                real_len++; // update len
            }else
            if(action==0){ // delete element - 0
                fscanf(in, "%d", &index); // scan arguments
                index++; // update index
                // printf("%d\n",*((int*) mass[index]->value));
                void* del_value = erase(mass[index]);
                free(del_value); // free memory
                real_len--; // update len
            }else
            if(action==(-1)){ // add new element behind - (-1)
                void* new_elem = (void*) malloc(sizeof(int));
                fscanf(in, "%d %d", &index, new_elem); // scan arguments
                index++; // update index
                // printf("%d\n", *((int*) new_elem));
                mass[n] = addBefore(mass[index], new_elem); // add elem
                n++; // update n
                real_len++; // update len
            }
        }
        //print whole list
        Node* cur_ind = head->next;
        for(int i=0; i<real_len; i++){
            fprintf(out, "%d\n", *((int*)cur_ind->value));
            // printf("%d\n", *((int*)cur_ind->value));
            free((cur_ind->value)); // free value
            // if(cur_ind==head->prev) break;
            cur_ind = cur_ind->next;
            free(cur_ind->prev);
        }
        //print ===
        fprintf(out, "===\n");
        //clean cur list
        free(mass);
        //clean head
        free(head);
    }
    fclose(in);
    fclose(out);
    return 0;
}



// tests 
// 2
// 5
// 1 -1 4283
// -1 0 2718
// 1 0 5000
// -1 1 1111
// 1 1 3141
// 6
// 1 -1 0
// 1 -1 1000
// -1 -1 2000
// 1 1 3000
// -1 0 4000
// 0 2