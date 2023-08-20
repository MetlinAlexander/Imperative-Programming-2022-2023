#include <stdio.h>

int main()
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int n;
    fscanf(in, "%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        fscanf(in, "%d", &a[i]);
    }

    for (int shag = 1; shag < n+1; shag++)
    {
        int sum = 0;
        for (int i = shag; i < n+1; i+=shag)
        {   //printf("%d+", a[i-1]);
            sum+=a[i-1];
        }
        fprintf(out, "%d\n", sum);
        //printf(" = %d\n", sum);
    }
    return 0;
}