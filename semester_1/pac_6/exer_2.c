#include <stdio.h>
#include <malloc.h>
typedef struct list_s
{
    char* value[8];
    int next;
}list;



int main(){
    //scan how many tests
    int tests; scanf("%d", &tests);
    //variables for every test
    int n, f, q;
    int action, index;
    char new[8];
    //solving every test
    int real_len;
    int size = 1000000;
    for(int t=0; t<tests; t++){
        if(t!=0){
            printf("\n");
        }
        //scan cur data
        scanf("%d %d %d", &n, &f, &q);
        real_len=n;
        //make list
        list *mass = malloc(size*sizeof(list));
        list *ukaz = mass;
        //scan list values
        for(int i=0; i<n; i++){
            scanf("%s %d", &mass[i].value, &mass[i].next);
        }
        //operations with list and print operations results
        for(int i=0; i<q; i++){
            //scan var for operations
            scanf("%d", &action); // scan action
            if(action==0){ // add new element
                n++; // update len
                real_len++;
                //list *mass = realloc(ukaz, n*sizeof(list)); // add new memory
                //list *ukaz = mass; // update pointer
                scanf("%d %s", &index, &mass[n-1].value); // scan arguments
                if(index==(-1)){ // add to the head
                    mass[n-1].next = f;
                    f = (n-1);
                }
                else{ // add to any place
                    mass[n-1].next = mass[index].next;
                    mass[index].next=(n-1);
                }
                printf("%d\n", n-1); // print new index
            }else
            if(action==1){ // delete element
                scanf("%d", &index);
                if(index==(-1)){ // delete head
                    printf("%s\n", mass[f].value);// print del element
                    f = mass[f].next;
                    real_len--;
                }
                else{ // delete other
                    printf("%s\n", mass[mass[index].next].value);// print del element
                    mass[index].next=mass[mass[index].next].next;// delete element
                    real_len--;
                }
            }
        }
        //print ===
        printf("===\n");
        //print whole list
        int cur_ind = f;
        for(int i=0; i<real_len; i++){
            //printf("\n");
            printf("%s\n", mass[cur_ind].value);
            cur_ind = mass[cur_ind].next;
        }
        //print ===
        printf("===");
        //clean cur list
        free(ukaz);
    }

    return 0;

}