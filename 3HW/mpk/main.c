#include <stdio.h>
#include <stdlib.h>
#include "tests.h"

struct Poly {
  unsigned len;
  int *p;
};

struct Poly Pcalloc(unsigned len);
void Pfree(struct Poly *pol);

void Pscanf(struct Poly *pol);
void Pprintf(const struct Poly pol);

struct Poly *Pmult_classic(const struct Poly *lhs, const struct Poly *rhs, struct Poly *res);

struct Poly termA1(const struct Poly *A);
struct Poly termA2(const struct Poly *A);

struct Poly Psum(const struct Poly *lhs, const struct Poly *rhs);
struct Poly *merge_terms(const struct Poly *A, const struct Poly *B, const struct Poly *C, struct Poly *res);


struct Poly *karatsuba_terms(struct Poly *A, const struct Poly *B, const struct Poly *C) {
  unsigned i;
  assert((A -> len) == (B -> len));
  assert((B -> len) == (C -> len));

  for(i = 0; i < (A -> len); ++i) {
    A -> p[i] = (A -> p[i]) - (B -> p[i]) - (C -> p[i]);
  }

  return A;
}
struct Poly Pmult(const struct Poly *lhs, const struct Poly *rhs) {
  struct Poly A1B1_mult, A2B2_mult;
  struct Poly A1A2_sum, B1B2_sum;
  struct Poly karat;

  struct Poly A1 = termA1(lhs);
  struct Poly A2 = termA2(lhs);
  struct Poly B1 = termA1(rhs);
  struct Poly B2 = termA2(rhs);
  struct Poly res = Pcalloc((lhs -> len) + (rhs -> len) - 1);

  if (lhs -> len == 2) {
    Pmult_classic(lhs, rhs, &res);
    return res;
  }


  A1B1_mult = Pmult(&A1, &B1);
  A2B2_mult = Pmult(&A2, &B2);

  A1A2_sum = Psum(&A1, &A2);
  B1B2_sum = Psum(&B1, &B2);
  karat = Pmult(&A1A2_sum, &B1B2_sum);
  karatsuba_terms(&karat, &A1B1_mult, &A2B2_mult);

  Pfree(&A1A2_sum);
  Pfree(&B1B2_sum);

  merge_terms(&A1B1_mult, &karat, &A2B2_mult, &res);

  Pfree(&A1B1_mult);
  Pfree(&A2B2_mult);
  Pfree(&karat);

  return res;
}


int main(void){
  unsigned sizeA, sizeB;
  struct Poly A, B;
  struct Poly C;
  test_all();

  if (2 != scanf("%d%d", &sizeA, &sizeB)) {
    printf("scanf of sizeA and sizeB failed\n");
    abort();
  }
  A = Pcalloc(sizeA);
  B = Pcalloc(sizeB);

  Pscanf(&A);
  Pscanf(&B);

  //C = Pmult(A, B);

  Pprintf(A);
  Pprintf(B);

  Pfree(&C);
  Pfree(&A);
  Pfree(&B);

  return 0;
}


struct Poly Pcalloc(unsigned len) {
  struct Poly pol = {len, NULL};
  pol.p = calloc(len, sizeof(int));
  if (NULL == pol.p) {
    printf("Palloc malloc of %u failed\n", len);
    abort();
  }
  return pol;
}

void Pfree(struct Poly *pol) {
  free(pol -> p);
  pol -> len = 0;
  pol -> p = NULL;
}

void Pscanf(struct Poly *pol) {
  for(unsigned i = 0; i < pol -> len; ++i) {
    scanf("%d", pol -> p + i);
  }
}

void Pprintf(const struct Poly pol) {
  for(unsigned i = 0; i < pol.len; ++i) {
    printf("%d ", pol.p[i]);
  }
  printf("\n");
}

struct Poly *Pmult_classic(const struct Poly *lhs, const struct Poly *rhs, struct Poly *res) {
  unsigned i, j, k;

  assert((lhs -> len) == (rhs -> len));
  assert((lhs -> len) + (rhs -> len) - 1 == (res -> len));
  for(j = 0; j < rhs -> len; ++j) {
    k = j;
    for(i = 0; i < lhs -> len; ++i) {
      res -> p[k] += (rhs -> p[j]) * (lhs -> p[i]);
      ++k;
    }
  }
  return res;
}

unsigned ln2(unsigned len) {
  unsigned res = 0;
  for(unsigned i = 0; i < 32; ++i) {
    if((len >> i) && 1u) {
      res = i;
    }
  }
  return res;
}

struct Poly termA1(const struct Poly *A) {
  struct Poly A1 = {A -> len/2, A ->p};
  return A1;
}

struct Poly termA2(const struct Poly *A) {
  struct Poly A2 = {A -> len/2, (A -> p) + (A -> len/2)};
  return A2;
}

struct Poly Psum(const struct Poly *lhs, const struct Poly *rhs) {
  unsigned i;
  struct Poly sum = Pcalloc(lhs -> len);
  assert(lhs -> len == rhs -> len);
  for(i = 0; i < (lhs -> len); ++i) {
    sum.p[i] = (lhs -> p[i]) + (rhs ->p[i]);
  }
  return sum;
}

struct Poly *merge_terms(const struct Poly *A, const struct Poly *B, const struct Poly *C, struct Poly *res) {
  unsigned i;
  unsigned beginB = (B -> len + 1)/2;
  unsigned beginC = (C -> len + 1);
  assert((A -> len) == (B -> len));
  assert((B -> len) == (C -> len));
  assert((res -> len) == (2 * (A -> len) + 1));

  for(i = 0; i < A -> len; ++i) {
    res -> p[i] = A -> p[i];
    res -> p[i + beginC] = C -> p[i];
  }
  for(i = 0; i < B -> len; ++i) {
    res -> p[i + beginB] += B -> p[i];
  }
  return res;
}
