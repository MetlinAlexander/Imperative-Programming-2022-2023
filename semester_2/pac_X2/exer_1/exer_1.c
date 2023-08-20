#include <stdio.h>
#include <stdlib.h>


typedef long long int int64;

// C function for extended Euclidean Algorithm
int64 gcdExtended(int64 a, int64 b, int64 *x, int64 *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
 
    int64 x1, y1; // To store results of recursive call
    int64 gcd = gcdExtended(b%a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}

int64 inverse(int64 num, int64 mod){
    int64 x, y;
    int64 gcd = gcdExtended(num, mod, &x, &y);
    return ((x % mod + mod) % mod);
}


int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    //scan k
    int64 k; fscanf(in, "%lld", &k);
    // printf("k=%d\n", k);
    
    //scan mods and find product of all mods
    int64 product =1;
    int64* mods= (int64*) malloc(sizeof(int64)*k);
    for(int64 i=0; i<k;i++){
        fscanf(in, "%lld", &mods[i]);
        product *= mods[i];
        // printf("%llu ", mods[i]);
    }
    // printf("\nproduct = %llu\n", product);
    //scan remainders
    int64* remainders = (int64*) malloc(sizeof(int64)*k);
    for(int64 i=0; i<k;i++){
        fscanf(in, "%lld", &remainders[i]);
        // printf("%llu ", remainders[i]);
    }
    // printf("\n");
    // find p_m[i] is product of all divided by mods[i] 
    int64* p_m = (int64*) malloc(sizeof(int64)*k);
    for(int64 i=0; i<k; i++){
        p_m[i] = product / mods[i];
        // printf("%llu ", p_m[i]);
    }
    // printf("\n");
    //find inv[i] for p_m[i] by mods[i]
    int64* inv_p = (int64*) malloc(sizeof(int64)*k);
    for(int64 i=0; i<k; i++){
        inv_p[i] = inverse(p_m[i], mods[i]);
        // printf("%llu ", inv_p[i]);
    }
    // printf("\n");
    //find x
    // x =  ( ∑ (rem[i]*pp[i]*inv[i]) ) % prod
    int64 x=0;
    for(int64 i=0; i<k; i++){
        x = (x + ( (( remainders[i]*inv_p[i] % mods[i]) *p_m[i]) % product) ) % product;
    }
    //print answer
    fprintf(out, "%lld\n", x);
    // printf("%lld\n", x);
    //free
    free(mods);
    free(remainders);
    free(p_m); 
    free(inv_p);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}