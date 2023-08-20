#include <stdio.h>
#include <malloc.h>

typedef unsigned long long bitword ;

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    // scan colovo request
    int n; fscanf(in, "%d", &n);
    //varibles
    int ans=0;
    bitword rez_bit;
    //arr for bitwords
    bitword* arr = (bitword*) malloc((n+1)*sizeof(bitword));
    //scan numbers
    for(int i=0; i<n; i++){
        fscanf(in, "%llx", &arr[i]);
        // printf("%llx\n", arr[i]);
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if((arr[i]&arr[j])== (bitword) 0) {
                ans++;
            }
            
        }
    }
    fprintf(out, "%d", ans);
    //clear arr
    free(arr);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}