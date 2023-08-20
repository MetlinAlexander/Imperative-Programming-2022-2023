#include <stdio.h>
#include <stdlib.h>
// typedef long long int bitword;
int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    // scan colovo elements
    int n; fscanf(in, "%d", &n);
    //init arr
    long int* arr = (long int*) malloc(n*sizeof(long int));
    //scan sort list
    for(int i=0; i<n;i++){
        fscanf(in, "%ld", &arr[i]);
        // printf("%ld ", arr[i]);
    }
    // printf("\n");
    //variables
    long int cur_x, cur_y, ind_r;
    long int pref_r = 0;
    // scan colovo request
    int q; fscanf(in, "%d", &q);
    for(int i=0; i<q; i++){
        ind_r = -1;
        fscanf(in, "%ld", &cur_x);
        cur_y = pref_r + cur_x;
        // printf("%ld = ", cur_y);
        //bin search
        printf("searsh: %d\n", cur_y);
        if((arr[0]<=cur_y) & (arr[n-1]>=cur_y)){
            //vars for bin search
            int start = 0, end =(n-1), ind=0;
            while(end>=start & ind >= 0){
                ind = (start+end)/2;
                // printf("%d = [%d, %d]\n", ind, start, end);
                if (cur_y < arr[ind])
                    end = ind - 1;
                else if (cur_y > arr[ind])
                    start = ind + 1;
                else{
                    if((end - start) == 1){
                        if(arr[start]==cur_y) ind = start;
                        else if (arr[end]==cur_y) ind = end;
                    }
                    break;
                }
            }
            if(arr[ind]==cur_y) {
                ind_r = ind;
                if(arr[n-1]==cur_y) {
                    ind_r = n-1;
                    ind = n-1;
                }
                for(int j=ind; j<n-1; j++){
                    if(arr[j+1]!=cur_y){
                        ind_r = j;
                        break;
                    }
                }
            }
        }

        // printf("answer = %d\n", ind_r);
        fprintf(out, "%d\n", ind_r);
        pref_r =ind_r;
    }
    //clear arr
    free(arr);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}