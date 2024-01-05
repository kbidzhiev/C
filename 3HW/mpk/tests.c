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
  printf("1) test_split_quadric\n");
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

  printf("2) test_split_qubic\n");
}

struct Poly
Poly_sum(const struct Poly A, const struct Poly B);

void test_sum(){
  unsigned len = 5;
  int pA[5] = {2, 4, 6, 8, 10};
  int pB[5] = {1, 3, 5, 9, 11};
  int pres[5] = {0, 0, 0, 0, 0};
  struct Poly A = {len, pA};
  struct Poly B = {len, pB};
  struct Poly res = {len, pres};

  res = Poly_sum(A,B);

  assert(3 == res.p[0]);
  assert(7 == res.p[1]);
  assert(11 == res.p[2]);
  assert(17 == res.p[3]);
  assert(21 == res.p[4]);

  printf("3) test_sum\n");
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

  printf("4) test_coeff\n");
}

struct Poly
Poly_mult_quadric(struct Poly lhs, struct Poly rhs);
void test_mult_quadric() {
  struct Poly A, B, C;
  int pA[2] = {3, 1};
  int pB[2] = {7, 4};
  A.len = 2;
  A.p = pA;
  B.len = 2;
  B.p = pB;

  C = Poly_mult_quadric(A, B);
  assert(21 == C.p[0]);
  assert(19 == C.p[1]);
  assert(4  == C.p[2]);
  printf("5) test_mult_quadric\n");
}


struct Poly
Poly_mult_karatsuba(const struct Poly A, const struct Poly B);
void test_mult_karatsuba() {
  unsigned i;
  struct Poly A, B, res1, res2;
  int pA[4] = {1, 2, 1, 1};
  int pB[4] = {2, 7, 3, 1};
  A.len = 4;
  A.p = pA;
  B.len = 4;
  B.p = pB;

  res1 = Poly_mult_karatsuba(A, B);
  res2 = Poly_mult_quadric(A, B);
  printf("Kar\tquadr:\n");
  for(i = 0; i < res2.len; ++i) {
    printf("%d\t%d\n", res1.p[i], res2.p[i]);
    //assert(res1.p[i] == res2.p[i]);
  }
  printf("6) test Poly_mult_karatsuba\n");
}

void test_karatsuba() {
  test_split_quadric();
  test_split_qubic();
  test_sum();
  test_copy_coeff();
  test_mult_quadric();
  test_mult_karatsuba();

  printf("All tests are DONE\n");
}



