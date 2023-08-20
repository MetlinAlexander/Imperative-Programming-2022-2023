#include <stdio.h>
#include <stdlib.h>


int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan size
    int n; fscanf(in, "%d", &n); 
    //scan matrix
    char** set = (char**) malloc(n*sizeof(char*));
    for(int i=0; i<n; i++){
        set[i] = (char*) malloc(n*sizeof(char));
        fscanf(in, "%s\n", set[i]);
    }
    //find all ways
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                printf("%d %d; %d %d\n", i+1, j+1, i+1, k+1);
                if(set[i][j]=='1' | (set[i][k]=='1' & set[k][j]=='1') | i==j){
                    set[i][j]='1';
                    
                } 
            }
        }
        printf("next\n");
    }
    //print answer and clean memory
    for(int i=0; i<n; i++){
        fprintf(out, "%s\n", set[i]);
        free(set[i]);
    }
    free(set);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}