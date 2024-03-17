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

typedef unsigned (row_t)[N];
typedef row_t * mat_t;


mat_t Mcalloc() {
  mat_t M = calloc(N, sizeof(row_t));
  if (NULL == M) {
    printf("Fail to allocate N rows\n");
    abort();
  }
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
    for(int j = 0; j < N; ++j)
      if (i == j)
        M[i][j] = 1;
  return M;
}

void rem(mat_t M, unsigned mod) {
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      M[i][j] = M[i][j] % mod;
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
  mat_t tmp, prod;
  rem(A, m);
  prod = Id();
  while (k > 0) {
    if ((k % 2) == 1) {
      tmp = matmul(prod, A);
      matcopy(tmp, prod);
      Mfree(tmp);
      rem(prod, m);
    }
    tmp = matmul(A, A);
    matcopy(tmp, A);
    Mfree(tmp);
    rem(A, m);
    k /= 2;
  }
}

void callmat() {
  mat_t M = Id();
  powNxN(M, 10, 4);
  Mprintf(M);
  Mfree(M);
}
