#include <stdio.h>
#include <stdlib.h>

typedef struct Node_s{
    int position;
    int next;
}Node;

void list_print(Node* arr, int head, int max_len){
    int cur_ind = head;
    for(int i=0; i<max_len; i++){
        printf("%d ", arr[cur_ind].position);
        cur_ind = arr[cur_ind].next;
        if(cur_ind==head) break;
    }
    printf("\n");
}

void del_elem(Node* arr, int index, int* head, FILE* out){
    // print del element
    fprintf(out, "%d\n", arr[arr[index].next].position);
    //update head
    if(arr[index].next==*head)
        *head = arr[arr[index].next].next;
    // delete element
    arr[index].next=arr[arr[index].next].next;
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    // scan vars N and K
    int n, k; 
    fscanf(in, "%d %d", &n, &k);
    //make list
    Node *mass = malloc(n*sizeof(Node));
    int first = 0, last = n-1, real_len=n;
    //write list values
    for(int i=1; i<n+1; i++){
        mass[i-1].next = i;
        mass[i-1].position = i;
    }
    //connect last elem with first
    mass[last].next = first;
    mass[last].position = n;

    //count and delete
    int pass=0, cur=first;
    while(real_len>0){
        pass++;
        if(pass==(k-1)){
            real_len--;
            pass = 0;
            del_elem(mass, cur, &first, out);
        }
        cur =  mass[cur].next;
    }
    //clear space
    free(mass);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}