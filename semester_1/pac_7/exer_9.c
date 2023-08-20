#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define VALTYPE int //тип значений: целое
typedef struct Node_s{
    size_t xorlinks; // XOR адресов соседних узлов
    VALTYPE value;   //значение в этом узле
} Node;

typedef struct List_s{
    // ??? //тут можно хранить всякие данные
} List;

//инициализировать пустой список в list
void initList(List *list);

//добавить новый узел со значением val между соседними узлами left и right
Node *addBetween(Node *left, Node *right, VALTYPE val);

//дано два соседних узла left и right, нужно удалить узел left
VALTYPE eraseLeft(Node *left, Node *right);

//дано два соседних узла left и right, нужно удалить узел right
VALTYPE eraseRight(Node *left, Node *right);

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    // scan colovo request
    int tests; fscanf(in, "%d", &tests);
    printf("n = %d\n", tests);
    //variables
    int q, left, right, new_elem, action;
    //solve request
    for(int t=0; t<tests; t++){
        //scan colovo of operations
        fscanf(in, "%d", &q);
        printf("q = %d\n", q);
        //make list of index
        //operations with list and print operations results
        for(int i=0; i<q; i++){
            //scan var for operations
            fscanf(in, "%d", &action); // scan action
            if(action==1){ // delete right - 1
                fscanf(in, "%d %d", &left, &right); // scan arguments
                printf("%d : del right %d %d\n", i, left, right);
            }else
            if(action==0){ // add element - 0
                fscanf(in, "%d %d %d", &left, &right,  &new_elem); // scan arguments
                printf("%d : add = %d;  %d %d\n", i, new_elem, left, right);
            }else
            if(action==(-1)){ // delete left - (-1)
                fscanf(in, "%d %d", &left, &right); // scan arguments
                printf("%d : del left %d %d\n", i, left, right);
            }
        }
    }
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}