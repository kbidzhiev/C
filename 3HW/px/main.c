#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

//#include"px.h"

#define N 5

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

void Mprintf(mat_t M) {
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j) {
      printf("%u ", M[i][0][j]);
    }
    printf("\n");
  }
}

int main(void) {
  mat_t M = Mcalloc(); 
  Mprintf(M);
  return 0;
}
