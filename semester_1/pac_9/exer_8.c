#include <stdio.h>
#include <stdlib.h>

//Ternary search
int searchMin(const long long int* arr, int len_arr, long long int c_j){
    int left =0, right = len_arr -1, mid_1, mid_2;
    long long int minimum = 0, val_1, val_2;
    while(right - left >=3){
        mid_1 = left + (right - left ) / 3;
        mid_2 = right - (right - left) / 3;
        val_1 = arr[mid_1] + (c_j * mid_1);
        val_2 = arr[mid_2] + (c_j * mid_2);
        if  (val_1> val_2)
            left  =  mid_1;
        else
            right  =  mid_2;
    }
    return (left+right)/2;
}

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan len
    int n; fscanf(in, "%d", &n); 
    //scan array
    long long int* mass = (long long int*) malloc(n*sizeof(long long int));
    for(int i=0; i<n; i++)
        fscanf(in ,"%lld", &mass[i]);
    //scan colovo of requests
    int q; fscanf(in, "%d", &q);
    //scan and solve request
    long long int cur_request, funct_val, minim, min_ind, last;
    for(int i=0; i<q; i++){
        //scan Cj
        fscanf(in, "%lld", &cur_request);
        //find minimum
        minim = searchMin(mass, n, cur_request);
        //check first and last element
        if(mass[0]<=(mass[minim] + (cur_request * (long long int) minim))){
            minim = 0;
        }
        last = mass[n-1] + (cur_request * (long long int) (n-1));
        if( last <(mass[minim] + (cur_request * (long long int) minim)) & (mass[0]>last)) {
            minim = n-1;
        }
        //print answer
        fprintf(out, "%d\n", minim);
    }
    //free arr
    free(mass);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}
