
#include "modular.h" //в этом хедере должны быть объявления
#include <assert.h>
// #include <stdio.h>
int main(){
    MOD = 13; // устанавливаем глобальный модуль
    int a = 45;
    a = pnorm(a);
    assert(a == 6);
    int x = pmul(padd(7, psub(2, 3)), 5);
    assert(x == 4);
    int y = pdiv(7, x);
    assert(pmul(x, y) == 7);
    MOD = 2; // меняем модуль на другой
    assert(pnorm(5) == 1);

    //my tests
    MOD = 999999937;
    a = pnorm(-999999948);
    assert(a == 999999926);

    a = padd(999999926, 999999906);
    assert(a == 999999895);

    a = psub(6, 999999911);
    assert(a==32);

    a = pmul(999999926, 999999906);
    // printf("%d", a);
    assert(a == 341);

    a = psub(999999911, 0);
    assert(a==999999911);

    a = pdiv(999999911, 1345667);
    assert(a==734015873);
    
    return 0;
}