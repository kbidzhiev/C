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
typedef row_t * mat_t;


mat_t Mcalloc() {
  mat_t M = calloc(N, sizeof(row_t));
  if (NULL == M) {
    printf("Fail to allocate N rows\n");
    abort();
  }
  for(int i = 0; i < N; ++i) {
    M[i] = calloc(1, sizeof(unsigned[N]));
    if (NULL == M[i]) {
      printf("Fail to allocate row %d, cleaning up\n", i);
      while(--i > 0)
        free(M[i]);
      free(M); 
      abort();
    }
  }
  return M;
}

void Mfree(mat_t M) {
  for (int i = 0; i < N; ++i) {
    free(M[i]);
  }
  free(M);
}
void Mprintf(mat_t M) {
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j) {
      printf("%u ", M[i][0][j]);
    }
    printf("\n");
  }
}

mat_t Id() {
  mat_t M = Mcalloc();
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j) {
      if (i == j)
        M[i][0][j] = 1;
    }
  }
  return M;
}

void callmat() {
  mat_t M = Id();


  Mprintf(M);
  Mfree(M);
}
