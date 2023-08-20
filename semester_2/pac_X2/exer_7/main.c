#include "primes.h" //в этом хедере должны быть объявления
#include <assert.h>
#include <stdio.h>
// #include <stdio.h>
int main(){

    //check is prime
    assert(isPrime(12)==0);
    assert(isPrime(3002)==0);
    assert(isPrime(13)==1);
    assert(isPrime(3001)==1);
    assert(isPrime(0)==0);
    assert(isPrime(10000000)==0);
    assert(isPrime(9999991)==1);

    // check next prime
    assert(findNextPrime(678)==683);
    assert(findNextPrime(1234566)==1234577);
    assert(findNextPrime(1234547)==1234547);
    assert(findNextPrime(0)==2);
    assert(findNextPrime(9999991)==9999991);
    assert(findNextPrime(9999990)==9999991);
    assert(findNextPrime(10000000)==10000019);
    //check count primes
    assert(getPrimesCount(0, 72)==20);
    assert(getPrimesCount(3433, 3467)==5);
    assert(getPrimesCount(24, 29)==0);
    assert(getPrimesCount(24, 24) == 0);
    assert(getPrimesCount(2, 2)==0);
    assert(getPrimesCount(0, 10000000)==664579);
    assert(getPrimesCount(0, 9999991)==664578);
    // printf("%d", getPrimesCount(0, 9999991));
    return 0;
}