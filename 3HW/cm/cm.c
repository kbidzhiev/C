//#include "cm.h"
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>


typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);

int sum_arr_elem(int *sizes, int nelts, int begin, int num) {
  int i, size = 0;
  assert(begin + num <= nelts);
  for(i = 0; i < num; ++i)
    size += sizes[begin + i]; 
  return size;
}

void *arr_elem(void *mem, int* sizes, int nelts, int elem_id) {
  int shift = sum_arr_elem(sizes, nelts, 0, elem_id);
  return (void *)((char*) mem + shift);
}

void merge(void *mem, int *sizes, int nelts, int l, int m, int r, xcmp_t cmp) {
  int i, j, k, nbytes, size = 0;
  int length = r - l + 1;
  void *arr_el_j, *arr_el_k, *tmp, *tmp0;
  int *tmp_sizes;
  // compute size required for malloc
  nbytes = sum_arr_elem(sizes, nelts, l, length);

  // allocate memory for merging `sizes` elements
  tmp = malloc(nbytes * CHAR_BIT);
  tmp0 = tmp;
  tmp_sizes = (int *)malloc(length * sizeof(int));
  i = 0, j = l, k = m + 1;
  arr_el_j = arr_elem(mem, sizes, nelts, j);
  arr_el_k = arr_elem(mem, sizes, nelts, k);
  for(; (j < m + 1) && (k < r + 1); ++i) {
    if(cmp(arr_el_j, sizes[j], arr_el_k, sizes[k]) <= 0) {
      size = sizes[j];
      memcpy(tmp, arr_el_j, size);
      arr_el_j = (void *)((char*) arr_el_j + size);
      ++j;
    } else { 
      size = sizes[k];
      memcpy(tmp, arr_el_k, size);
      arr_el_k = (void *)((char*) arr_el_k + size);
      ++k;
    }
    tmp_sizes[i] = size;
    tmp = (void *)((char*) tmp + size);
  }
  
  //copy remaining elements
  for(; i < length; ++i) {
    if(j < m + 1) {
      size = sizes[j];
      memcpy(tmp, arr_el_j, size);
      arr_el_j = (void *)((char*) arr_el_j + size);
      ++j;
    } 
    if (k < r + 1) { 
      size = sizes[k];
      memcpy(tmp, arr_el_k, size);
      arr_el_k = (void *)((char*) arr_el_k + size);
      ++k;
    }
    tmp_sizes[i] = size;
    tmp = (void *)((char*) tmp + size);
  }

  //copy all from *tmp to *mem
  //tmp = (void *)((char*) tmp - nbytes);
  tmp = tmp0;
  mem = arr_elem(mem, sizes, nelts, l);
  for(i = l; i < r + 1; ++i) {
    size = tmp_sizes[i - l];
    //copy
    memcpy(mem, tmp, size);
    sizes[i] = tmp_sizes[i - l];
    // iterate next
    tmp = (void *)((char*) tmp + size);
    mem = (void *)((char*) mem + size);
  }

  free(tmp0);
  free(tmp_sizes);
}

void xmsort_impl(void *mem, int *sizes, int nelts, int l, int r, xcmp_t cmp) {
  int m = l + (r - l) / 2;
  if (l >= r)
    return;
  xmsort_impl(mem, sizes, nelts, l, m, cmp);
  xmsort_impl(mem, sizes, nelts, m + 1, r, cmp);
  merge(mem, sizes, nelts, l, m, r, cmp);
}


void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp) {
  xmsort_impl(mem, sizes, nelts, 0, nelts - 1, cmp);
}

