#include <stdio.h>
int main()
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int l, r, k;
    fscanf(in, "%d %d %d", &l, &r, &k);
    int mx = r - l;
    int step = mx / (k - 1);
    int a_n;
    int answer = 0;
    for (int i = step; i > 0; i--)
    {
        a_n = (k - 1) * i;
        if (mx - a_n + 1 > i)
            answer += i;
        else
            answer += mx - a_n + 1;
    }
    fprintf(out, "%d", answer);
    fclose(in);
    fclose(out);
    return 0;
}