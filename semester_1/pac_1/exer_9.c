#include <stdio.h>

int main(void)
{
  int n;
  int a, b, c, field;
  scanf("%d", &n);
  long long answer = n + (n/2-1)*(n!=1);
  for (a = 1; a <= n; a++)
  {
    for (b = a; b <= n; b++)
    {
      for (c = b; c <= n; c++)
      {
        field = a * b * c;
        if (field <= n && c != 1 && (b!=2 || a>=2)){
          printf("%d %d %d\n", a, b, c);
          answer++;
        }
        else break;
      }
    }
  }
  printf("%lld", answer);
  return 0;
}