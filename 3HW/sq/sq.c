#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

unsigned first_high_from_left(int* arr, unsigned pivot_pos, unsigned from, unsigned to) {
  for(unsigned i = from; i < to; ++i)
    if (arr[i] > arr[pivot_pos])
      return i;
  return to;
}
unsigned first_low_from_right(int* arr, unsigned pivot_pos, unsigned from, unsigned to) {
  for(unsigned i = from-1; i >= to; --i)
    if (arr[i] <= arr[pivot_pos])
      return i;
  return to;
}

unsigned partition(int *arr, unsigned low, unsigned high) {
  unsigned pivot_pos = low;
  unsigned left_high, right_low;

  left_high = first_high_from_left(arr, pivot_pos, low, high);
  right_low = first_low_from_right(arr, pivot_pos, high, low);

  return 0u;
}
void qsort_impl(int *arr, unsigned low, unsigned high) {
  if (low >= high) return;
  unsigned pi = partition(arr, low, high);
  if (pi > low) qsort_impl(arr, low, pi - 1);
  qsort_impl(arr, pi + 1, high);
}

#if 1
//void qsort(int *arr, unsigned len) {
//  qsort_impl(arr, 0u, len - 1);
//}

void test_swap() {
  int a = 5, b = 10;
  swap(&a, &b);
  assert(a == 10 && b == 5);
}
void test_find() {
  int arr[8] = {6, 1, 9, 3, 2, 8, 7, 4};
  unsigned pivot_pos = 0, low = 1, high = 8;
  unsigned left_high = first_high_from_left(arr, pivot_pos, low, high);
  unsigned right_low = first_low_from_right(arr, pivot_pos, high, low);

  assert(arr[left_high] == 9 && arr[right_low] == 4);

}

void test() {
  test_swap();
  test_find();
}

int main() {
  test();
  unsigned res = 0;
  int a[3] = {2, 1, 3};

  res = partition(a, 0, 2);
  printf("%d\n", res);


  return 0;
}

#endif
