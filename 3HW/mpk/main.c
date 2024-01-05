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



void poly_mult_karatsuba(struct Poly A, struct Poly B) {
  //unsigned degA = A.len - 1;
  struct Poly A1, A2, B1, B2;

  A1 = high_coeff(A);
  A2 = low_coeff(A);

  B1 = high_coeff(B);
  B2 = low_coeff(B);

  free_Poly(&A1);
  free_Poly(&A2);
  free_Poly(&B1);
  free_Poly(&B2);
}

unsigned canonic_form(int *pol, unsigned size) {
  --size; //size is length of pol
  for (; size >= 0; --size) {
    if (pol[size] != 0)
      // pol[size] is first nonzero elem,
      // i.e. size of arr is size+1
      return ++size;
  }
  return 0;
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
  size3 = canonic_form(pol3, size3);

  for(i = 0; i < size3; ++i) {
    printf("%d ", pol3[i]);
  }
  printf("\n");

  free(pol1);
  free(pol2);
  free(pol3);
  return 0;
}
