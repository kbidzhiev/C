#include "rg.h"

int f(int x) {

  return (x + 2)%5 + 3;
}

int main() {
  unsigned len = 0;
  unsigned res = 0;
  for(int i = 0; i < 10; ++i) {
    res = f(res);
    printf("%d ", res);
  }
  printf("\n");

  len = cycle_len(f);
  printf("len = %d\n", len);
  return 0;
}
