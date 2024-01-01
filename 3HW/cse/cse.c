#include<stdio.h>
#include<stdlib.h>

void copyto(void *to, void *from, unsigned eltsize) {
  unsigned i;
  for (i = 0; i < eltsize; ++i) {
    *((char *)to + i) = *((char*)from + i);
  }
}

void swap(void *lhs, void *rhs, unsigned eltsize) {
  void *tmp = malloc(eltsize * sizeof(char));
  if (NULL == tmp) {
    abort();
  }
  copyto(tmp, lhs, eltsize);
  copyto(lhs, rhs, eltsize);
  copyto(rhs, tmp, eltsize);
}

typedef int (*cmp_t)(void const * lhs, void const * rhs);

unsigned find_min(void const *parr, unsigned eltsize, unsigned numelts, unsigned begin, cmp_t cmp) {
  unsigned i, min = begin;
  char const *arr = parr;
  for (i = begin + 1; i < numelts; ++i) {
    if ( cmp((void const*)(arr + i * eltsize), (void const*)(arr + min * eltsize))) {
      min = i;
    }
  }
  return min;
}

int selstep(void *parr, int eltsize, int numelts, int nsorted, cmp_t cmp) {
  void* min_elem;
  void* first_elem = (char*)parr + nsorted * eltsize;
  unsigned min_pos = find_min(parr, eltsize, numelts, nsorted, cmp);
  min_elem = (char*)parr + min_pos * eltsize;
  swap(first_elem, min_elem, eltsize);
  return 0;
}

#if 0
int cmp(void const * lhs, void const *rhs);

int main() {
  int a[5] = {3, 2, 1, 5, 4};
  int i = 0;
  int size = 5;
  void* arr = a;

  for (i = 0; i < size; ++i) {
    selstep(arr, sizeof(a[0]), size, i, cmp);
  }

  for (i = 0; i < size; ++i) {
    printf("%d\n", a[i]);
  }

  return 0;
}


int cmp(void const * lhs, void const * rhs) {
  int l = *(int*)lhs;
  int r = *(int*)rhs;
  return l < r;
}
#endif
