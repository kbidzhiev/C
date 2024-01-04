#include"tests.h"
#include<stdlib.h>
#include<assert.h>

void test_split() {
  // x2 + 2x + 1 == (x + 0)*x + (2x + 1)
  int *A1, *A2, len;
  int A[3] = {1, 2 , 1};
  len = 3;

  A1 = malloc((len+1)/2 * sizeof(int));
  A2 = malloc((len+1)/2 * sizeof(int));

  pol_split(A, len, A1, A2);

  assert(A1[0] == 0 && A1[1] == 1); // 1x + 0
  assert(A2[0] == 1 && A2[1] == 2); // 2x + 1


  free(A1);
  free(A2);

}

void test_karatsuba() {
  test_split();
}



