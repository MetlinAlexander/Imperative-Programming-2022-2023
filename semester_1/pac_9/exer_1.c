#include <stdio.h>
#include <stdlib.h>

//merges sorted arrays a[0..ak-1] and b[0..bk-1] into
//one sorted array res[0..rk-1], returning rk from function
int merge ( const int *a , int ak , const int *b , int bk , int * res ){
    int a_ind=0, b_ind=0, rk=0;
    for(int i=0; i<(ak+bk); i++){
        if(*a<*b){
            res[rk++] = *a++;
            a_ind++;
        }else{
            res[rk++] = *b++;
            b_ind++;
        }
        if(a_ind==ak){
            for(int j=0; j<(bk-b_ind); j++)
                res[rk++] = *b++;
            break;
        }else
        if(b_ind==bk){
            for(int j=0; j<(ak-a_ind); j++)
                res[rk++] = *a++;
            break;
        }
    }
    return rk;
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");
    //var for len
    int n, m;
    //scan first len
    fread(&n, sizeof(int), 1, in);
    //scan first len
    fread(&m, sizeof(int), 1, in);
    //array
    int* a_arr = (int*) malloc(n*sizeof(int));
    int* b_arr = (int*) malloc(m*sizeof(int)); 
    //scan first array
    fread(a_arr, sizeof(int), n, in);
    //scan second array
    fread(b_arr, sizeof(int), m, in);
    //array for answer
    int* answer = (int*) malloc((n+m)*sizeof(int));
    //merge
    int rk = merge(a_arr, n, b_arr, m, answer);
    //print merge array
    fwrite(answer, sizeof(int), rk, out);
    //free arrays
    free(a_arr);
    free(b_arr);
    free(answer);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}
