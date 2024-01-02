#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

void merge(int *arr, int l, int m, int r) {
  int *tmp;
  int i, j, k;
  int size = r - l + 1;

  assert(size > 0);
  tmp = (int*)malloc(size * sizeof(int));
  if (NULL == tmp) {
    abort();
  }

  i = 0;
  j = l;
  k = m + 1;
  for(i = 0; (j < m + 1) && (k < r + 1); ++i) {
    tmp[i] = (arr[j] <= arr[k]) ? arr[j++] : arr[k++];
  }

  for(; i < size; ++i) {
    if((j == m + 1) && (k < r + 1))
      tmp[i] = arr[k++];
    if((k == r + 1) && (j < m + 1))
      tmp[i] = arr[j++];
  }

  for (i = 0; i < size; ++i){
    arr[i + l] = tmp[i];
  }
  free(tmp);
}

#if 0

void merge_sort_imp(int *arr, int l, int r) {
  int m;
  if (l >= r)
    return;
  m = (l + r) / 2;
  merge_sort_imp(arr, l, m);
  merge_sort_imp(arr, m + 1, r);
  merge(arr, l, m, r);
}

void merge_sort(int *arr, int n) {
  merge_sort_imp(arr, 0, n - 1);
}

void test_merge() {
  int i, l, m, r;
  int a[8] = {1, 3, 6, 9, 2, 4, 7, 8};
  int res[8] = {1, 2, 3, 4, 6, 7, 8, 9};
  l = 0;
  r = 7;
  m = (r - l)/ 2;
  merge(a, l, m ,r);

  for(i = 0; i < 8; ++i) {
    assert(a[i] == res[i]);
  }
}

void test_sort() {
  int i;
  int a[8] = {6, 1, 9, 3, 2, 8, 7, 4};
  int r[8] = {1, 2, 3, 4, 6, 7, 8, 9};
  merge_sort(a, 8);

  for(i = 0; i < 8; ++i) {
    assert(a[i] == r[i]);
  }
}

void test_merge_small() {
  int i;
  int a[3] = {2, 1, 3};
  int b[3] = {1, 3, 2};
  int c[3] = {1, 2, 3};

  merge(a, 0, 0, 2);
  merge(b, 0, 1, 2);
  merge(c, 0, 0, 2);

  assert(1 == a[0] &&  2 == a[1] && 3 == a[2]);
  assert(1 == b[0] &&  2 == b[1] && 3 == b[2]);
  assert(1 == c[0] &&  2 == c[1] && 3 == c[2]);
}
void test() {
  test_merge_small();
  test_merge();
  test_sort();
}

int main() {
  test();
  return 0;
}
#endif
