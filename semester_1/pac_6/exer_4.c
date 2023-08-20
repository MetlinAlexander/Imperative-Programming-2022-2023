#include <stdio.h>
#include <malloc.h>
typedef struct Node_s
{   
    int prev;
    int value;
    int next;
}Node;

int main(){
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan how many tests
    int tests; fscanf(in, "%d", &tests);
    //variables for every test
    int n=0, f, l, q;
    int action, index;
    int real_len;
    //solving every test
    int size = 300000;
    Node *mass = NULL;
    for(int t=0; t<tests; t++){
        if(t!=0){
            fprintf(out, "\n");
        }
        //scan cur data
        fscanf(in, "%d %d %d %d", &n, &f, &l, &q);
        //make list
        mass = (Node*) malloc(size*sizeof(Node));
        // put in index=0 helper
        mass[0].next =f+1; mass[0].prev = l+1; n++;
        real_len = n-1;
        //scan list values
        for(int i=1; i<n; i++){
            fscanf(in, "%d %d %d", &mass[i].value, &mass[i].next, &mass[i].prev);
            mass[i].prev+=1; mass[i].next+=1;
        }
        //operations with list and print operations results
        for(int i=0; i<q; i++){
            //scan var for operations
            fscanf(in, "%d", &action); // scan action
            // printf("%d-actions: -%d-\n", i, action);
            if(action==1){ // add new element in front - 1
                n++; real_len++;// update len
                fscanf(in, "%d %d", &index, &mass[n-1].value); // scan arguments
                index++;// update index
                // add to any place
                mass[n-1].next = mass[index].next; // update new element
                mass[mass[n-1].next].prev = (n-1); // update next element
                mass[n-1].prev = index; // update new element
                mass[index].next=(n-1); // update prev element
                fprintf(out, "%d\n", n-2); // print new index
            }else
            if(action==0){ // delete element - 0
                fscanf(in, "%d", &index);
                //printf("%d-%d\n", i, index);
                index++;// update index
                real_len--;
                // delete other
                fprintf(out, "%d\n", mass[index].value);// print del element
                mass[mass[index].prev].next=mass[index].next;// update prev
                mass[mass[index].next].prev=mass[index].prev; // update next
            }else
           if(action==(-1)){ // add new element behind - (-1)
                n++; real_len++;// update len
                fscanf(in, "%d %d", &index, &mass[n-1].value); // scan arguments
                index++;// update index
                // add to any place
                mass[n-1].next = index;
                mass[n-1].prev = mass[index].prev;
                mass[mass[index].prev].next=(n-1);
                mass[index].prev = (n-1);
                fprintf(out, "%d\n", n-2); // print new index   
           }
        }
        //print ===
        fprintf(out, "===\n");
        //print whole list
        int cur_ind = mass[0].next;
        for(int i=0; i<real_len; i++){
            fprintf(out, "%d\n", mass[cur_ind].value);
            cur_ind = mass[cur_ind].next;
            // if(cur_ind==0) break;
        }
        //print ===
        fprintf(out, "===");
        //clean cur list
        free(mass);
    }
    
    fclose(in);
    fclose(out);
    return 0;
}



//---------------------------------------------------
//for emeregency situatio
//---------------------------------------------------


/*
                if(index==(-1)){ // add to the head
                    mass[n-1].prev = mass[helper.next].prev;
                    mass[helper.next].prev = (n-1);
                    mass[n-1].next = helper.next;
                    helper.next = (n-1);
                }else
                if(helper.prev==index){ // add after last
                    mass[n-1].prev = index;
                    mass[index].next=(n-1);
                    helper.prev=(n-1);
                    mass[n-1].next = (-1);
                }*/

/*
if(helper.next==index){ // delete head
                    fprintf(out, "%d\n", mass[index].value);// print del element
                    helper.next=mass[index].next;// update helper
                    mass[mass[index].next].prev=mass[index].prev; // update next
                }else
                if(helper.prev==index){ // delete last elem
                    fprintf(out, "%d\n", mass[index].value);// print del element
                    helper.prev=mass[index].prev;// update helper
                    mass[ mass[index].prev].next=(-1);// update prev
                }
*/
// if(index==(-1)){ // add after last
//                     mass[helper.prev].next = (n-1);
//                     mass[n-1].next = (-1);
//                     helper.prev = (n-1); //update helper 
//                 }else
//                 if(helper.next==index){ // add to the head
//                     mass[n-1].next = index;
//                     mass[index].prev=(n-1);
//                     helper.next=(n-1);//update helper
//                     mass[n-1].prev = (-1);
//                 }

// tests 
// 1
// 5 3 2 13
// 4283 2 4
// 2718 4 3
// 5000 -1 0
// 1111 1 -1
// 3141 0 1
// 1 0 6666
// 1 -1 123
// 1 -1 111
// 1 2 5555
// 1 8 7777
// 1 9 8888
// 0 1
// 0 7
// 0 6
// 0 10
// -1 3 91
// -1 11 81
// -1 2 55