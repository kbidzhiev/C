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

void *arr_elem(void *mem, int* sizes, int nelts, int elem_id);
void test_shift(int k) {
  int el;
  int s = sizeof(int);
  int arr[6] = {3, 5, 9, 1, 2, 8};
  int sizes[6] = {s, s, s, s, s ,s};
  
  el = *(int *)arr_elem(arr, sizes, 6, 1);
  assert(5 == el);

  el = *(int *)arr_elem(arr, sizes, 6, 5);
  assert(8 == el);

  printf("%d. Test shift - OK;\n", k);
}


int cmp(void *lhs, int lsz, void *rhs, int rsz) {
  int l, r;
  l = *(int *)lhs;
  r = *(int *)rhs;
  if (l < r) return -1;
  if (l > r) return 1;
  return 0;
}

void test_sorting_1(int k) {
  int s = sizeof(int);
  int arr[4] = {3, 2, 6, 1};
  int sizes[4] = {s, s, s, s};
  printf("before sorting\n");
  for(s = 0; s < 4; ++s) {
    printf("%d\t weight %d\n", arr[s], sizes[s]);
  }
  printf("\n");

  xmsort(arr, sizes, 4, cmp);
  
  for(s = 0; s < 4; ++s) {
    printf("%d\t weight %d\n", arr[s], sizes[s]);
  }
  printf("\n");
  assert(1 == arr[0]); 
  assert(2 == arr[1]); 
  assert(3 == arr[2]); 
  assert(6 == arr[3]);

  printf("%d. test_sorting_1 - OK;\n", k);
}

void test_sorting_2(int k) {
  int s = sizeof(int);
  int arr[7] = {3, 2, 6, 1, 9, -2, 3};
  int sizes[7] = {s, s, s, s, s, s, s};
  for(s = 0; s < 7; ++s) {
    printf("%d\t weight %d\n", arr[s], sizes[s]);
  }
  printf("\n");

  xmsort(arr, sizes, 7, cmp);
  
  for(s = 0; s < 7; ++s) {
    printf("%d\t weight %d\n", arr[s], sizes[s]);
  }
  printf("\n");
  assert(-2 == arr[0]); 
  assert(1 == arr[1]); 
  assert(2 == arr[2]); 
  assert(3 == arr[3]);
  assert(3 == arr[4]);
  assert(6 == arr[5]);
  assert(9 == arr[6]);

  printf("%d. test_sorting_2 - OK;\n", k);
}

void test_sorting_3(int k) {
  int size = 10;
  int s = sizeof(int);
  int arr[10] = {8, 9, 9, 7, 1, 7, 9, 9, 1, 8};
  int sizes[10] = {s, s, s, s, s, s, s, s, s, s};
  for(s = 0; s < size; ++s) {
    printf("%d\t weight %d\n", arr[s], sizes[s]);
  }
  printf("\n");

  xmsort(arr, sizes, size, cmp);
  
  for(s = 0; s < size; ++s) {
    printf("%d\t weight %d\n", arr[s], sizes[s]);
  }
  printf("\n");
  assert(1 == arr[0]); 
  assert(1 == arr[1]); 
  assert(7 == arr[2]); 
  assert(7 == arr[3]);
  assert(8 == arr[4]);
  assert(8 == arr[5]); 
  assert(9 == arr[6]);
  assert(9 == arr[7]);
  assert(9 == arr[8]);
  assert(9 == arr[9]);
  printf("%d. test_sorting_3 - OK;\n", k);
}
void test_all(void) {
  test_sum_arr_elem(1);
  test_shift(2);
  test_sorting_1(3);
  test_sorting_2(4);
  test_sorting_3(5);
  printf("All tests are OK\n");
}


int main(void) {
  test_all();
  return 0;
}
