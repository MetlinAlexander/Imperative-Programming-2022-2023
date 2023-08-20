#include <stdio.h>

int main(void) {
  int n, answer;
  scanf("%d", &n);
  answer = (int)(n + 1) * n * 0.5;
  printf("%d", answer);
  return 0;
}