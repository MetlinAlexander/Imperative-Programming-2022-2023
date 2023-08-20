#include <stdio.h>
#include <stdlib.h>
//main
int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan mod and how many tests
    int m, t; fscanf(in, "%d %d", &m, &t);
    //create Pascal's triangle
    int** triagle = (int**) malloc(sizeof(int*)*(2001));
    triagle[0] = (int*) malloc(sizeof(int));
    triagle[0][0] = 1;
    for(int i = 1; i<2001; i++){
        triagle[i] = (int*) malloc(sizeof(int)*(i+1));
        triagle[i][0] = 1;
        for(int j =1; j<i; j++){
            triagle[i][j]=(triagle[i-1][j-1] + triagle[i-1][j]) % m;
        }
        triagle[i][i] = 1;
    }
    //scan and solve every test
    int n, k;
    for(int i=0; i<t; i++){
        //scan cur n k
        fscanf(in, "%d %d", &n, &k);
        //check k and n
        if(k<0 || k>n){
            // printf("%d %d : %d\n", n, k, 0);
            fprintf(out, "%d\n", 0);
            continue;
        }
        //print answer
        fprintf(out, "%d\n", triagle[n][k]);
    }
    //free space
    for(int i=0; i<2001;i++){
        free(triagle[i]);
    }
    free(triagle);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}