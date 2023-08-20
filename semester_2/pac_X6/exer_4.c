#include <stdio.h>
#include <stdlib.h>

// #define INF 
int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan data
    int n; fscanf(in, "%d\n", &n);
    int* array = (int*) malloc(sizeof(int)*(n));
    for(int i=0; i<n; i++){
        fscanf(in, "%d", &array[i]);
    }
    // solve
    int* dist = (int*) malloc(sizeof(int)*n);
    int* prev = (int*) malloc(sizeof(int)*n); 
    for(int i=0; i<n; i++){
        dist[i] = 1;
        prev[i] = -1;
        for(int j=0; j<i;j++){
            if(array[j]<array[i] && (dist[i] < (dist[j]+1)) ){
                dist[i] = dist[j]+1;
                prev[i] =j;
            }
        }
    }
    int len=dist[0], pos=0;
    for(int i=0; i<n;i++){
        if(dist[i]>len){
            pos=i;
            len = dist[i];
        }   
    }
    //recreate 
    int* way = (int*) malloc(sizeof(int)*len);
    int way_len=0;
    while(pos!=-1){
        way[way_len] = pos;
        pos = prev[pos];
        way_len++;
    }
    //print answer
    fprintf(out, "%d\n", len);
    for(int i=way_len-1; i>=0;i--){
        fprintf(out, "A[%d] = %d\n", way[i]+1, array[way[i]]);
    }
    // free
    free(array);
    free(dist);
    free(prev);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}