#include"px.h"
#include<stdlib.h>
#include<stdio.h>
/*
void powNxN (unsigned (*A)[N], unsigned k, unsigned m) {
  unsigned mult = n%m;
  unsigned prod = 1;
  while (k > 0) {
    if ((k % 2) == 1)
      prod = (prod * mult) % m;
    mult = (mult * mult) % m;
    k /= 2;
  }
}
*/


typedef unsigned (*row_t)[N];

row_t * Mcalloc(){
  row_t * M = (row_t *)calloc(N, sizeof(row_t));
  if (NULL == M) {
    printf("calloc of N rows failed\n"); 
    abort();
  }
  for (int i = 0; i < N; ++i) {
    M[i] = (row_t) calloc(N, sizeof(unsigned));
    if(NULL == M[i]) {
      printf("calloc of a %d-th row failed\n", i);
      abort();
    }
  }
  return M;
}
void Mfree(row_t * M) {
 for (int i = 0; i < N; ++i) 
   free(M[i]);
 free(M);
}

row_t * idMat() {
  row_t *res = Mcalloc();
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      if(i == j)
        (*res)[i][j] = 1;
  return res;
}
/*
unsigned (*)[N] matmul(unsigned (*A)[N], unsigned (*B)[N]};
void powNxN (unsigned (*A)[N], unsigned k, unsigned m) {
  int i;
  int Prod[N];
  int Mult[N];
  reminder(N, Mult, m);

  Identity(Prod);
  while (k>0){
    if ((k%2) == 1){
      //prod = (prod*mult)%m;
      multiplication(Prod, Mult, Prod);
      reminder(Prod, Prod, m);
    }
    //mult = (mult * mult)%m;
    multiplication(Mult, Mult, Mult);
    reminder(Mult, Mult, m);
    k = k/2;
  }
  for(i = 0; i<SIZE; ++i){
    N[i] = Prod[i];
  }
}
*/

