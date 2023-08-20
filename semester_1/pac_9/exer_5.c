#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// generate random numbers in range [lower, upper].
int myRand(int lower, int upper){
    srand(time(NULL));
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

int partition (int *a , int n , int pivot ){
    int* temp = (int*) malloc(n*sizeof(int));
    int left=0, right=0;
    int end = n-1, start = 0;
    int l_same=0, r_same=0;
    int same_as_pivot = 0;

    for(int i=0; i<n;i++){
        if(a[i]>pivot){
            temp[end] = a[i];
            end--;
            right++;
        }else
        if(a[i]<pivot){
            temp[start] = a[i];
            left++;
            start++;
        }else
        if(a[i] == pivot) same_as_pivot++;
        
    }
    int cur_ind=0;
    for(int i=0; i<start; i++){
        a[cur_ind++] = temp[i];
    }
    for(int i=0; i<same_as_pivot; i++){
        a[cur_ind++] = pivot;
    }
    for (int i = start+same_as_pivot; i < n; i++){
        a[cur_ind++] = temp[i];
    }
    
    left += same_as_pivot/2;
    free(temp);
    return left;

}

void quickSort(int* arr, int start, int end){
    if(end - start > 1){
        int len = end - start;
        int pivot = myRand(start, end-1);
        int left = partition(arr+start, len, arr[pivot]);
        quickSort(arr, start, start+left);
        quickSort(arr, start+left+1, end);
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
    // quick sort
    quickSort(arr, 0, n);
    //print quick sort array
    for(int i=0; i<n; i++){
        fwrite(&arr[i], sizeof(int), 1, out);
    }
    //free arrays
    free(arr);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}