#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define test 0
#if test
#include"tests.h"
#endif

struct Poly {
  unsigned len;
  int *p;
};

struct Poly
allocate_Poly(unsigned len) {
  struct Poly res = {len, NULL};
  res.p = calloc(len, sizeof(int));
  if (NULL == res.p) {
    //printf("allocate_Poly: mem not allocated\n");
    abort();
  }
  return res;
}

void free_Poly(struct Poly *pol) {
  pol -> len = 0;
  free(pol -> p);
}

struct Poly
Poly_mult_quadric(struct Poly lhs, struct Poly rhs) {
  unsigned i, j, k;
  struct Poly res = {lhs.len + rhs.len - 1, NULL};
  res.p = calloc(res.len, sizeof(int));

  for(j = 0; j < rhs.len; ++j) {
    k = j;
    for(i = 0; i < lhs.len; ++i) {
      res.p[k] += rhs.p[j] * lhs.p[i];
      ++k;
    }
  }
  return res;
}

struct Poly
high_coeff(const struct Poly A) {
  unsigned degA1 = (A.len - 1)/2;
  struct Poly A1 = {degA1 + 1, A.p + degA1 + 1};
  return A1;
}

struct Poly
low_coeff(const struct Poly A) {
  unsigned degA2 = (A.len - 1)/2;
  struct Poly A2 = {degA2 + 1, A.p};
  return A2;
}

struct Poly
Poly_mult(struct Poly A, struct Poly B);
void fill_coeff(const struct Poly A, const struct Poly B, struct Poly *res);

void fillA1B1()

void fill_coeff(const struct Poly A, const struct Poly B, struct Poly *res) {
  struct Poly A1, A2, B1, B2;
  A1 = high_coeff(A);
  B1 = high_coeff(B);
  A2 = low_coeff(A);
  B2 = low_coeff(B);

  fillA1B1(A1, B1, res);

}
struct Poly
Poly_mult(const struct Poly A, const struct Poly B) {
  struct Poly res = {A.len + B.len - 1, NULL};
  res = allocate_Poly(res.len);

  fill_coeff(A, B, &res);



  return res;
}

void canonic_form(struct Poly *A) {
  int degA = (A -> len) - 1; //size is length of pol
  for (; degA >= 0; --degA) {
    if ((A ->p[degA]) != 0) {
      // pol[degA] is first nonzero elem,
      A -> len = degA + 1;
      break;
    }
  }
}

struct Poly
Poly_scanf(unsigned len) {
  unsigned i;
  struct Poly A = allocate_Poly(len);
  A = allocate_Poly(A.len);

  for(i = 0; i < A.len; ++i) {
    scanf("%d", A.p + i);
  }
  return A;
}

int main() {
  unsigned i;
  struct Poly A, B, C;
#if test
  test_karatsuba();
#endif
  if((2 != scanf("%d%d", &A.len, &B.len)) || (A.len != B.len) ) {
    abort();
  }

  A = Poly_scanf(A.len);
  B = Poly_scanf(B.len);

  C = Poly_mult(A, B);

  canonic_form(&C);

  for(i = 0; i < C.len; ++i) {
    printf("%d ", C.p[i]);
  }
  printf("\n");

  free_Poly(&A);
  free_Poly(&B);
  free_Poly(&C);
  return 0;
}
