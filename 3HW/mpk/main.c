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



int main(){

  return 0;
}
