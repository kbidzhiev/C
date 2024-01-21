#include "tests.h"
#include <stdio.h>


struct Poly {
  unsigned len;
  int *p;
};

struct Poly Pmalloc(unsigned len);
void Pfree(struct Poly *p);

struct Poly Pmult_classic(const struct Poly lhs, const struct Poly rhs, struct Poly res);

void Passert(const struct Poly lhs, const struct Poly rhs) {
  unsigned i;
  int l, r;
  if (lhs.len != rhs.len) {
    printf("Passert length: %u != %u\n", lhs.len, rhs.len);
    abort();
  }
  for(i = 0; i < lhs.len; ++i) {
    l = lhs.p[i];
    r = rhs.p[i];
    if(l != r) {
      printf("Passert %u-th elem: %d != %d\n", i, l, r);
      abort();
    }
  }

}

void test_Pmult2(int i) {
  int a[4] = {4, 3, 2, 1};
  int b[4] = {8, 7, 6, 5};
  struct Poly A, B, C;
  A.len = B.len = 4;
  A.p = a;
  B.p = b;
  C = Pmalloc(4 + 4 - 1);

  C = Pmult_classic(A, B, C);
  assert(32 == C.p[0] && 52 == C.p[1]);
  assert(61 == C.p[2] && 60 == C.p[3]);
  assert(34 == C.p[4] && 16 == C.p[5]);
  assert(5 == C.p[6]);

  Pfree(&C);
  printf("%i. Test Pmult2\n", i);
}

struct Poly termA2(const struct Poly *A);
struct Poly termA1(const struct Poly *A);
void test_termA1_termA2(int i) {
  struct Poly A11, A22;
  struct Poly A1 = {4, NULL}, A2 = {4, NULL};
  struct Poly A = {8, NULL};
  int a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  int a1[4] = {1, 2, 3, 4};
  int a2[4] = {5, 6, 7, 8};

  A1.p = a1;
  A2.p = a2;
  A.p = a;

  A11 = termA1(&A);
  A22 = termA2(&A);
  Passert(A11, A1);
  Passert(A22, A2);

  printf("%d. Test termA1_termA2\n", i);
}


struct Poly termA1B1_prod(const struct Poly *C);
struct Poly termA2B2_prod(const struct Poly *C);
void test_termA1B1_termA2B2(int i) {
  struct Poly A1B1, A2B2;
  struct Poly a1b1, a2b2;
  struct Poly C = {7, NULL};
  int c[7] = {1, 2, 3, 4, 5, 6, 7};
  int c1[3] = {1, 2, 3};
  int c2[3] = {5, 6, 7};
  C.p = c;
  a1b1.p = c1;
  a2b2.p = c2;
  a1b1.len = a2b2.len = 3;
  A1B1 = termA1B1_prod(&C);
  A2B2 = termA2B2_prod(&C);

  Passert(a1b1, A1B1);
  Passert(a2b2, A2B2);

  printf("%d. Test termA1B1_termA2B2\n", i);
}


struct Poly termA1A2_sum(const struct Poly A1, const struct Poly A2, struct Poly *tmp);
struct Poly termB1B2_sum(const struct Poly B1, const struct Poly B2, struct Poly *tmp);

void test_termA1A2(int i) {
  struct Poly A, tmp, A1, A2;
  struct Poly A1A2_sum, res;
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int r1[] = {6, 8, 10, 12};
  unsigned len = 8;
  tmp = Pmalloc(len/2);

  res.len = len/2;
  res.p = r1;

  A.len = len;
  A.p = a;
  A1 = termA1(&A);
  A2 = termA2(&A);
  A1A2_sum = termA1A2_sum(A1, A2, &tmp);
  Passert(A1A2_sum, res);

  Pfree(&tmp);
  printf("%d. Test termA1A2_add\n", i);
}

unsigned ln2(unsigned len);
void test_ln2(unsigned i) {

  assert(ln2(1) == 0);
  assert(ln2(2) == 1);
  assert(ln2(4) == 2);
  assert(ln2(8) == 3);
  assert(ln2(16) == 4);
  assert(ln2(17) == 4);

  printf("%d. Test ln2\n", i);
}

struct Poly Pmult(const struct Poly A, const struct Poly B);
void Pprintf(const struct Poly pol);
void test_Pmult(int i) {
  int a[4] = {4, 3, 2, 1};
  int b[4] = {8, 7, 6, 5};
  struct Poly A, B, C, Ckar;
  A.len = B.len = 4;
  A.p = a;
  B.p = b;
  C = Pmalloc(4 + 4 - 1);

  C = Pmult_classic(A, B, C);
  Ckar = Pmult(A, B);
  assert(32 == C.p[0] && 52 == C.p[1]);
  assert(61 == C.p[2] && 60 == C.p[3]);
  assert(34 == C.p[4] && 16 == C.p[5]);
  assert(5 == C.p[6]);

  Pprintf(C);
  Pprintf(Ckar);
  assert(32 == Ckar.p[0] && 52 == Ckar.p[1]);
  assert(61 == Ckar.p[2] && 60 == Ckar.p[3]);
  assert(34 == Ckar.p[4] && 16 == Ckar.p[5]);
  assert(5 == Ckar.p[6]);

  Pfree(&C);
  Pfree(&Ckar);
  printf("%i. Test Pmult_karats\n", i);
}

void test_all(void) {
  test_Pmult2(1);
  test_termA1_termA2(2);
  test_termA1B1_termA2B2(3);
  test_termA1A2(4);
  test_ln2(5);
  test_Pmult(6);
  printf("All tests are ok\n");
}
