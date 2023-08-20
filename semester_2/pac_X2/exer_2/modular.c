#include "modular.h"

int MOD=0; // define global variable

int pnorm(int num){
    if(num<0){
        return (num%MOD + MOD) %MOD;
    }
    return num%MOD;
}

int padd(int a, int b){
    long long temp_a = (long long) a;
    long long temp_b = (long long) b;
    long long temp_rez;
    temp_rez = (temp_a + temp_b) % MOD;
    return (int) temp_rez;
}

int psub(int a, int b){
    long long temp_a = (long long) a;
    long long temp_b = (long long) b;
    long long temp_rez;
    temp_rez = (temp_a - temp_b) % MOD;
    return pnorm(temp_rez);
}

int pmul(int a, int b){
    long long temp_a = (long long) a;
    long long temp_b = (long long) b;
    long long temp_rez;
    temp_rez = (temp_a * temp_b) % MOD;
    return pnorm(temp_rez);
}




long long int inverse(long long int x){
    long long int p = MOD - 2;
    long long int r=1;
    while(p>0){
        if(p%2==1){
            r = (r*x)%MOD;
        }
        x= (x*x)%MOD;
        p /=2;
    }
    return r%MOD;
}

int pdiv(int a, int b){
    long long temp_b = (long long) b;
    return pmul(a, inverse(temp_b));
}
