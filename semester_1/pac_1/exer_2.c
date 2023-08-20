#include <stdio.h>

int main(void) {
  int x, y, z;
  scanf("%d %d %d", &x, &y, &z);
  if (x<=0) printf("%d", (-1));
  else if (y<=0) printf("%d", (-2));
  else if (z<=0) printf("%d", (-3));
  else {
    int surface = (int) 2*x*y + 2*y*z + 2*z*x;
    printf("%d", surface);
  }
  return 0;
}