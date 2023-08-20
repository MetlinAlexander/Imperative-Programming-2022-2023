#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    }
    //-------------------------------------------------------------------------
    //variables
    long int cur_y, ind_r, diff=0;
    // scan colovo request
    int q; fscanf(in, "%d", &q);
    for(int i=0; i<q; i++){
        //scan cur element for search
        fscanf(in, "%ld", &cur_y);
        //-------------------------
        //vars for bin search
        ind_r=0;
        int start = 0, end =(n-1), ind, cur_diff, tets;
        diff = abs(arr[0]-cur_y);
        //bin search
        while (start<=end){
            ind = (start+end)/2;
            cur_diff = abs(arr[ind]-cur_y);
            //check diff
            if(cur_diff<diff){
                diff = cur_diff;
                ind_r = ind;
            }else 
            if(cur_diff==0){
                diff = cur_diff;
                ind_r = ind;
                break;
            }
            //check ind
            if(cur_y < arr[ind])
                end = ind - 1;
            else if (cur_y > arr[ind])
                start = ind + 1;
            else{
                ind_r = ind;
                break;
            }
        }
        //-------------------------------------
        //print rezalt
        fprintf(out, "%d %ld\n", ind_r, diff);
        //-------------------------------------
    }
    //clear arr
    free(arr);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}
//for debug
// printf("searsh: %d\n", cur_y);
// printf("%d = [%d, %d]\n", ind, start, end);
// printf("ind = %d ; diff = %d\n", ind_r, diff);
// printf("----------\n");