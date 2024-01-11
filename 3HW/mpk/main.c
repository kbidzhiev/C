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

struct Poly termA2(const struct Poly A) {
  struct Poly A2 = {A.len/2, A.p};
  return A2;
}

struct Poly termA1(const struct Poly A) {
  struct Poly A1 = {A.len/2, A.p + A.len/2};
  return A1;
}

struct Poly Pmul(const struct Poly A, const struct Poly B) {
  struct Poly C;
  //struct Poly term1; //A1B1
  //struct Poly term2; //Karatsuba term
  //struct Poly term3; //A2B2
  struct Poly A1, A2, B1, B2;
  C = Palloc(A.len + B.len - 1); //len(A) == len(B) == pow(2,k)

  A1 = termA1(A);
  A2 = termA2(A);

  B1 = termA1(B);
  B2 = termA2(B);



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
