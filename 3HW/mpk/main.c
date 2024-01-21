#include <stdio.h>
#include <stdlib.h>
#include "tests.h"

struct Poly {
  unsigned len;
  int *p;
};

struct Poly Pmalloc(unsigned len);
void Pfree(struct Poly *pol);

void Pscanf(struct Poly *pol);
void Pprintf(const struct Poly pol);

struct Poly Pmult_classic(const struct Poly lhs, const struct Poly rhs, struct Poly res);

struct Poly termA1(const struct Poly *A);
struct Poly termA2(const struct Poly *A);

struct Poly termA1B1_prod(const struct Poly *C);
struct Poly termA2B2_prod(const struct Poly *C);

struct Poly termA1A2_sum(const struct Poly A1, const struct Poly A2, struct Poly *tmp);
struct Poly termB1B2_sum(const struct Poly B1, const struct Poly B2, struct Poly *tmp);


#if 1
void Pmul_impl(const struct Poly *A,
              const struct Poly *B,
                    struct Poly *C,
                    struct Poly *tmp) {
/* 
 *
 *
 */
  unsigned i;
  struct Poly A1B1_prod; //A1B1 stored in the begining of C
  //struct Poly term2_karatsuba; //Karatsuba term stored in the middle of C
  struct Poly A2B2_prod; //A2B2 stored in the end of C
  struct Poly A1, A2, B1, B2;
  struct Poly A1A2_sum, B1B2_sum;
  struct Poly tmp2; //contains a pointer to the third part of tmp

  assert(A -> len == B -> len);
  if (2 == (A -> len)) {
    Pmult_classic(*A, *B, *C);
    return;
  }

  A1 = termA1(A);
  A2 = termA2(A);
  B1 = termA1(B);
  B2 = termA2(B);

  A1B1_prod = termA1B1_prod(C); //A1B1 is empty //write test
  A2B2_prod = termA2B2_prod(C); //A2B2 is empty //write test
  A1A2_sum = termA1A2_sum(A1, A2, tmp); //A1 + A2 is written in tmp;
  B1B2_sum = termB1B2_sum(B1, B2, tmp); //B1 + B2 is written in tmp;

  tmp2.len = A1A2_sum.len + B1B2_sum.len - 1;
  tmp2.p = tmp -> p + (A1A2_sum.len + B1B2_sum.len);

  Pmul_impl(&A1, &B1, &A1B1_prod, &tmp2); //filling A1B1
  Pmul_impl(&A2, &B2, &A2B2_prod, &tmp2); //filling A2B2


  Pmul_impl(&A1A2_sum, &B1B2_sum, &tmp2, &tmp2); //filling Karatsuba term into tmp

  for(i = 0; i < A -> len; ++i) {
    (C -> p)[i + (A -> len)/2] += (tmp2.p)[i];
  }

  return ;
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

struct Poly Pmult(const struct Poly A, const struct Poly B) {
  unsigned lentmp = (4 * A.len - ln2(A.len) - 7);
  struct Poly C, tmp;
  C = Pmalloc(A.len + B.len - 1); //len(A) == len(B) == pow(2,k)
  tmp = Pmalloc(lentmp);

  Pmul_impl(&A, &B, &C, &tmp);

  Pfree(&tmp);

  return C;
}
#endif

int main(void){
  unsigned sizeA, sizeB;
  struct Poly A, B;
  struct Poly C;
  test_all();

  if (2 != scanf("%d%d", &sizeA, &sizeB)) {
    printf("scanf of sizeA and sizeB failed\n");
    abort();
  }
  A = Pmalloc(sizeA);
  B = Pmalloc(sizeB);

  Pscanf(&A);
  Pscanf(&B);

  C = Pmult(A, B);

  Pprintf(A);
  Pprintf(B);

  Pfree(&C);
  Pfree(&A);
  Pfree(&B);

  return 0;
}


struct Poly Pmalloc(unsigned len) {
  struct Poly pol = {len, NULL};
  pol.p = malloc(len * sizeof(int));
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
  /* #I think "if" doesn't make sense here
  if ((pol -> p != NULL) || (pol -> len != 0)) {
    printf("Pfree failed\n");
    abort();
  }
  */
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

struct Poly Pmult_classic(const struct Poly lhs, const struct Poly rhs, struct Poly res) {
  unsigned i, j, k;
  assert(lhs.len + rhs.len - 1 == res.len);
  for(j = 0; j < rhs.len; ++j) {
    k = j;
    for(i = 0; i < lhs.len; ++i) {
      res.p[k] += rhs.p[j] * lhs.p[i];
      ++k;
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

struct Poly termA1B1_prod(const struct Poly *C) {
  /* Mathematical explanaition:
   * lenA + len B - 1 == lenC  // assert(lenA == lenB)
   * lenA1 + lenA2 == lenA //assert(lenA1 == lenA2 == lenB1 == lenB2)
   * => lenA == (lenC + 1)/2
   * => lenA1 == lenA/2
   * => lenA1B1 == lenA1 + lenB1 - 1 == lenA - 1 == (lenC - 1)/2
   */
  unsigned lenA1B1 = ((C -> len) - 1)/2;
  struct Poly A1B1 = {lenA1B1, C -> p};
  return A1B1;
}

struct Poly termA2B2_prod(const struct Poly *C) {
  /* Mathematical explanaition:
  * lenA + len B - 1 == lenC  // assert(lenA == lenB)
  * lenA1 + lenA2 == lenA //assert(lenA1 == lenA2 == lenB1 == lenB2)
  * => lenA == (lenC + 1)/2
  * => lenA2 == lenA/2
  * => lenA1B1 == lenA1 + lenB1 - 1 == lenA - 1 == (lenC - 1)/2
  */
  unsigned lenA2B2 = (C -> len - 1)/2;
  struct Poly A2B2 = {lenA2B2, (C -> p) + ((C -> len) - lenA2B2)};
  return A2B2;
}

struct Poly termA1A2_sum(const struct Poly A1, const struct Poly A2, struct Poly *tmp) {
  unsigned i;
  struct Poly A1A2 = {A1.len, tmp -> p};
  for(i = 0; i < A1A2.len; ++i) {
    A1A2.p[i] = A1.p[i] + A2.p[i];
  }
  return A1A2;
}

struct Poly termB1B2_sum(const struct Poly B1, const struct Poly B2, struct Poly *tmp) {
  unsigned i;
  struct Poly B1B2 = {B1.len, (tmp -> p) + B1.len};
  for(i = 0; i < B1B2.len; ++i) {
    B1B2.p[i] = B1.p[i] + B2.p[i];
  }
  return B1B2;
}
