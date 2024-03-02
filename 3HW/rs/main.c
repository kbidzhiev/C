#include <stdio.h>
#include <stdlib.h>


struct arr_t {
  int size;
  int *p;
};
struct arr_calloc(int size) {
  struct arr_t arr;
  arr.size = size;
  arr.p = calloc(size, sizeof(int));
  if (NULL == arr.p)
    abort();
  return arr;
}
void arr_free(struct arr_t *arr) {
  arr -> size = 0;
  free(arr -> p);
}

int main(void) {



  return 0;
}
