#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cm.h"



//void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp);

int sum_arr_elem(int *sizes, int nelts, int begin, int num);
void test_sum_arr_elem(int k) {
  int sizes[6] = {3, 5, 9, 1, 2, 8};
  int begin = 2, num = 1;
  assert(9 == sum_arr_elem(sizes, 6, begin, num));

  begin = 0, num = 2;
  assert(8 == sum_arr_elem(sizes, 6, begin, num));
  
  begin = 1, num = 5;
  assert(25 == sum_arr_elem(sizes, 6, begin, num));

  printf("%d. test_sum_arr_elem - OK;\n", k);
}

void test_all(void) {
  test_sum_arr_elem(1);
}


int main(void) {
  test_all();
  return 0;
}
