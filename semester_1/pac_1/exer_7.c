#include <stdio.h>

int main() {
  int n;
  int m, p, k, l;
  scanf("%d", &n);
  scanf("%d %d %d %d", &m, &p, &k, &l);
  int col_floors_before_M = (p-1)*l +(k-1);
  int col_flat_on_floor = m/col_floors_before_M;
  //printf("%d %d\n", col_floors_before_M, col_flat_on_floor);
  int flats_in_entrance = l*col_flat_on_floor;
  int entrance_n = n/(flats_in_entrance) + 1*(n%(l*col_flat_on_floor)!=0);
  int floor_n = n/col_flat_on_floor + 1*(n%col_flat_on_floor!=0) - l*(entrance_n-1);
  printf("%d %d", entrance_n, floor_n);
  return 0;
}