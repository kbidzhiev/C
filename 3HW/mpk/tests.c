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

  printf("2) test_split_qubic\n");
}

struct Poly
Poly_sum(const struct Poly A, const struct Poly B);

void test_sum(){
  unsigned len = 5;
  int pA[5] = {2, 4, 6, 8, 10};
  int pB[5] = {1, 3, 5, 9, 11};
  struct Poly A = {len, pA};
  struct Poly B = {len, pB};
  struct Poly res = {len, NULL};

  res = Poly_sum(A,B);

  assert(3 == res.p[0]);
  assert(7 == res.p[1]);
  assert(11 == res.p[2]);
  assert(17 == res.p[3]);
  assert(21 == res.p[4]);

  free_Poly(&res);
  printf("3) test_sum\n");
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

  free_Poly(&C);
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
    assert(res1.p[i] == res2.p[i]);
  }
  free_Poly(&res1);
  free_Poly(&res2);

  printf("6) test Poly_mult_karatsuba\n");
}

void test_karatsuba() {
  test_split_qubic();
  test_sum();
  test_mult_quadric();
  test_mult_karatsuba();

  printf("All tests are DONE\n");
}



