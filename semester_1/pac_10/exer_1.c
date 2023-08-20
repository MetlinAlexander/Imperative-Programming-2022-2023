#include <stdio.h>
#include <stdlib.h>

// do compare a and b
int compare (const void * a, const void * b){
    int data1 = *(int *)a, data2 = *(int *)b;
    if(data1<data2) return -1; // return -1 (or any negative number) if a < b
    else if(data1 == data2) return 0; // return 0 if a == b
    return 1; // return 1 (or any positive number) if a > b
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan len a
    int len_a; fscanf(in, "%d", &len_a);
    // printf("a = %d\n", len_a);
    //scan set_a
    int* a = (int*) malloc(len_a*sizeof(int));
    for(int i=0; i<len_a; i++){
        fscanf(in, "%d", &a[i]);
        // printf("%d ", a[i]);
    }
    // printf("\n");
    //scan len a
    int len_b; fscanf(in, "%d", &len_b);
    // printf("b = %d\n", len_b);
    //scan set_a
    int* b = (int*) malloc(sizeof(int)*len_b);
    for(int i=0; i<len_b; i++){
        fscanf(in, "%d", &b[i]);
        // printf("%d ", b[i]);
    }
    // printf("\n");
    //sort arrays
    qsort(a, len_a, sizeof(int), compare); 
    qsort(b, len_b, sizeof(int), compare);
    //searsh xor of sets
    int answer = 0, ind_a=0, ind_b=0, ans_ind=0;
    int* xor_lst = (int*) malloc(sizeof(int)*len_a);
    while (1){
        if(ind_a==len_a) break;
        if(ind_b==len_b){
            while(ind_a!=len_a){
                if(a[ind_a-1]!=a[ind_a]){
                    answer++;
                    xor_lst[ans_ind] = a[ind_a];
                    // printf("%d ", xor_lst[ans_ind]);
                    ans_ind++;
                }
                ind_a++;
            }
            break;
        }
        if(a[ind_a]>b[ind_b]){
            ind_b++;
        }else
        if(a[ind_a]==b[ind_b]){
            ind_a++;
        }else
        if(a[ind_a]<b[ind_b]){
            answer++;
            xor_lst[ans_ind] = a[ind_a]; 
            // printf("%d ", xor_lst[ans_ind]);
            ans_ind++;
            ind_a++;
            while(a[ind_a-1]==a[ind_a] & ind_a!=len_a){
                ind_a++;
            }
        }
    }
    //print answer
    fprintf(out, "%d\n", answer);
    for(int i=0; i<answer; i++){
        fprintf(out, "%d ", xor_lst[i]);
    }
    // free arrays
    free(a);
    free(b);
    free(xor_lst);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}