#include <stdio.h>
#include <stdlib.h>

//merge sort -------------------------------------------------------------
void merge (int* mass , int start , int middle , int end){
    //create temp arrays
    int len_head = middle+1-start;
    int len_tail = end-middle;
    int* head = (int*) malloc(len_head*sizeof(int)); int* h_uk = head;
    for(int i=0; i<len_head; i++){
        head[i] = mass[start+i];
    }
    int* tail = (int*) malloc(len_tail*sizeof(int)); int* t_uk = tail;
    for(int i=0; i<len_tail; i++){
        tail[i] = mass[middle+i+1];
    }
    //merge
    int a_ind=0, b_ind=0, rk=start, ak = len_head, bk = len_tail;
    for(int i=0; i<(ak+bk); i++){
        if(*head<*tail){
            mass[rk++] = *head++;
            a_ind++;
        }else{
            mass[rk++] = *tail++;
            b_ind++;
        }
        if(a_ind==ak){
            for(int j=0; j<(bk-b_ind); j++)
                mass[rk++] = *tail++;
            break;
        }else
        if(b_ind==bk){
            for(int j=0; j<(ak-a_ind); j++)
                mass[rk++] = *head++;
            break;
        }
    }
    //clear temp arrays
    free(h_uk);
    free(t_uk);
}


void merge_sort(int* mass, int start, int end){
    if(end>start){
        //search middle
        int midlle = (start+end)/2;
        //sort left and right
        merge_sort(mass, start, midlle);
        merge_sort(mass, midlle+1, end);
        //merge
        merge(mass, start, midlle, end);
    }
}
//merge sort -------------------------------------------------------------

//2 147 483 647
//1 000 000 000
int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan len
    int n; fscanf(in, "%d", &n);
    //var for answer
    int ans =0;
    //scan array
    int* arr = (int*) malloc((n+1)*sizeof(int));
    for(int i=0; i<n; i++)
        fscanf(in ,"%d", &arr[i]);
    //sort arr with merge sort
    merge_sort(arr, 0, n-1);
    //massive for answer
    int* mass = (int*) malloc(n*sizeof(int));
    int len_mass=0;
    //speacial trick
    arr[n] = arr[n-1] + 1;
    //search sum
    for(int i=0; i<n; i++){
        if(arr[i]!=arr[i+1]){
            ans++;
            mass[len_mass++] = arr[i];
        }
    }
    //print answer
    fprintf(out, "%d\n", ans);
    for(int i=0; i<len_mass; i++)
        fprintf(out, "%d\n", mass[i]);
    //free arr
    free(mass);
    free(arr);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}
