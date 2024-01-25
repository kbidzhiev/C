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

  //C = Pmult(A, B);

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

unsigned ln2(unsigned len) {
  unsigned res = 0;
  for(unsigned i = 0; i < 32; ++i) {
    if((len >> i) && 1u) {
      res = i;
    }
  }
  return res;
}


