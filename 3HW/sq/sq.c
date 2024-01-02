#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

unsigned first_high_from_left(int* arr, unsigned pivot_pos, unsigned from, unsigned to) {
  for(unsigned i = from; i <= to; ++i)
    if (arr[i] > arr[pivot_pos])
      return i;
  return to;
}
unsigned first_low_from_right(int* arr, unsigned pivot_pos, unsigned from, unsigned to) {
  for(unsigned i = from; i >= to; --i)
    if (arr[i] <= arr[pivot_pos])
      return i;
  return to;
}

unsigned partition(int *arr, unsigned low, unsigned high) {
  unsigned pivot_pos = low;
  unsigned left_high, right_low;
  ++low;

  while(low < high) {
    left_high = first_high_from_left(arr, pivot_pos, low, high);
    right_low = first_low_from_right(arr, pivot_pos, high, low);
    if (left_high < right_low) {
      swap(&arr[left_high], &arr[right_low]);
    }
    low = left_high;
    high = right_low;
  }
  if (arr[pivot_pos] != arr[high]) {
    swap(&arr[pivot_pos], &arr[high]);
  }
  return high;
}
#if 0

void qsort_impl(int *arr, unsigned low, unsigned high) {
  unsigned pi;
  if (low >= high)
    return;
  pi = partition(arr, low, high);
  if (pi > low)
    qsort_impl(arr, low, pi - 1);
  qsort_impl(arr, pi + 1, high);
}

void qqsort(int *arr, unsigned len) {
  qsort_impl(arr, 0u, len - 1);
}

void test_swap() {
  int a = 5, b = 10;
  swap(&a, &b);
  assert(a == 10 && b == 5);
}
void test_find() {
  unsigned left_high, right_low;
  int arr[8] = {6, 1, 9, 3, 2, 8, 7, 4};

  unsigned pivot_pos = 0, low = 1, high = 7;

  left_high = first_high_from_left(arr, pivot_pos, low, high);
  right_low = first_low_from_right(arr, pivot_pos, high, low);
  assert(arr[left_high] == 9 && arr[right_low] == 4);
  low = left_high;
  high = right_low;
  assert(arr[low] == 9 && arr[high] == 4);
  swap(&arr[low], &arr[high]);

  left_high = first_high_from_left(arr, pivot_pos, low, high);
  right_low = first_low_from_right(arr, pivot_pos, high, low);
  low = left_high;
  high = right_low;
  assert(low == 5 && high == 4);
}

void test_partition() {
  int low = 0, high = 2;
  int a[3] = {2, 1, 3};
  unsigned res = partition(a, low, high);

  assert(1 == res);
  assert(1 == a[0] && 2 == a[1] && 3 == a[2]);

  low = 0, high = 2;
  a[0] = a[1] = a[2] = 1;

  res = partition(a, low, high);

  assert(2 == res);
  assert(1 == a[0] && 1 == a[1] && 1 == a[2]);
}

void test_sort() {
  int i;
  int a[8] = {6, 1, 9, 3, 2, 8, 7, 4};
  int res[8] = {1, 2, 3, 4, 6, 7, 8, 9};

  qqsort(a, 8);
  for(i = 0; i < 8; ++i) {
    assert(a[i] == res[i]);
  }

}

void test() {
  test_swap();
  test_find();
  test_partition();
  test_sort();
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
