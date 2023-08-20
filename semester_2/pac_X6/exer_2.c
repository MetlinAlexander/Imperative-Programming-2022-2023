#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
// #define INF
int **memo;
int mod = 1000000007;
int N;

int Rec(int Sum, int Last)
{
    if (memo[Sum][Last] == -1)
    { // -1 в memo означает, что значение ещё не вычислено
        int res = 0;
        if (Sum == N)
            res = 1; // разбиение построено: один вариант
        else
        {
            for (int x = 1; x <= MIN(Last, N - Sum); x++) // перебираем все допустимые x
                res = (res + Rec(Sum + x, x))%mod;                   // запускаем перебор хвоста последовательности
        }
        memo[Sum][Last] = res; // запоминаем результат в memo
    }
    return memo[Sum][Last]; // возвращаем запомненный результат
}

int main()
{
    // open files
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    // scan data
    fscanf(in, "%d\n", &N);
    // mem for rez
    memo = (int **)malloc(sizeof(int *) * (N + 1));
    for (int i = 0; i < N + 1; i++)
    {
        memo[i] = (int *)malloc(sizeof(int) * (N + 1));
        for (int j = 0; j < N + 1; j++)
        {
            memo[i][j] = -1;
        }
    }
    // solve
    // print ans
    fprintf(out, "%d\n", Rec(0, N));
    // free
    for (int i = 0; i < N + 1; i++)
    {
        free(memo[i]);
    }
    free(memo);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}