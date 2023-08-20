#include <stdio.h>
int main()
{   
    // scan input
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int sv_1 = 1;
    int sv_2 = 2;
    int sv_3 = 3;
    int sv_4 = 4;
    int sv_5 = 5;
    int n, m;
    fscanf(in, "%d %d", &n, &m);
    int r[301]={0};
    int y_opr[301]={0};
    int x, y;
    int colovo_x = 0;
    int y_colovo = 0;
    // scan pairs
    for(int i=0; i<m; i++){
        fscanf(in, "%d %d", &x, &y);
        if(r[x]!=0){
            sv_1=0;
            fprintf(out, "%d", sv_1);
            return 0;
        }
        else{
            r[x]=y;
            colovo_x++;
            if(y_opr[y]!=0)
                sv_3=0;
            else y_colovo++;

            y_opr[y]=y;
        }
    }
    //check 1 questions
    fprintf(out, "%d ", sv_1);

    //check 2 questions
    if(colovo_x==n)
        fprintf(out, "%d ", sv_2);

    //check 3 questions
    if (sv_3==3)
        fprintf(out, "%d ", sv_3);
    //check 4 questions
    if (y_colovo==n)
        fprintf(out, "%d ", sv_4);
    else sv_4=0;
    //check 5 questions
    if (sv_3!=0 && sv_4!=0)
        fprintf(out, "%d ", sv_5);
    return 0;
}