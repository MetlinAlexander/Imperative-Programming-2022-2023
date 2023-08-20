#include "primes.h"

static int n = 0;
static int sieve[10000020];
static int prefics[10000021];

static void init_Sieve_of_Eratosthenes(){
    // make sieve erastrofeno
    for(int i=0; i<10000020; i++)
        sieve[i]=1;
    sieve[0]=0;
    sieve[1]=0;
    for(int i=2; i<10000020; i++){
        if (sieve[i]==1){
        for(int j =i+i; j<10000020; j+=i){
            sieve[j]=0;
        }
        }
    }
    n=10000020;
    //count prificsis
    prefics[0] =0;
    for(int i=1; i<n+1;i++){
        prefics[i] = prefics[i-1] + sieve[i-1];
    }

}
// init_Sieve_of_Eratosthenes();
// returns: 1 if x is prime number, 0 otherwise
int isPrime(int x){
    if(n==0){
        init_Sieve_of_Eratosthenes();
    }
    if(sieve[x]){
        return 1;
    }
    return 0;
}
// returns minimal prime number p such that p >= x
int findNextPrime(int x){
    if(n==0){
        init_Sieve_of_Eratosthenes();
    }
    for(int i=x; i<n; i++){
        if(isPrime(i)){
            return i;
        }
    }
}
// returns the number of primes x such that l <= x < r
int getPrimesCount(int l, int r){
    if(n==0){
        init_Sieve_of_Eratosthenes();
    }
    
    return prefics[r]-prefics[l];
}