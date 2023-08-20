// структура, в которой хранится разложение на простые множители
typedef struct Factors{
    int k;          // сколько различных простых в разложении
    int primes[32]; // различные простые в порядке возрастания
    int powers[32]; // в какие степени надо эти простые возводить
} Factors;
// функция, которая находит разложение числа X и записывает его в структуру res
void Factorize(int X, Factors *res){
    res->k = 0;
    int i=2;
    while(i*i<=X){
        if(X%i==0){
            res->k+=1;
            res->primes[res->k-1]=i;
            res->powers[res->k-1]=0;
            while(X%i==0){
                X/=i;
                res->powers[res->k-1]+=1;
            }
        }
        i+=1;
    }
    if(X>1){
        res->k+=1;
        res->primes[res->k-1]=X;
        res->powers[res->k-1]=1;
    }
    return ;

}