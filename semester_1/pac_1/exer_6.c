#include <stdio.h>

int main() {
  int n, cur;
  scanf("%d", &n);
  int mn = 10001;
  int mx = -10001;
  int n_mn, n_mx;
  if (n == 1) {
    scanf("%d", &cur);
    printf("%d %d %d %d", cur, 1, cur, 1);
  } 
  else {
    for (int i = 0; i < n; i++) {
      scanf("%d", &cur);
      if (cur > mx) {
        mx = cur;
        n_mx = i+1;
      }
      if (cur < mn) {
        mn = cur;
        n_mn=i+1;
      }
    }
    printf("%d %d %d %d", mn, n_mn, mx, n_mx);
  }
  
  return 0;
}