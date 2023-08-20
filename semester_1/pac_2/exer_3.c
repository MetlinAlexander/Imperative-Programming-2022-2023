#include <stdio.h>
int main(void) {
  FILE *in = fopen("input.txt", "r");
  FILE *out = fopen("output.txt", "w");
  int n;
  int plus = 0; 
  int minus = 0;
  int zero = 0;
  fscanf(in, "%d", &n);
  for (int i = 0; i < n; i++) {
    int cur;
    fscanf(in, "%d", &cur);
    if (cur > 0)
      plus++;
    else if (cur < 0)
      minus++;
    else
      zero++;
  }
  double ans_m = minus/(double) n;
  double ans_z = zero/(double) n;
  double ans_p = plus/(double) n;
  fprintf(out, "%0.5lf %0.5lf %0.5lf", ans_m, ans_z, ans_p);
  fclose(in);
  fclose(out);
  return 0;
}