#include<stdio.h>
#include<stdlib.h>


typedef int (*cmp_t)(const void *lhs, const void *rhs);

void const *shiftptr(const void * ptr, int shift, int size) {
  return (void const*)((char const*) ptr + shift * size);
}

void *cbsearch(const void *key, const void *base, int num, int size, cmp_t cmp) {
  int m, l = 0, r = num - 1;
  int comp;
  void const *lp = shiftptr(base, l, size);
  void const *rp = shiftptr(base, r, size);
  void const *mp;

  while (l <= r) {
    m = l + (r - l)/2;
    mp = shiftptr(base, m, size);
    comp = cmp(mp, key);
    if (comp == 0) {
      return (void *)((char *) base + m*size);
    }
    if (comp < 0) {
      l = m + 1;
      lp = shiftptr(base, l, size);
    };
    if (comp > 0) {
      r = m - 1;
      rp = shiftptr(base, r, size);
    }
  }

  return NULL;

}

#if 0
int cmp(void const * lhs, void const * rhs);

int main() {
  void * res;
  int a[6] = {1, 2, 3, 4, 5, 6};
  int key = 0;
  res = cbsearch(&key, a, 6, sizeof(a[0]), cmp);

  if (res == NULL) {
    printf("Null\n");
    return 0;
  }
  printf("%d\n", *(int*)res);

  return 0;
}

int cmp(void const * lhs, void const * rhs) {
  return (*(int *)lhs) > (*(int *)rhs);
}

#endif
