#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cm.h"



//void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp);



void test_all(void) {
  test_find_bound(1);
}


int main(void) {
  test_all();
  return 0;
}
