#include <stdio.h>

int main(void) {
  int a, b;
  scanf("%d %d", &a, &b);
  if (a>0) {
    printf("%d %d %d %d", a/b, a/b+1*(a%b!=0), a/b, a%b);
  }
  else if (a<0){
    printf("%d %d %d %d", a/b-1*(a%b!=0), a/b, a/b, (b-(a*(-1)%b))*(a%b!=0));
  }
  else printf("%d %d %d %d", 0, 0, 0, 0);
  return 0;
}
