#include <stdio.h>

int main()
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int n;
    fscanf(in, "%d", &n);
    int a[n];
    for(int i = 0; i<n; i++)
        fscanf(in, "%d", &a[i]);
    int max_sum = -100000;
    int r = 100000;
    int l = 100000;
    for(int i = 0; i<n; i++){
        int cur_sum = 0;
        for(int j = i; j<n; j++){
            cur_sum += a[j];
            if (cur_sum > max_sum){
                l =i;
                r = j;
                max_sum = cur_sum;
            }
        }
    }
    fprintf(out, "%d %d %d", l, r, max_sum);
    return 0;
}