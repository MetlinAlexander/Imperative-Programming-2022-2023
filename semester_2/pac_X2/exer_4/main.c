#include <stdio.h>
#include <stdlib.h>

//gcc -o app main.c sum.c query.c

int n;

void Init ( const int * arr , int n );

int Query ( int l , long long sum );

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan vars
    fscanf(in, "%d", &n); // 𝑁 — the number of array elements 𝐴
    int m; fscanf(in, "%d", &m); //  𝑀 —the number of questions
    //scan A
    int* arr = (int*) malloc(sizeof(int)*n);
    for(int i=0; i<n;i++){
        fscanf(in, "%d", &arr[i]);
    }
    //init all sums
    Init(arr, n);
    // scan and solve questions
    int l;
    long long s;
    for(int i=0; i<m;i++){
        fscanf(in, "%d %lld", &l, &s);
        fprintf(out, "%d\n", Query(l, s));
    }
    // free array
    free(arr);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}
// 1 4 0 5 6 0 0 1 5 3