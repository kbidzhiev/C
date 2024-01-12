#include<stdio.h>
#include<stdlib.h>

struct Poly {
  unsigned len;
  int *p;
};

struct Poly Palloc(unsigned len) {
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
  pol -> p = NULL; // How to check did free worked correctly
  if ((pol -> p != NULL) || (pol -> len != 0)) {
    printf("Pfree failed\n");
    abort();
  }
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

struct Poly termA2(const struct Poly *A) {
  struct Poly A2 = {A -> len/2, A ->p};
  return A2;
}

struct Poly termA1(const struct Poly *A) {
  struct Poly A1 = {A -> len/2, (A -> p) + (A -> len/2)};
  return A1;
}

struct Poly termA2B2(const struct Poly *C) {
  // Mathematical explanaition:
  // lenA + len B - 1 == lenC  // assert(lenA == lenB)
  // lenA1 + lenA2 == lenA //assert(lenA1 == lenA2 == lenB1 == lenB2)
  // => lenA == (lenC + 1)/2
  // => lenA2 == lenA/2
  // => lenA2B2 == lenA2 + lenB2 - 1 == lenA - 1 == (lenC - 1)/2
  unsigned lenA2B2 = (C -> len - 1)/2;
  struct Poly A2B2 = {lenA2B2, C -> p};
  return A2B2;
}

struct Poly termA1B1(const struct Poly *C) {
  // Mathematical explanaition:
  // lenA + len B - 1 == lenC  // assert(lenA == lenB)
  // lenA1 + lenA2 == lenA //assert(lenA1 == lenA2 == lenB1 == lenB2)
  // => lenA == (lenC + 1)/2
  // => lenA2 == lenA/2
  // => lenA1B1 == lenA1 + lenB1 - 1 == lenA - 1 == (lenC - 1)/2
  unsigned lenA1B1 = (C -> len - 1)/2;
  struct Poly A1B1 = {lenA1B1, C -> p + ((C -> len) - lenA1B1)};
  return A1B1;
}

struct Poly termA1A2(const struct Poly A1, const struct Poly A2, struct Poly *tmp) {
  unsigned i;
  struct Poly A1A2 = {A1.len, tmp -> p};
  for(i = 0; i < A1A2.len; ++i) {
    A1A2.p[i] = A1.p[i] + A2.p[i];
  }
  return A1A2;
}

struct Poly termB1B2(const struct Poly B1, const struct Poly B2, struct Poly *tmp) {
  unsigned i;
  struct Poly B1B2 = {B1.len, (tmp -> p) + B1.len};
  for(i = 0; i < B1B2.len; ++i) {
    B1B2.p[i] = B1.p[i] + B2.p[i];
  }
  return B1B2;
}
void Pmul_impl(const struct Poly *A,
                      const struct Poly *B,
                      struct Poly *C,
                      struct Poly *tmp) {
  struct Poly A1B1; //A1B1 stored in the begining of C
  struct Poly term2; //Karatsuba term stored in the middle of C
  struct Poly A2B2; //A2B2 stored in the end of C
  struct Poly A1, A2, B1, B2;
  struct Poly A1A2, B1B2;
  struct Poly tmp2; //point to the third part of tmp

  A1 = termA1(A); //write test
  A2 = termA2(A); //write test
  B1 = termA1(B);
  B2 = termA2(B);

  A1B1 = termA1B1(C); //A1B1 is empty //write test
  A2B2 = termA2B2(C); //A2B2 is empty //write test
  A1A2 = termA1A2(A1, A2, tmp); //A1 + A2 is written in tmp;
  B1B2 = termB1B2(B1, B2, tmp); //B1 + B2 is written in tmp;
  tmp2.len = A1A2.len + B1B2.len - 1;
  tmp2.p = tmp -> p + ((tmp -> len) - tmp2.len);

  Pmul_impl(&A1, &B1, &A1B1, &tmp2); //filling A1B1
  Pmul_impl(&A2, &B2, &A2B2, &tmp2); //filling A2B2
  
  Pmul_impl(A1A2, B1B2, tmp2, tmp); //filling Karatsuba term into tmp


  return ;
}

struct Poly Pmul(const struct Poly A, const struct Poly B) {
  struct Poly C, tmp;
  C = Palloc(A.len + B.len - 1); //len(A) == len(B) == pow(2,k)
  tmp = Palloc(A.len + B.len - 1); //len(A) == len(B) == pow(2,k)


  Pmul_impl(&A, &B, &C, &tmp);

  return C;
}

int main(){
  unsigned sizeA, sizeB;
  struct Poly A, B, C;

  if (2 != scanf("%d%d", &sizeA, &sizeB)) {
    printf("scanf of sizeA and sizeB failed\n");
    abort();
  }
  A = Palloc(sizeA);
  B = Palloc(sizeB);

  Pscanf(&A);
  Pscanf(&B);

  C = Pmul(A, B);

  Pprintf(A);
  Pprintf(B);

  return 0;
}
