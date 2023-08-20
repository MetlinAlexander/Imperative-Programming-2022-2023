#include <stdio.h>

int main()
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int n;
    fscanf(in, "%d", &n);
    printf("%d\n", n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        fscanf(in, "%d", &a[i]);
    }
    for (int i = 0; i < n; i++)
    {
        int cur = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] > a[j])
                cur++;
        }
        fprintf(out, "%d ", cur);
    }
    return 0;
}