#ifndef tests
#define tests
#include<stdlib.h>


void pol_split(int *A, unsigned lenA, int *A1, int *A2);

void test_split() {
  int *A1, *A2, len;
  int A[3] = {1, 2 , 1};
  len = 3;

  A1 = malloc((len-1)/2 * sizeof(int));
  A2 = malloc((len-1)/2 * sizeof(int));

  pol_split(A, len, A1, A2);

  assert(A1[0] == 0 && A1[1] == 1);
  assert(A2[1] == 0 && A2[2] == 1);


  free(A1);
  free(A2);

}

void test_karatsuba() {
  test_split();
}



#endif


