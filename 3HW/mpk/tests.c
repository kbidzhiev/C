#include "tests.h"
#include <stdio.h>


struct Poly {
  unsigned len;
  int *p;
};

struct Poly Pcalloc(unsigned len);
void Pfree(struct Poly *p);

struct Poly *Pmult_classic(const struct Poly *lhs, const struct Poly *rhs, struct Poly *res);

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

void test_Pmult_classic(int i) {
  int a[4] = {4, 3, 2, 1};
  int b[4] = {8, 7, 6, 5};
  struct Poly A, B, C;
  A.len = B.len = 4;
  A.p = a;
  B.p = b;
  C = Pcalloc(4 + 4 - 1);

  Pmult_classic(&A, &B, &C);
  assert(32 == C.p[0] && 52 == C.p[1]);
  assert(61 == C.p[2] && 60 == C.p[3]);
  assert(34 == C.p[4] && 16 == C.p[5]);
  assert(5 == C.p[6]);

  Pfree(&C);
  printf("%i. Test Pmult2\n", i);
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


struct Poly Pmult(const struct Poly *A, const struct Poly *B);
void Pprintf(const struct Poly pol);
void test_Pmult(int i) {
  int a[4] = {4, 3, 2, 1};
  int b[4] = {8, 7, 6, 5};
  struct Poly A, B, C, Ckar;
  A.len = B.len = 4;
  A.p = a;
  B.p = b;
  C = Pcalloc(4 + 4 - 1);

  Pmult_classic(&A, &B, &C);
  Ckar = Pmult(&A, &B);
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
  test_Pmult_classic(1);
  test_ln2(2);
  test_Pmult(3);
  printf("All tests are ok\n");
}
