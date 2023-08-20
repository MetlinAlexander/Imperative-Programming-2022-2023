#include <stdio.h>
#include <math.h>
#include <ctype.h>
int main()
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int n;
    fscanf(in, "%d", &n);
    char a[n];
    char pr;
    int s_sistem = 0;
    int digit;
    for (int i = 0; i < n; i++){
        fscanf(in, "%c", &pr);
        fscanf(in, "%c", &a[i]);
        digit = (int) a[i] - 96;
        if (s_sistem<digit) s_sistem=digit;
    }
    printf("%d\n", s_sistem);
    for(int i=0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n ");
    // make decem number
    int decem = 0;
    char cur;
    for(int i=n-1; i>=0; i--){
        cur = a[i];
        digit = (int) cur - 97;
        printf("%d ", digit);
        decem += digit * pow(s_sistem, n-i-1);
    }
    printf("%d", decem);
    return 0;
}