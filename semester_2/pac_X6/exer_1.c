#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
FILE *in;
FILE *out;
char field[13][13];
int col[40];
int hasV[40], hasS[40];
int hasD[40];
int N, M; //𝑀 — количество строк и 𝑁 — количество столбцов
char solve_exist='f';
void Rec(int r)
{
    if (r == M && solve_exist=='f'){   
        solve_exist='t';
        fprintf(out, "YES\n");
        for(int i=0; i<M; i++){
            for(int j=0; j<N; j++){
                if(col[i]==j){
                    fprintf(out, "X");
                    continue;
                }
                fprintf(out, ".");
            }
            fprintf(out, "\n");
        }
        // print(col); // нашли решение --- печатаем его
        return;     // проверять решение НЕ надо, т.к. все проверки на "бьёт" выполнены ранее в отсечениях
    }
    for (int c = 0; c < N; c++)
    {
        if (hasV[c]==1 || hasS[r + c]==1 || hasD[12 + r - c]==1 || field[r][c]=='.'){ // отсечение: если вертикаль или диагонали уже бьются
            continue;            //           тогда ставить ферзя НЕ будем
        } 
                                        

        
        col[r] = c;                              // ставим ферзя в клетку
        hasV[c] = 1;
        hasS[r + c] = 1;
        hasD[12 + r - c] = 1; // обновляем глобальное состояние

        Rec(r + 1); // запускаем перебор всех вариантов для r+1 и последующих строк

        hasV[c] = 0;
        hasS[r + c] = 0;
        hasD[12 + r - c] = 0; // откатываем изменения, возвращая в точности состояние до установки ферзя
        col[r] = c;                               // (мы уверены, что hasX[?] все имели значение 0 до того, как мы записали туда 1)
    }
}

int main()
{
    // open files
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    // scan 𝑀 — количество строк и 𝑁 — количество столбцов
    fscanf(in, "%d %d\n", &M, &N);
    // printf("M=%d; N=%d\n", M, N);
    // scan filed
    // char field[M][N + 1];
    for (int i = 0; i < M; i++)
    {
        fscanf(in, "%s\n", field[i]);
        field[i][N] = '\0';
        // printf("[%s]\n", field[i]);
    }
    //solve
    for(int i=0; i<40; i++){
        col[i]=-1;
        hasV[i]=0;
        hasS[i]=0;
        hasD[i]=0;
    }
    Rec(0);
    //print answer
    if(solve_exist=='f'){
        fprintf(out, "NO\n");
    }
    // for(int i=0; i<M; i++){
    //     printf("%d ", col[i]);
    // }
    // printf("\n%c\n", solve_exist);
    // CLOSE FILES
    fclose(in);
    fclose(out);
    return 0;
}