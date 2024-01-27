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
void A1A2_B1B2sum(const struct Poly *A1, const struct Poly *A2,
                         const struct Poly *B1, const struct Poly *B2,
                         struct Poly *A1A2_sum, struct Poly *B1B2_sum
                         );
struct Poly *merge_terms(const struct Poly *kar, struct Poly *res);


struct Poly *karatsuba_terms(struct Poly *A, const struct Poly *B, const struct Poly *C) {
  unsigned i;
  assert((A -> len) == (B -> len));
  assert((B -> len) == (C -> len));
  for(i = 0; i < (A -> len); ++i)
    A -> p[i] -= (B -> p[i]) + (C -> p[i]);
  return A;
}

struct Poly A1B1_in_res(const struct Poly *res);
struct Poly A2B2_in_res(const struct Poly *res);

struct Poly Pmult(const struct Poly *lhs, const struct Poly *rhs);
struct Poly *Pmult_impl(const struct Poly *lhs, const struct Poly *rhs, struct Poly *res) {
  struct Poly karat;

  struct Poly A1B1_mult = A1B1_in_res(res);
  struct Poly A2B2_mult = A2B2_in_res(res);
  struct Poly A1 = termA1(lhs);
  struct Poly A2 = termA2(lhs);
  struct Poly B1 = termA1(rhs);
  struct Poly B2 = termA2(rhs);
  struct Poly A1A2_sum = Pcalloc(A1.len);
  struct Poly B1B2_sum = Pcalloc(B1.len);
  
  if (lhs -> len == 2) {
    Pmult_classic(lhs, rhs, res);
    return res;
  }

  Pmult_impl(&A1, &B1, &A1B1_mult);
  Pmult_impl(&A2, &B2, &A2B2_mult);

  A1A2_B1B2sum(&A1, &A2, &B1, &B2, &A1A2_sum, &B1B2_sum);
  karat = Pmult(&A1A2_sum, &B1B2_sum);
  karatsuba_terms(&karat, &A1B1_mult, &A2B2_mult);

  Pfree(&A1A2_sum);
  Pfree(&B1B2_sum);

  merge_terms(&karat, res);

  Pfree(&A1A2_sum);
  Pfree(&B1B2_sum);
  Pfree(&karat);

  return res;
}
struct Poly Pmult(const struct Poly *lhs, const struct Poly *rhs) {
  struct Poly res = Pcalloc((lhs -> len) + (rhs -> len) - 1);
  if (lhs -> len == 2) {
    Pmult_classic(lhs, rhs, &res);
    return res;
  }

  Pmult_impl(lhs, rhs, &res);
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
  for(unsigned i = 0; i < pol -> len; ++i)
    scanf("%d", pol -> p + i);
}

void Pprintf(const struct Poly pol) {
  for(unsigned i = 0; i < pol.len; ++i)
    printf("%2d ", pol.p[i]);
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
  for(unsigned i = 0; i < 32; ++i)
    if((len >> i) && 1u)
      res = i;
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
  for(i = 0; i < (lhs -> len); ++i)
    sum.p[i] = (lhs -> p[i]) + (rhs ->p[i]);
  return sum;
}

struct Poly *merge_terms(const struct Poly *kar, struct Poly *res) {
  unsigned i;
  unsigned begin = (kar -> len + 1)/2;
  assert((res -> len) == (2 * (kar -> len) + 1));

  for(i = 0; i < kar -> len; ++i)
    res -> p[i + begin] += kar -> p[i];
  return res;
}

struct Poly A1B1_in_res(const struct Poly *res) {
  /* A1 and B1 are half size of A
   * len(A1*B1) = 2*len(A1) - 1 == len(A) - 1
   * len(res) = 2*len(A) - 1 = 2*lenA - 2 + 1 = 2(lenA - 1) + 1 = 2len(A1*B1) + 1;
   * => len(A1*B1) == (len(res) - 1)/2   */
  unsigned len = ((res -> len) - 1)/2;
  struct Poly A1B1 = {len, res -> p};
  return A1B1;
}
struct Poly A2B2_in_res(const struct Poly *res) {
  /* A1 and B1 are half size of A
   * len(A1*B1) = 2*len(A1) - 1 == len(A) - 1
   * len(res) = 2*len(A) - 1 = 2*lenA - 2 + 1 = 2(lenA - 1) + 1 = 2len(A1*B1) + 1;
   * => len(A1*B1) == (len(res) - 1)/2   */
  unsigned len = ((res -> len) - 1)/2;
  struct Poly A2B2 = {len, (res -> p) + len + 1};
  return A2B2;
}

void A1A2_B1B2sum(const struct Poly *A1, const struct Poly *A2,
                         const struct Poly *B1, const struct Poly *B2,
                         struct Poly *A1A2_sum, struct Poly *B1B2_sum
                         ) {
  unsigned i;
  assert(A1 -> len == A2 -> len);
  assert(A2 -> len == B1 -> len);
  assert(B1 -> len == B2 -> len);
  assert(B2 -> len == A1A2_sum -> len);
  assert(A1A2_sum -> len == B1B2_sum -> len);
  for(i = 0; i < A1 -> len; ++i) {
    A1A2_sum -> p[i] = A1 -> p[i] + A2 -> p[i];
    B1B2_sum -> p[i] = B1 -> p[i] + B2 -> p[i];
  }
}
