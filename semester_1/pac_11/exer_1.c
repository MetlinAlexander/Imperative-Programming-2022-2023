#include <stdio.h>
#include <stdlib.h>

int jenkins(const char *key, size_t len){
    int hash = 0;
    for (int i = 0; i < len; i++)
    {   
        hash += (int) key[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

typedef struct node_s{
    int value;
    struct node_s* next;
}node;
//add elem and return 1 if hash_arr hasn`t this elem, else 0
int add_elem(node** hash_arr, int elem){
    char* pointer_temp = (char*) &elem;
    int cell = abs(jenkins(pointer_temp, sizeof(int)))%(100000);
    if(hash_arr[cell]==NULL){
        hash_arr[cell] = (node*) malloc(sizeof(node));
        hash_arr[cell]->value = elem;
        hash_arr[cell]->next = NULL;
        return 1;
    }else{
        node* cur = hash_arr[cell];
        while (cur){
            if(cur->value==elem){
                return 0;
            }else
            if(cur->next==NULL){
                cur->next = (node*) malloc(sizeof(node));
                cur->next->value = elem;
                cur->next->next = NULL;
                return 1;
            }
            cur = cur->next;

        }
        
    }
    return 0;
}


void free_hash_arr(node** hash_arr){
    node* cur; node* to_free;
    for(int i=0; i<100000; i++){
        if(hash_arr[i]){
            cur = hash_arr[i];
            while(cur){
                to_free = cur;
                cur= cur->next;
                free(to_free);
            }
            
        }
    }
    free(hash_arr);
}

int main(){
    // open files
    FILE *in = fopen("input.bin", "rb");
    FILE *out = fopen("output.bin", "wb");
    //read n
    int n;
    fread(&n, sizeof(int), 1, in);
    //scan other elements in hash
    int temp; 
    int cell;
    node** hash_arr= (node**) calloc(100000, sizeof(node*));
    int* ans = (int*) malloc(sizeof(int)*n);
    int k=0;
    for(int i=0; i<n; i++){
        fread(&temp, sizeof(int), 1, in);
        if(add_elem(hash_arr, temp)==1){
            ans[k] = temp;
            k++;
        }
    }
    //print k and ans
    fwrite(&k, sizeof(int), 1, out);
    fwrite(ans, sizeof(int), k, out);
    //free space
    free_hash_arr(hash_arr);
    free(ans);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}