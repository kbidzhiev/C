//#include"px.h"
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

typedef unsigned (row_t)[N];
typedef row_t * mat_t;


mat_t Mcalloc() {
  mat_t M = calloc(N, sizeof(row_t));
  if (NULL == M) {
    printf("Fail to allocate N rows\n");
    abort();
  }
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      M[i][j] = 0;
  return M;
}

void Mfree(mat_t M) {
  free(M);
}
void Mprintf(mat_t M) {
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j)
      printf("%u ", M[i][j]);
    printf("\n");
  }
}

mat_t Id() {
  mat_t M = Mcalloc();
  for(int i = 0; i < N; ++i)
    M[i][i] = 1;
  return M;
}

void rem(mat_t M, unsigned mod) {
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      M[i][j] = (M[i][j]) % mod;
}

mat_t matmul(mat_t A, mat_t B) {
  mat_t res = Mcalloc();
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      for(int k = 0; k < N; ++k)
        res[i][j] += A[i][k] * B[k][j];
  return res;
}


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
void matcopy(mat_t from, mat_t to) {
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      to[i][j] = from[i][j];
}

void powNxN (unsigned (*A)[N], unsigned k, unsigned m) {
  mat_t tmp;
  mat_t prod = Id(); //prod = 1
  mat_t mult = Mcalloc();
  matcopy(A, mult);
  rem(mult, m);
  while (k > 0) {
    if ((k % 2) == 1) {
      tmp = matmul(mult, prod);
      matcopy(tmp, prod);

      Mfree(tmp);
      rem(prod, m);
    }
    tmp = matmul(mult, mult);
    matcopy(tmp, mult);
    Mfree(tmp);
    rem(mult, m);
    k /= 2;
  }
  matcopy(prod, A);
  Mfree(prod);
  Mfree(mult);
}

void callmat() {
  //A = {1 1 1 0}, N = 2, x = 20, m = 10
  mat_t M = Mcalloc();
  M[0][0] = 1;
  M[0][1] = 1;
  M[1][0] = 1;
  M[1][1] = 0;
  powNxN(M, 20, 10);
  Mprintf(M);
  /* 
  for(int i = 0; i < 8; ++i) {
    printf("i = %u\n", i);
    M[0][0] = 1;
    M[0][1] = 1;
    M[1][0] = 1;
    M[1][1] = 0;
    powNxN(M, i, 10);
    Mprintf(M);
    printf("\n");
  }
  */
  Mfree(M);
}
