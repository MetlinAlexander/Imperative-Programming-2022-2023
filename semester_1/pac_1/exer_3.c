#include <stdio.h>

int main(void) {
  int i, size, cur;
  scanf("%d", &size);
  int sum_chet = 0;
  for(i=0; i < size; i++) {
    scanf("%d", &cur);
    if (cur%2==0) {
      sum_chet+=cur;
    }
  }
  printf("%d", sum_chet);
  return 0;
}