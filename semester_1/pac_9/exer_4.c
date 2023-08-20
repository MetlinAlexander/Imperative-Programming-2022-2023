#include <stdio.h>
#include <stdlib.h>

//merges sorted arrays a[0..ak-1] and b[0..bk-1] into
//one sorted array res[0..rk-1], returning rk from function
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



int main(){
    // open files
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");
    //scan len
    int n; fread(&n, sizeof(int), 1, in);
    //array
    int* arr = (int*) malloc(n*sizeof(int));
    //scan array
    fread(arr, sizeof(int), n, in);
    // merge sort
    merge_sort(arr, 0, n-1);
    //print merge sort array
    for(int i=0; i<n; i++)
        fwrite(&arr[i], sizeof(int), 1, out);
    //free arrays
    free(arr);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}