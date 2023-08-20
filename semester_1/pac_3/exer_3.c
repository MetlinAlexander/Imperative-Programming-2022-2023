#include <stdio.h>

int main()
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int n;
    fscanf(in, "%d", &n);
    int a[10000] = {0};
    int cur;
    for (int i = 0; i < n; i++){
        fscanf(in, "%d", &cur);
        a[cur-1]++;
    }
    for(int i = 0; i<10000; i++){
        if (a[i]!=0) {
            fprintf(out, "%d: %d\n", i+1, a[i]);
            }
    }
    return 0;
}