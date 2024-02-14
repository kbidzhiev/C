#include "cm.h"
#include <stdlib.h>
#include <assert.h>
#include <limits.h>


typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);

int sum_arr_elem(int *sizes, int nelts, int begin, int num) {
  int i, size = 0;
  assert(begin + num <= nelts);
  for(i = 0; i < num; ++i) {
    size += sizes[begin + i]; 
  }
  return size;
}

void *arr_elem(void *mem, int* sizes, int nelts, int elem_id) {
  int shift = sum_arr_elem(sizes, nelts, 0, elem_id);
  return (void *)((char*) mem + shift);
}

void merge(void *mem, int *sizes, int nelts, int l, int m, int r, xcmp_t cmp) {
  int i, j, k, nbytes, min;
  int size = r - l + 1;
  void *arr1, *arr2;
  void *tmp;


  // compute size required for malloc
  nbytes = sum_arr_elem(sizes, nelts, l, size);

  // allocate memory for merging `size` elements
  tmp = malloc(nbytes * CHAR_BIT);

  //copy elements from [l;m] and [m+1;r] to *tmp
  i = 0, j = l, k = m + 1;
  for(; i < (j < m + 1) && (k < r + 1); ++i) {
    arr_el_j = arr_elem(mem, sizes, nelts, j);
    arr_el_k = arr_elem(mem, sizes, nelts, k);
    if( cmp(arr_el_j, sizes[j], arr_el_k, sizes[k]) <= 0) {
      memcpy(tmp, arr_el_j, nelts[j]);
      tmp = (void *)((char*) tmp + nelts[j]);
      ++j;
    } else { 
      memcpy(tmp, arr_el_k, nelts[k]);
      tmp = (void *)((char*) tmp + nelts[k]);
      ++k;
    }
  }
  //copy remaining elements

  
  
  //copy all from *tmp to *mem
  free(tmp);//free tmp !
}

#if 0
void xmsort_impl(void *mem, int *sizes, int nelts, int l, int r, xcmp_t cmp) {
  int m = l + (r - l) / 2;
  if (l >= r)
    return;
  xmsort_impl(mem, sizes, nelts, l, m, cmp);
  xmsort_impl(mem, sizes, nelts, m + 1, r, cmp);
  merge(mem, sizes, nelts, l, m, r, cmp);
}



void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp) {
  xmsort_imp(mem, sizes, nelts, 0, nelts - 1, xcmp_t cmp);
}
#endif
