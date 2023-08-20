#include <stdio.h>
#include <stdlib.h>

typedef struct node_s{
    int value;
    struct node_s* next;
}node;

void free_list(node* head){
    node* cur = head;
    node* to_free;
    while(cur){
        to_free = cur;
        cur = cur->next;
        free(cur);
    }
}



void compare( void * ctx , int * value ){
    if((*value)%2==0){ 
        int* temp = (int*) ctx;
        *temp =  ((int) (*((int*) ctx) + *value)); 
    }
}

//тип указателя на функцию, которую можно передавать как callback
typedef void (* callback )( void * ctx , int * value );

//здесь ctx –- это контекст, который передаётся в func первым аргументом
//последние два параметра задают массив, по элементам которого нужно пройтись
void arrayForeach ( void * ctx , callback func , int * arr , int n ){
    for(int i=0; i<n; i++){
        func(ctx, &arr[i]);
    }
}

void listForeach ( void * ctx , callback func , node * head){
    node* cur = head->next;
    while(cur){
        func(ctx, &cur->value);
        cur= cur->next;
    }
}



int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //read n
    int n; fscanf(in, "%d", &n);
    //mass
    int* mass= (int*) malloc(sizeof(int)*n);
    //list
    node* head = (node*) malloc(sizeof(node));
    head->next= NULL;
    head->value = 0;
    //scan n elements in massiv nad in list
    int cur;
    node* temp;
    for(int i=0; i<n; i++){
        fscanf(in, "%d", &cur);
        // printf("%d ", cur);
        //write in massiv
        mass[i] = cur;
        //write in list
        temp = head->next;
        head->next = (node*) malloc(sizeof(node));
        head->next->value = cur;
        head->next->next = temp;
    }
    //vars for anwers
    int arr_ans = 0;
    int list_ans = 0;
    void* p_arr= (void*) &arr_ans; 
    void* p_list= (void*) &list_ans; 
    //for array
    arrayForeach(p_arr, &compare, mass, n);
    listForeach(p_list, &compare, head);
    fprintf(out, "%d %d", arr_ans, list_ans);
    //free space
    free(mass);
    free_list(head);
    //CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}