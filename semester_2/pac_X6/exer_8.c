#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int **memo;
int** f;
int N, Wmax;
int* weight;
int* cost;
int is_taken=0;

int Rec(int k, int sumW) {
    if (k == N){
        memo[k][sumW]=0;  // предметов не осталось => общая стоимость остатка нулевая
        return 0; 
    }                          
    int Cskip = 0;
    int Ctake =0;
    // пробуем не брать k-ый предмет, определяем
    if(memo[k+1][sumW]!=-1){
        Cskip = memo[k+1][sumW];
    }else{
        Cskip = Rec(k+1, sumW);             
    }


    if (sumW + weight[k] <= Wmax) {                  // брать предмет можно, только если он входит в рюкзак
        // Ctake = Rec(k+1, sumW + weight[k]) + cost[k]; // если предмет возьмём, то надо выбрать оптимальный набор среди
                                                // оставшихся предметов (начиная с k+1-ого), и не забываем
                                                // добавить стоимость k-ого предмета
        if(memo[k+1][sumW + weight[k]]!=-1){
            Ctake = memo[k+1][sumW + weight[k]] + cost[k];
        }else{
            Ctake = Rec(k+1, sumW + weight[k]) + cost[k];            
        }
    }
    is_taken =MAX(is_taken, k);
    memo[k][sumW] = MAX(Cskip, Ctake);
    if(Cskip>Ctake){
        f[k][sumW] = 0;
    }else{
        f[k][sumW] = 1;
    }
    return MAX(Cskip, Ctake);
  }
// int Rec(int Sum, int Last)
// {
//     if (memo[Sum][Last] == -1)
//     { // -1 в memo означает, что значение ещё не вычислено
//         int res = 0;
//         if (Sum == N)
//             res = 1; // разбиение построено: один вариант
//         else
//         {
//             for (int x = 1; x <= MIN(Last, N - Sum); x++) // перебираем все допустимые x
//                 res = (res + Rec(Sum + x, x))%mod;                   // запускаем перебор хвоста последовательности
//         }
//         memo[Sum][Last] = res; // запоминаем результат в memo
//     }
//     return memo[Sum][Last]; // возвращаем запомненный результат
// }

int main()
{
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    // scan data
    fscanf(in, "%d %d", &N, &Wmax);
    printf("n=%d; Max_weigth=%d\n", N, Wmax);
    weight = (int*) malloc(sizeof(int)*N);
    cost = (int*) malloc(sizeof(int)*N);
    for(int i=0; i<N; i++){
        fscanf(in, "%d %d", &weight[i], &cost[i]);
        printf("%d %d\n", weight[i], cost[i]);
    }
    // mem for rez
    memo = (int **)malloc(sizeof(int *) * (N + 1));
    f = (int **)malloc(sizeof(int *) * (N + 1));
    for (int i = 0; i < N + 1; i++){
        memo[i] = (int *)malloc(sizeof(int) * (Wmax + 1));
        f[i] = (int *)malloc(sizeof(int) * (Wmax + 1));
        for (int j = 0; j < Wmax + 1; j++){
            memo[i][j] = -1;
            f[i][j] = -1;
        }
    }
    // solve
    // print ans
    fprintf(out, "%d\n", Rec(0, 0));
    printf("[%d %d]\n", is_taken, Rec(0, 0));
    // free
    free(cost);
    free(weight);
    for (int i = 0; i < N + 1; i++)
    {   
        for (int j = 0; j < Wmax + 1; j++){
            printf("%d ", f[i][j] ) ;
        }
        printf("\n");
        free(f[i]);
        free(memo[i]);
    }
    free(memo);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}