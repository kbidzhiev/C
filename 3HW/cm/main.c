#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cm.h"



//void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp);
//typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);

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

int cmp(void *lhs, int lsz, void *rhs, int rsz) {
  int l, r;
  if (lsz != rsz) {
    assert(0);
  }
  l = *(int *)lhs;
  r = *(int *)rhs;
  if (l < r) return -1;
  if (l > r) return 1;
  return 0;
}

void test_sorting(int k) {
  int s = sizeof(int);
  int arr[4] = {3, 2, 6, 1};
  int sizes[4] = {s, s, s, s};
  for(s = 0; s < 4; ++s) {
    printf("%d ", arr[s]);
  }
  printf("\n");

  xmsort(arr, sizes, 4, cmp);
  
  for(s = 0; s < 4; ++s) {
    printf("%d ", arr[s]);
  }
  printf("\n");
  assert(1 == arr[0]); 
  assert(2 == arr[1]); 
  assert(3 == arr[2]); 
  assert(6 == arr[3]);

  printf("%d. test_sorting - OK;\n", k);
}


void test_all(void) {
  test_sum_arr_elem(1);
  test_sorting(2);
  printf("All tests are OK\n");
}


int main(void) {
  test_all();
  return 0;
}
