

#include "tests.h"
#include <stdio.h>


struct Poly {
  unsigned len;
  int *p;
};
struct Poly Pmalloc(unsigned len);
void Pfree(struct Poly *p);
struct Poly Pmult2(const struct Poly lhs, const struct Poly rhs, struct Poly res);

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

  C = Pmult2(A, B, C);
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


struct Poly termA1B1(const struct Poly *C);
struct Poly termA2B2(const struct Poly *C);
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
  A1B1 = termA1B1(&C);
  A2B2 = termA2B2(&C);

  Passert(a1b1, A1B1);
  Passert(a2b2, A2B2);

  printf("%d. Test termA1B1_termA2B2\n", i);
}

void test_all(void) {
  test_Pmult2(1);
  test_termA1_termA2(2);
  test_termA1B1_termA2B2(3);

  printf("All tests are ok\n");
}
