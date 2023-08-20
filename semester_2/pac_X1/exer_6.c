#include <stdio.h>
#include <stdlib.h>
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

//find inverse elem
long long int inverse(long long int num, long long int mod){
    return fast_pow(num, mod-2, mod);
}

//main
int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan how many tests
    int t; fscanf(in, "%d", &t);
    //mod
    int mod = 1000000007; 
    //find all factorials up to 1000000
    long long int* prepare_factorial = (long long int*) malloc(sizeof(long long int)*1000002);
    prepare_factorial[0] = 1;
    for(long long int i=1; i<1000002; i++){
        prepare_factorial[i] = (prepare_factorial[i-1]*i) % mod;
    }
    //scan and solve every test
    int n, k;
    long long int cur_result;
    for(int i=0; i<t; i++){
        //scan cur n k
        fscanf(in, "%d %d", &n, &k);
        //find answer C(n, k) = n! / (k! (n-k!)) = x / y
        cur_result = ( prepare_factorial[n] * inverse( (prepare_factorial[k] * prepare_factorial[n-k]) %mod , mod) ) %mod ;
        //print answer 
        fprintf(out, "%d\n", cur_result);
    }
    //free 
    free(prepare_factorial);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}