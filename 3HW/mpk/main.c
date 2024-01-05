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

struct Poly
high_coeff(const struct Poly A) {
  unsigned i;
  unsigned degA = A.len - 1;
  unsigned degA1 = degA/2;
  unsigned shiftA1 = degA % 2; // degA == 2*k ?
  struct Poly A1 = {degA1 + 1, NULL};

  A1.p = calloc(A1.len, sizeof(int));
  if (NULL == A1.p) {
    printf("high_coeff: mem not allocated\n");
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
    printf("low_coeff: mem not allocated\n");
    abort();
  }

  for(i = 0; i < A2.len; ++i) {
    A2.p[i] = A.p[i];
  }
  return A2;
}

struct Poly
poly_sum(const struct Poly A, const struct Poly B) {
  unsigned i;
  struct Poly res;
  if (A.len != B. len) {
    printf("poly_sum: A.len != B.len\n");
    abort();
  }
  res.len = A.len;
  res.p = malloc(res.len * sizeof(int));
  if (NULL == res.p) {
    printf("poly_sum: mem not allocated\n");
    abort();
  }
  for(i = 0; i < res.len; ++i) {
    res.p[i] = A.p[i] + B.p[i];
  }
  return res;
}



struct Poly
poly_mult_karatsuba(struct Poly A, struct Poly B);

struct Poly
first_term(const struct Poly A, const struct Poly B) {
  struct Poly A1, B1, A1B1;
  A1 = high_coeff(A);
  B1 = high_coeff(B);
  A1B1 = poly_mult_karatsuba(A1, B1);
  free_Poly(&A1);
  free_Poly(&B1);
  return A1B1;
}

struct Poly
third_term(const struct Poly A, const struct Poly B) {
  struct Poly A2, B2, A2B2;
  A2 = low_coeff(A);
  B2 = low_coeff(B);
  A2B2 = poly_mult_karatsuba(A2, B2);
  free_Poly(&A2);
  free_Poly(&B2);
  return A2B2;
}

struct Poly
add_high_low(const struct Poly A){
  struct Poly A1, A2, addA1A2;
  A1 = high_coeff(A);
  A2 = low_coeff(A);
  addA1A2 = poly_sum(A1,A2);

  free_Poly(&A1);
  free_Poly(&A2);
  return addA1A2;
}

void subtract(struct Poly tmp, const struct Poly A1B1, const struct Poly A2B2){
  for(unsigned i = 0; i < tmp.len; ++i){
    tmp.p[i] = tmp.p[i] - A1B1.p[i] - A2B2.p[i];
  }
}

struct Poly
second_term(const struct Poly A, const struct Poly B, const struct Poly A1B1, const struct Poly A2B2) {
  struct Poly addA1A2, addB1B2, res;
  addA1A2 = add_high_low(A);
  addB1B2 = add_high_low(B);

  res = poly_mult_karatsuba(addA1A2, addB1B2);
  subtract(res, A1B1, A2B2);

  free_Poly(&addA1A2);
  free_Poly(&addB1B2);
  return res;
}

void copy_coeff(struct Poly a, struct Poly A, unsigned begin, unsigned end) {
  if (A.len < end) {
    printf("copy_coeff: A.len < end\n");
    abort();
  }
  for(unsigned i = begin; i < end; ++i) {
    A.p[i] = a.p[i-begin];
  }
}

struct Poly
poly_mult_karatsuba(struct Poly A, struct Poly B) {
  struct Poly res, A1B1, term2, A2B2;

  if (A. len == 1) {
    res = poly_mult_quadratic(A, B);
    return res;
  }

  A1B1 = first_term(A, B);
  A2B2 = third_term(A, B);
  term2 = second_term(A, B, A1B1, A2B2);

  res.len = A2B2.len + term2.len + A1B1.len;
  res.p = malloc(re.len * sizeof(int));
  if(NULL == res.p) {
    printf("poly_mult_karatsuba: mem not allocated\n");
    abort();
  }

  copy_coeff(A2B2,  res, 0, A2B2.len);
  copy_coeff(term2, res, A2B2.len, A2B2.len + term2.len);
  copy_coeff(A1B1,  res, A2B2.len + term2.len, res.len) ;

  free_Poly(&A1B1);
  free_Poly(&term2);
  free_Poly(&A2B2);

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
