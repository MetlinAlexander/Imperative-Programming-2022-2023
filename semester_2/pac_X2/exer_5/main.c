#include <stdio.h>
#include <stdlib.h>
// структура, в которой хранится разложение на простые множители
typedef struct Factors{
    int k;          // сколько различных простых в разложении
    int primes[32]; // различные простые в порядке возрастания
    int powers[32]; // в какие степени надо эти простые возводить
} Factors;
void Factorize(int X, Factors *res);

int main(){
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int m; fscanf(in, "%d", &m);
    int x;
    Factors* cur;
    //scan every x
    for(int i = 0; i<m;i++){
        fscanf(in, "%d", &x);
        fprintf(out, "%d = ", x);
        if(x==1){
            fprintf(out, "%d\n", x);
            continue;
        }
        cur = (Factors*) malloc(sizeof(Factors));
        Factorize(x, cur);
        //print answer
        for(int j=0; j<cur->k; j++){
            fprintf(out, "%d^%d", cur->primes[j], cur->powers[j]);
            if(j!=cur->k-1){
                fprintf(out, " * ");
            }
        }
        fprintf(out, "\n");

        free(cur);
    }
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}