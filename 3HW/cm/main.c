#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cm.h>



//void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp);


int find_end(int *sizes, int nelts);
int find_mid(int *sizes, int nelts);

void test_find_bound(int k) {
  int sizes[5] = {1, 2, 3, 4, 5};
  int sizes2[6] = {2, 4, 6, 8, 10, 12};

  assert(10 == find_end(&sizes, 5);
  assert(3 == find_mid(&sizes, 5);
  

  assert(30 == find_end(&sizes2, 6);
  assert(12 == find_mid(&sizes2, 6);
  printf("%d) test_find_end\n"; k);
}

void test_all(void) {
  test_find_end(1);
}


int main(void) {
  test_all();
  return 0;
}
