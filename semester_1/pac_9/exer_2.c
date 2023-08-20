#include <stdio.h>
#include <stdlib.h>
//partitions array a[0..n-1] into two subarrays, returning value k
// the subarray a[0..k-1] must have all elements <= pivot
// the subarray a[k..n-1] must have all elements >= pivot
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

int main(){
    // open files
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");
    //var for len and pivot
    int n, p;
    //scan len
    fread(&n, sizeof(int), 1, in);
    //scan pivot
    fread(&p, sizeof(int), 1, in);
    // printf("n=%d; p=%d\n", n, p);
    //array
    int* arr = (int*) malloc(n*sizeof(int));
    //scan array
    fread(arr, sizeof(int), n, in);
    //partition
    int left = partition(arr, n, p);
    fwrite(&left, sizeof(int), 1, out);
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