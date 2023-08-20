#include <stdio.h>
#include <stdlib.h>


//hash functions
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
//node for hash arr
typedef struct node_s{
    unsigned long long int value;
    struct node_s* next;
}node;
//add elem and return 1 if hash_arr hasn`t this elem, else 0
int add_elem(node** hash_arr, unsigned long long int elem){
    char* pointer_temp = (char*) &elem;
    int cell = abs(jenkins(pointer_temp, sizeof(unsigned long long int)))%(200000);
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

// free hash arr after using
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

//struct func for values
typedef struct data_s{
    unsigned long long int m, a, b, c;
}data;


unsigned long long int func ( unsigned long long int state,  data myData) {
    return (state * state * myData.a + state * myData.b + myData.c ) % myData.m;
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //read data
    data mydata;
    fscanf(in, "%llu", &mydata.m);
    fscanf(in, "%llu %llu %llu", &mydata.a, &mydata.b, &mydata.c);
    //make hash arr 
    node** hash_arr= (node**) calloc(200001, sizeof(node*));
    //arr for every state
    unsigned long long int* values = (unsigned long long int*) malloc((4*1000000+1)*sizeof(unsigned long long int));
    //search every value
    unsigned long long int state = 1;
    for(int i=0; i<4*1000000+1; i++){
        values[i] = state;
        state = func(state, mydata);
    }
    //find cycle
    int start=0, end=0;
    for(int i=0; i<4*1000000+1; i++){
        printf("%d ", values[i]);
        if(add_elem(hash_arr, values[i])==0){
            //we find cycle
            end = i; // end of cycle
            //find start of cycle
            for(int j=end-1; j>=0; j--){
                if(values[j]==values[end]){
                    start = j;
                    break;
                }
            }
            //print answer
            fprintf(out, "%d %d", start, end);
            break;
        }
    }
    //free space
    free(values);
    free_hash_arr(hash_arr);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}