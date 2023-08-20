#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
    char value[8];      //значение узла
    struct Node *next; //указатель на следующий элемент (или 0 если его нет)
} Node;
int main()
{
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    // scan colovo request
    int n;
    fscanf(in, "%d", &n);
    // var for temp data
    int index;
    // выделение памяти под указатели на массивы
    int size = 1000001;
    Node **arr = NULL;
    arr = (Node **)malloc(size * sizeof(Node *));
    // memory for pointers of end
    Node **end = NULL;
    end = (Node **)malloc(size * sizeof(Node *));
    for(int i=0; i<1000001; i++){
        end[i]= NULL;
    }
    // scan data and make lists
    for (int i = 0; i < n; i++)
    {
        fscanf(in, "%d", &index);
        
        if(end[index]){
            end[index]->next = (Node*) malloc(sizeof(Node)); // make new node
            fscanf(in, "%s", (end[index]->next)->value);
            end[index] = (end[index]->next);
        }else{
            arr[index] = (Node*) malloc(sizeof(Node)); // make new node
            fscanf(in, "%s", arr[index]->value);
            arr[index]->next = NULL;
            end[index] = arr[index]; // update end
        }
    }
    // print sort list
    for(int i=0; i<1000001; i++){
        if(end[i]==NULL) continue; // check index with data
        Node *cur_ind = arr[i]; 
        Node *to_free = NULL;
        // print every element with cur index
        for(int j=0; j<200001; j++){
            fprintf(out, "%d %s\n", i, cur_ind->value);
            if(cur_ind==end[i]){
                to_free =cur_ind;
                free(to_free);
                break;
            }
            to_free =cur_ind;
            cur_ind = cur_ind->next;
            free(to_free);
        }
    }
    // CLOSE FILES
    free(arr);
    free(end);
    fclose(in);
    fclose(out);
    return 0;
}