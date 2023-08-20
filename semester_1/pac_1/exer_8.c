#include <stdio.h>

int main() {
  int h, m, s, k;
  scanf("%d %d %d %d", &h, &m, &s, &k);
  int sec_cur = h*3600 + m*60 + s;
  int future_time = sec_cur + k;
  int fut_h = (future_time/3600)%24;
  int fut_m = ((future_time - fut_h*3600) / 60)%60;
  int fut_s = (future_time - fut_h*3600 - fut_m*60)%60;
  printf("%d %d %d", fut_h, fut_m, fut_s);
}