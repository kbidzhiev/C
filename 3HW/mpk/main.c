#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define test 1
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
    printf("allocate_Poly: mem not allocated\n");
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
  unsigned degA = A.len - 1;
  unsigned degA1 = degA/2;
  struct Poly A1 = {degA1 + 1, A.p + degA1 + 1};
  return A1;
}

struct Poly
low_coeff(const struct Poly A) {
  unsigned degA = A.len - 1;
  unsigned degA2 = degA/2;
  struct Poly A2 = {degA2 + 1, A.p};
  return A2;
}

struct Poly
Poly_sum(const struct Poly A, const struct Poly B) {
  unsigned i;
  struct Poly res;
  if (A.len != B. len) {
    printf("Poly_sum: A.len != B.len\n");
    abort();
  }
  res.len = A.len;
  res.p = malloc(res.len * sizeof(int));
  if (NULL == res.p) {
    printf("Poly_sum: mem not allocated\n");
    abort();
  }
  for(i = 0; i < res.len; ++i) {
    res.p[i] = A.p[i] + B.p[i];
  }
  return res;
}

struct Poly
Poly_mult_karatsuba(struct Poly A, struct Poly B);


struct Poly
add_high_low(const struct Poly A1, const struct Poly A2) {
  struct Poly addA1A2;
  addA1A2 = Poly_sum(A1, A2);
  return addA1A2;
}

void subtract(struct Poly tmp, const struct Poly A1B1, const struct Poly A2B2) {
  for(unsigned i = 0; i < tmp.len; ++i) {
    tmp.p[i] = tmp.p[i] - A1B1.p[i] - A2B2.p[i];
  }
}

struct Poly
second_term(const struct Poly A1, const struct Poly A2,
            const struct Poly B1, const struct Poly B2,
            const struct Poly A1B1, const struct Poly A2B2) {
  struct Poly addA1A2, addB1B2, res;
  addA1A2 = add_high_low(A1, A2);
  addB1B2 = add_high_low(B1, B2);

  res = Poly_mult_karatsuba(addA1A2, addB1B2);
  subtract(res, A1B1, A2B2);

  free_Poly(&addA1A2);
  free_Poly(&addB1B2);
  return res;
}

void copy_coeff(struct Poly a, struct Poly A, unsigned begin, unsigned end) {
  if (A.len < end) {
    printf("copy_coeff: A.len < end\n (%d < %d)", A.len, end);
    abort();
  }
  for(unsigned i = begin; i < end; ++i) {
    A.p[i] += a.p[i-begin];
  }
}

struct Poly
Poly_mult_karatsuba(const struct Poly A, const struct Poly B) {
  struct Poly res, A1, A2, B1, B2, A1B1, term2, A2B2;

  if (A.len == 2) {
    res = allocate_Poly(3);
    res.p[0] = A.p[0] * B.p[0];
    res.p[1] = A.p[0] * B.p[1] + A.p[1] * B.p[0];
    res.p[2] = A.p[1] * B.p[1];
    //res = Poly_mult_quadric(A, B);
    return res;
  }

  res.len = A.len + B.len - 1;
  res = allocate_Poly(res.len);


  A1 = high_coeff(A);
  B1 = high_coeff(B);
  A2 = low_coeff(A);
  B2 = low_coeff(B);
  //A1B1 = first_term(A, B);
  //A2B2 = third_term(A, B);

  A1B1 = Poly_mult_karatsuba(A1, B1);
  A2B2 = Poly_mult_karatsuba(A2, B2);
  term2 = second_term(A1, A2, B1, B2, A1B1, A2B2);

  copy_coeff(A2B2, res, 0, A2B2.len);
  copy_coeff(term2, res, A.len/2, A.len/2 + term2.len);
  copy_coeff(A1B1, res, A.len, res.len) ;

  //free_Poly(&A1);
  //free_Poly(&B1);
  //free_Poly(&A2);
  //free_Poly(&B2);
  free_Poly(&A1B1);
  free_Poly(&term2);
  free_Poly(&A2B2);

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

int main() {
  unsigned i;
  struct Poly A, B, C;
#if test
  test_karatsuba();
#endif
  if((2 != scanf("%d%d", &A.len, &B.len)) || (A.len != B.len) ) {
    abort();
  }

  A = allocate_Poly(A.len);
  B = allocate_Poly(B.len);

  for(i = 0; i < A.len; ++i) {
    scanf("%d", &(A.p[i]));
  }
  for(i = 0; i < B.len; ++i) {
    scanf("%d", &(B.p[i]));
  }
  C = Poly_mult_karatsuba(A, B);

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
