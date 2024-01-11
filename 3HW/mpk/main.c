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

struct Poly Pmul(const struct Poly A, const struct Poly B) {
  struct Poly C;
  C = Palloc(A.len + B.len - 1);

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
