#include <stdio.h>
int main(){
    int n, f;
    scanf("%d %d", &n, &f);
    float mass[n];
    int ind[n];
    float ans[n];
    for(int i=0; i<n; i++){
        scanf("%f", &mass[i]);
        scanf("%d" ,&ind[i]);
        if(f==(-1)) f=0;
        //if(i==n-1) ind[i]=f;
    }
    for(int i=0; i<n; i++){
        ans[i] = mass[f];
        f=ind[f];
        //printf("%f--%d   ", mass[f], ind[f]);
    }
    //printf("\n=====%f===\n", mass[-1]);
    for(int i=0; i<n; i++){
        //printf("%0.3lf %d\n", mass[i], ind[i]);
        printf("%0.3lf\n", ans[i]);
    }
    return 0;
}

/*
5 3
4.283 2
2.718 4
5.0 -1
1.111 1
3.141 0
*/