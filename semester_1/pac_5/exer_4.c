#include <stdio.h>
int main(){
    // scan n and q
    int n, q;
    scanf("%d %d", &n, &q);
    // make resheto erastrofeno
    int resheto[n];
    for(int i=0; i<n; i++)
        resheto[i]=1;
    resheto[0]=0;
    resheto[1]=0;
    for(int i=2; i<n; i++){
        if (resheto[i]==1){
        for(int j =i+i; j<n; j+=i){
            resheto[j]=0;
        }
        }
    }
    // answer
    int zapros;
    for(int i=0; i<q; i++){
        scanf("%d", &zapros);
        printf("%d ", zapros);
        if(resheto[zapros]==1)
            printf("prime\n");
        else 
            printf("not\n");
    }
    return 0;
}