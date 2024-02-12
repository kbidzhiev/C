#include <cm.h>
#include <stdlib.h>


#if 0
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
#endif


typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);


void xmsort_imp(void *mem, int l, int r);

int find_end(int *sizes, int nelts) {
  return find_boundary(sizes, nelts, nelts - 1);
}

int find_mid(int *sizes, int nelts, int boundary) {
  return find boundary(sizes, nelts, nelts/2);
}

int find_boundary(int *sizes, int nelts, int boundary) {
  int end = 0, i = 0;
  for (; i < nelts - 1; ++i)
    end += sizes[i];

  return end;
}
void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp) {
  int l = 0;
  int r = find_end(sizes, nelts);
  xmsort_imp(*mem, l, r);
}
