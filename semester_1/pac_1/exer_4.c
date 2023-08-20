#include <stdio.h> 

int main() {
  int n, i;
  int flag = 1;
  scanf("%d", &n);
  int cur = n/2+1;
  if (n==1) {
    printf("NO");
    flag = 0;
  }
  for(i=2; i<cur;i++) {
    if( n%i==0) {
      printf("NO");
      flag = 0;
      i = cur;
    }
  }
  if(flag==1) {
      printf("YES");
    }
  return 0; 
}                