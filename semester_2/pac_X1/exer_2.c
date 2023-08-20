#include <stdio.h>

//fast pow
long long int fast_pow(long long int x, long long int p, long long int mod){
    long long int r=1;
    while(p>0){
        if(p%2==1){
            r = (r*x)%mod;
        }
        x= (x*x)%mod;
        p /=2;
    }
    return r%mod;
}
//main
int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan how many test and  cur mod
    int t, m; fscanf(in, "%d %d", &t, &m);
    // scan every test and print answer
    int cur_test;
    int inverse;
    for(int i=0; i<t; i++){
        //scan cur test
        fscanf(in, "%d", &cur_test);
        //check if this zero
        if(cur_test==0){
            fprintf(out, "%d\n", (-1));
            continue;
        }
        // find Inverse element
        fprintf(out, "%d\n", fast_pow(cur_test, m-2, m));
    }
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}