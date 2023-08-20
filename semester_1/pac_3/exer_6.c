#include <stdio.h>

int main()
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int n;
    fscanf(in, "%d", &n);
    int a[100001] = {0};
    int cur;
    int count = n;
    for (int i = 0; i < n; i++){
        fscanf(in, "%d", &cur);
        if (a[cur]!=0) count-=1; 
        a[cur]=1;
    }
    fscanf(in, "%d", &n);
    for (int i = 0; i < n; i++){
        fscanf(in, "%d", &cur);
        if (a[cur]!=0) count-=1;
        a[cur]=0;
    }
    fprintf(out, "%d\n", count);
    int cn=0;
    for(int i = 0; i<100001; i++){
        if (cn>=count) break;
        if (a[i]!=0) {
            fprintf(out, "%d ", i);
            cn++;
            }
    }
    return 0;
}