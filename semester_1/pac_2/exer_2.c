#include <stdio.h>
#include <string.h>
int main(void) {
  FILE *in = fopen("input.txt", "r");
  FILE *out = fopen("output.txt", "w");
  int size = 4;
  char day[size];
  fscanf(in, "%s", day);
  if (strcmp(day, "Mon")==0) fprintf(out, "%d", 1);
  else if (strcmp(day, "Tue")==0) fprintf(out, "%d", 2);
  else if (strcmp(day, "Wed")==0) fprintf(out, "%d", 3);
  else if (strcmp(day, "Thu")==0) fprintf(out, "%d", 4);
  else if (strcmp(day, "Fri")==0) fprintf(out, "%d", 5);
  else if (strcmp(day, "Sat")==0) fprintf(out, "%d", 6);
  else if (strcmp(day, "Sun")==0) fprintf(out, "%d", 7);
  fclose(in);
  fclose(out);
  return 0;
}