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
void fill_coeff(const struct Poly A, const struct Poly B, struct Poly *res, struct Poly *tmp);

struct Poly A1B1_in_res(const struct Poly *res, unsigned len){
  struct Poly A1B1 = {len, res -> p};
  return A1B1;
}
struct Poly A2B2_in_res(const struct Poly *res, unsigned len){
  struct Poly A2B2 = {len, res -> p + (res -> len - len)};
  return A2B2;
}

void fillA1B1(const struct Poly A1, const struct Poly B1, struct Poly *A1B1);
void fillA2B2(const struct Poly A2, const struct Poly B2, struct Poly *A2B2);

void fill_coeff(const struct Poly A, const struct Poly B, struct Poly *res, struct Poly *tmp) {
  struct Poly A1, A2, B1, B2;
  struct Poly A1B1, A2B2;
  struct Poly addA1A2, addB1B2;
  A1 = high_coeff(A);
  B1 = high_coeff(B);
  A2 = low_coeff(A);
  B2 = low_coeff(B);

  A1B1 = A1B1_in_res(res, A1.len + B1.len - 1);//A1B1 lives in res
  A2B2 = A2B2_in_res(res, A2.len + B2.len - 1);//A2B2 lives in res
  //fill_coeff(A1, B1, &A1B1); //A1B1 will be filled to res without malloc
  //fill_coeff(A2, B2, &A2B2); //A2B2 will be filled to res without malloc
  
  addA1A2.len = A1.len;
  addA1A2.p = tmp -> p;

  addB1B2.len = B1.len;
  addB1B2.p = tmp -> p + addA1A2.len;


}
struct Poly
Poly_mult(const struct Poly A, const struct Poly B) {
  struct Poly res = {A.len + B.len - 1, NULL};
  struct Poly tmp = {A.len + B.len - 1, NULL};
  res = allocate_Poly(res.len);
  // tmp stores (A1+A2) * (B1+B2)
  // How much additional memory it takes ?
  // storing first term  A1+A2: len(A1+A2) == len(A1)
  // storing second term B1+B2: len(B1+B2) == len(B1)
  // storing product     (A1+A2) * (B1+B2) == len(A1) + len(B1) - 1
  // Take into account that len(A1) == len(B1) == len(A2) == len(B2) because len(A) == pow(2,k)
  // therefore all together :
  // len(A1) + len(B1) + len(A1) + len(B1) - 1 == len(A) + len(B) - 1 == len(res)
  tmp = allocate_Poly(tmp.len);

  fill_coeff(A, B, &res, &tmp);

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
