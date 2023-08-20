#include <stdio.h>

int main()
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int n;
    fscanf(in, "%d", &n);
    int a[n];
    for (int i = 0; i < n; i++){
        fscanf(in, "%d", &a[i]);
    }
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1;j++){
            if (a[j]>a[j+1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++){
        fprintf(out, "%d ", a[i]);
    }
    return 0;
}