#include <stdio.h>

int main(void) {
  int n;
  int prime = 1;
  scanf("%d", &n);
  int i;
  for (i = 2; i < n + 1; i++) {
    for (int j=2; j < i / 2+1; j++) {
      if (i % j == 0) {
        prime = 0;
        break;}
    }
    if (prime == 1) printf("%d\n", i);
    prime = 1;
  }
  return 0;
}