

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
    printf("Passert length: %u != %u", lhs.len, rhs.len);
    abort();
  }
  for(i = 0; i < lhs.len; ++i) {
    l = lhs.p[i];
    r = rhs.p[i];
    if(l != r) {
      printf("Passert %u-th elem: %d != %d", i, l, r);
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
  struct Poly A1, A2;
  struct Poly A = {8, NULL};
  int a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  A.p = a;

  A1 = termA1(&A);
  A2 = termA2(&A);
  assert()

}
void test_all(void) {
  test_Pmult2(1);


  printf("All tests are ok\n");
}
