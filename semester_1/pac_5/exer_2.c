#include <stdio.h>
int main() {
   int q;
   scanf("%d", &q);
   double paskal[1001][1002];
   paskal[0][0]= (double) 1;
   for(int i=1; i<=1000; i++){
      paskal[i][0] = (double) 1;
      for(int j =1; j<i; j++){
         paskal[i][j]=paskal[i-1][j-1] + paskal[i-1][j];
      }
      paskal[i][i] = (double) 1;
   }
   int k, n;
   for(int i=0; i<q; i++){
       scanf("%d %d", &n, &k);
       printf("%0.10g\n", paskal[n][k]);
   }
   return 0;
}