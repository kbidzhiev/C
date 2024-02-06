#include <stdio.h>
#include <stdlib.h>
#include "tests.h"

#define DEBUG 1


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


struct Poly *merge_terms_old(const struct Poly *kar, struct Poly *res);
struct Poly *merge_terms(const struct Poly *A, const struct Poly *B, const struct Poly *C, struct Poly *res);

struct Poly *karatsuba_terms(struct Poly *A, const struct Poly *B, const struct Poly *C);


struct Poly A1B1_in_res(const struct Poly *res);
struct Poly A2B2_in_res(const struct Poly *res);


struct Poly Pmult(const struct Poly *lhs, const struct Poly *rhs);
struct Poly *Pmult_impl(const struct Poly *lhs, const struct Poly *rhs, struct Poly *res);

struct Poly Pmult(const struct Poly *lhs, const struct Poly *rhs) { 
  struct Poly res = Pcalloc((lhs -> len) + (rhs -> len) - 1);
  Pmult_impl(lhs, rhs, &res); 


  return res;
}

struct Poly *Pmult_impl(const struct Poly *lhs, const struct Poly *rhs, struct Poly *res) {
  struct Poly A1A2_sum, B1B2_sum;
  struct Poly A1B1_mult, A2B2_mult;
  struct Poly karat;
  struct Poly A1A2_plus_B1B2;

  struct Poly A1 = termA1(lhs);
  struct Poly A2 = termA2(lhs);
  struct Poly B1 = termA1(rhs);
  struct Poly B2 = termA2(rhs);

  if (lhs -> len <= (1u<<5)) {
    Pmult_classic(lhs, rhs, res);
    return res;
  }

  //A1B1_mult = Pmult(&A1, &B1);
  //A2B2_mult = Pmult(&A2, &B2);
  A1B1_mult = A1B1_in_res(res);
  A2B2_mult = A2B2_in_res(res);
  Pmult_impl(&A1, &B1, &A1B1_mult);
  Pmult_impl(&A2, &B2, &A2B2_mult);

  A1A2_plus_B1B2 = Pcalloc(A1.len + B1.len);
  A1A2_sum.len = A1.len;
  A1A2_sum.p = A1A2_plus_B1B2.p;

  B1B2_sum.len = B1.len;
  B1B2_sum.p = A1A2_plus_B1B2.p + A1.len;

  A1A2_B1B2sum(&A1, &A2, &B1, &B2, &A1A2_sum, &B1B2_sum);


  karat = Pmult(&A1A2_sum, &B1B2_sum);
  karatsuba_terms(&karat, &A1B1_mult, &A2B2_mult);

  Pfree(&A1A2_plus_B1B2);

  //merge_terms(&A1B1_mult, &karat, &A2B2_mult, res);
  merge_terms_old(&karat, res);

  //Pfree(&A1B1_mult);
  //Pfree(&A2B2_mult);
  Pfree(&karat);

  return res;
}

void mpk(void) {
  unsigned sizeA, sizeB;
  struct Poly A, B;
  struct Poly C;

  if (2 != scanf("%u%u", &sizeA, &sizeB)) {
    printf("scanf of sizeA and sizeB failed\n");
    abort();
  }
  A = Pcalloc(sizeA);
  B = Pcalloc(sizeB);

  Pscanf(&A);
  Pscanf(&B);

  C = Pmult(&A, &B);

  Pprintf(A);
  Pprintf(B);

  Pfree(&C);
  Pfree(&A);
  Pfree(&B);

}

int main(void){
  test_all();
  //mpk();
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
#if DEBUG
  assert((lhs -> len) == (rhs -> len));
  assert((lhs -> len) + (rhs -> len) - 1 == (res -> len));
#endif
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
#if DEBUG
  assert(lhs -> len == rhs -> len);
#endif
  for(i = 0; i < (lhs -> len); ++i)
    sum.p[i] = (lhs -> p[i]) + (rhs ->p[i]);
  return sum;
}

struct Poly *karatsuba_terms(struct Poly *A, const struct Poly *B, const struct Poly *C) {
  unsigned i;
#if DEBUG
  assert((A -> len) == (B -> len));
  assert((B -> len) == (C -> len));
#endif
  for(i = 0; i < (A -> len); ++i)
    A -> p[i] -= (B -> p[i]) + (C -> p[i]);
  return A;
}

struct Poly *merge_terms_old(const struct Poly *kar, struct Poly *res) {
  unsigned i;
  unsigned begin = (kar -> len + 1)/2;
#if DEBUG
  assert((res -> len) == (2 * (kar -> len) + 1));
#endif
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

struct Poly *merge_terms(const struct Poly *A, const struct Poly *B, const struct Poly *C, struct Poly *res) {
  unsigned i;
  unsigned beginB = (B -> len + 1)/2;
  unsigned beginC = (C -> len + 1);
#if DEBUG
  assert((A -> len) == (B -> len));
  assert((B -> len) == (C -> len));
  assert((res -> len) == (2 * (A -> len) + 1));
#endif
  for(i = 0; i < A -> len; ++i) {
    res -> p[i] += A -> p[i];
    res -> p[i + beginB] += B -> p[i];
    res -> p[i + beginC] += C -> p[i];
  }
  //for(i = 0; i < B -> len; ++i) {
  //  res -> p[i + beginB] += B -> p[i];
  //}
  return res;
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
#if DEBUG
  assert(A1 -> len == A2 -> len);
  assert(A2 -> len == B1 -> len);
  assert(B1 -> len == B2 -> len);
  assert(B2 -> len == A1A2_sum -> len);
  assert(A1A2_sum -> len == B1B2_sum -> len);
#endif
  for(i = 0; i < A1 -> len; ++i) {
    A1A2_sum -> p[i] = A1 -> p[i] + A2 -> p[i];
    B1B2_sum -> p[i] = B1 -> p[i] + B2 -> p[i];
  }
}
