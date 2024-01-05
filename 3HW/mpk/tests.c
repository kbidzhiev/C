#include"tests.h"
#include<stdlib.h>
#include<assert.h>

struct Poly {
  unsigned len;
  int *p;
};

void free_Poly(struct Poly *pol);

struct Poly
high_coeff(const struct Poly A);

struct Poly
low_coeff(const struct Poly A);

void test_split_quadric() {
  // x2 + 2x + 1 == (x + 0)*x + (2x + 1)
  int pA[3] = {1, 2 , 1};
  unsigned len = 3;
  struct Poly A = {len, pA};
  struct Poly A1, A2;

  A1 = high_coeff(A);
  A2 = low_coeff(A);

  assert(A1.p[0] == 0 && A1.p[1] == 1); // 1x + 0
  assert(A2.p[0] == 1 && A2.p[1] == 2); // 2x + 1

  free_Poly(&A1);
  free_Poly(&A2);
}

void test_split_qubic() {
  // x3 + 3x2 + 4x + 7 == (x + 3)*x2 + (4x + 7)
  int pA[4] = {7, 4 , 3, 1};
  unsigned len = 4;
  struct Poly A = {len, pA};
  struct Poly A1, A2;

  A1 = high_coeff(A);
  A2 = low_coeff(A);


  assert(A1.p[0] == 3 && A1.p[1] == 1); // 1x + 3
  assert(A2.p[0] == 7 && A2.p[1] == 4); // 4x + 7

  free_Poly(&A1);
  free_Poly(&A2);
}



void test_karatsuba() {
  test_split_quadric();
  test_split_qubic();
}



