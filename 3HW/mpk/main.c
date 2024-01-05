#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"tests.h"

struct Poly {
  unsigned len;
  int *p;
};

void free_Poly(struct Poly *pol) {
  pol -> len = 0;
  free(pol -> p);
}

struct Poly
poly_mult_quadric(struct Poly lhs, struct Poly rhs) {
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

void ppol_mult_quadric(int *pol1, unsigned size1, int *pol2, unsigned size2, int *pol3, unsigned size3) {
  unsigned i, j, k;
  for(k = 0; k < size3; ++k)
    pol3[k] = 0;

  for(j = 0; j < size2; ++j) {
    k = j;
    for(i = 0; i < size1; ++i) {
      pol3[k] += pol2[j] * pol1[i];
      ++k;
    }
  }
}

struct Poly
high_coeff(const struct Poly A) {
  unsigned i;
  unsigned degA = A.len - 1;
  unsigned degA1 = degA/2;
  unsigned shiftA1 = degA % 2; // degA == 2*k ?
  struct Poly A1 = {degA1 + 1, NULL};

  A1.p = calloc(A1.len, sizeof(int));
  if (NULL == A1.p) {
    abort();
  }

  for(i = A1.len; i < A.len; ++i) {
    //shiftA1 is requred to have degA1 == degA2
    //simply it makes constant term of the A1 polynomial == 0
    //Examples of A = A1*x + A2:
    // x2 + 2x + 1 == (x + 0)*x + (2x+1)
    // x3 + 3x2 + 4x + 7 == (x + 3x)*x2 + (4x + 7)
    A1.p[i-degA1-shiftA1] = A.p[i];
  }
  if (shiftA1 == 0) {
    A1.p[0] = 0;
  }

  return A1;
}

struct Poly
low_coeff(const struct Poly A) {
  unsigned i;
  unsigned degA = A.len - 1;
  unsigned degA2 = degA/2;
  struct Poly A2 = {degA2 + 1, NULL};

  A2.p = calloc(A2.len, sizeof(int));
  if (NULL == A2.p) {
    abort();
  }

  for(i = 0; i < A2.len; ++i) {
    A2.p[i] = A.p[i];
  }

  return A2;
}

void poly_sum(struct Poly const A, struct Poly const B, struct Poly *res) {
  unsigned i;
  if (A.len != B. len) {
    abort();
  }

  res -> len = A.len;
  for(i = 0; i < res -> len; ++i) {
    res -> p[i] = A.p[i] + B.p[i];
  }
}

struct Poly
poly_mult_karatsuba(struct Poly A, struct Poly B) {
  struct Poly A1, A2, B1, B2;
  struct Poly res, res1, res2, res3;

  if (A. len == 1) {
    return A;
  }
  A1 = high_coeff(A);
  A2 = low_coeff(A);

  B1 = high_coeff(B);
  B2 = low_coeff(B);

  res1 = poly_mult_karatsuba(A1, B1);
  res3 = poly_mult_karatsuba(A2, B2);

  poly_sum(A1, A2, &res1);
  poly_sum(B1, B2, &res2);


  free_Poly(&A1);
  free_Poly(&A2);
  free_Poly(&B1);
  free_Poly(&B2);

  free_Poly(&res1);
  free_Poly(&res2);
  free_Poly(&res3);
 
  res.len = 0;
  res.p = NULL;
  return res;
}

void canonic_form(struct Poly *A) {
  unsigned degA = (A -> len) - 1; //size is length of pol
  for (; degA >= 0; --degA) {
    if ((A ->p[degA]) != 0)
      // pol[degA] is first nonzero elem,
      A -> len = degA + 1;
      break;
  }
}

int main() {
  int size1, size2, size3;
  int *pol1, *pol2, *pol3;
  int i;

  test_karatsuba();

  if((2 != scanf("%d%d", &size1, &size2)) || (size1 != size2) ) {
    abort();
  }
  size3 = (size1 - 1) + (size2 - 1) + 1;

  pol1 = malloc(size1*sizeof(int));
  pol2 = malloc(size2*sizeof(int));
  pol3 = malloc(size3*sizeof(int));
  if (NULL == pol1 || NULL == pol2) {
    abort();
  }

  for(i = 0; i < size1; ++i) {
    scanf("%d", (pol1+i));
  }

  for(i = 0; i < size2; ++i) {
    scanf("%d", (pol2+i));
  }

  ppol_mult_quadric(pol1, size1, pol2, size2, pol3, size3);
  //size3 = canonic_form(pol3, size3);

  for(i = 0; i < size3; ++i) {
    printf("%d ", pol3[i]);
  }
  printf("\n");

  free(pol1);
  free(pol2);
  free(pol3);
  return 0;
}
