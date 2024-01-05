#include"tests.h"
#include<stdlib.h>
#include<stdio.h>
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
  printf("test_split_quadric\n");
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

  printf("test_split_qubic\n");
}

void poly_sum(struct Poly const A, struct Poly const B, struct Poly *res);

void test_sum(){
  unsigned len = 5;
  int pA[5] = {2, 4, 6, 8, 10};
  int pB[5] = {1, 3, 5, 9, 11};
  int pres[5] = {0, 0, 0, 0, 0};
  struct Poly A = {len, pA};
  struct Poly B = {len, pB};
  struct Poly res = {len, pres};

  poly_sum(A,B, &res);

  assert(3 == res.p[0]);
  assert(7 == res.p[1]);
  assert(11 == res.p[2]);
  assert(17 == res.p[3]);
  assert(21 == res.p[4]);

  printf("test_sum\n");
}

void copy_coeff(struct Poly a, struct Poly A, unsigned begin, unsigned end);

void test_copy_coeff() {
  unsigned len = 7;
  int pA[7] = {0, 0, 0, 0, 0, 0 , 0};
  int pA1[4] = {7, 4, 3, 1};
  int pA2[3] = {1, 2, 1};
  struct Poly A = {len, pA};
  struct Poly A1 = {4, pA1};
  struct Poly A2 = {3, pA2};

  copy_coeff(A1, A, 0, A1.len);
  copy_coeff(A2, A, A1.len, A1.len + A2.len);

  assert(7 == A.p[0]);
  assert(4 == A.p[1]);
  assert(3 == A.p[2]);
  assert(1 == A.p[3]);
  assert(1 == A.p[4]);
  assert(2 == A.p[5]);
  assert(1 == A.p[6]);

  printf("test_coeff\n");
}

void test_karatsuba() {
  test_split_quadric();
  test_split_qubic();
  test_sum();
  test_copy_coeff();

  printf("All tests are DONE\n");
}



