#include <stdio.h>
#include <stdlib.h>

typedef struct Elem_s{
    unsigned int key;
    unsigned int inf;
}Elem;

//radix sort----------------------------------

void counterRedix_Sort(Elem* arr, int bait, int len){
    //mass for count
    int* mass = (int*) calloc(256, sizeof(int));
    //count
    unsigned int helper = 0b11111111;
    for(int i=0; i<len; i++){
        mass[(arr[i].key>>(bait*8))&helper]++;
    }
    //count sums
    int ind=0, temp =0;
    for(int i=0; i<256; i++){
        if(mass[i]!=0){
            temp = mass[i];
            mass[i]=ind;
            ind = temp+ind;
        }
    }
    //make new sort arr by cur bait
    Elem* sort_arr = (Elem*) malloc(sizeof(Elem)*len);
    int cur_ind;
    for(int i=0; i<len; i++){
        cur_ind = (arr[i].key>>(bait*8))&helper;
        sort_arr[mass[cur_ind]] = arr[i];
        mass[cur_ind]++;
    }
    //copy to arr
    for(int i=0; i<len; i++){
        arr[i] = sort_arr[i];
    }
    //free arr
    free(mass);
    free(sort_arr);
}


//main radix sort
void radix_sort(Elem* arr, int bait_len, int len){
    for(int i=0; i<bait_len; i++){
        //sort by cur bait
        counterRedix_Sort(arr, i, len);
    }
}
//radix sort----------------------------------

int main(){
    // open files
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");
    //scan len
    int n; fread(&n, sizeof(int), 1, in);
    //scan pairs
    Elem* arr= (Elem*) malloc(n*sizeof(Elem));
    fread(arr, sizeof(Elem), n, in);
    //radix sort
    radix_sort(arr, 4, n);
    //print sort array
    fwrite(arr, sizeof(Elem), n, out);
    //free arr
    free(arr);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}