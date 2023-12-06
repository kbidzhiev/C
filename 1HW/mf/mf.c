#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define SIZE  4

void reminder(int* A, int* R, int m){
  int i;
  for (i = 0; i<SIZE; ++i){
    R[i] = A[i]%m;
  }
}

void Identity(int *A){
  A[0] = 1;
  A[1] = 0;
  A[2] = 0;
  A[3] = 1;
}

void multiplication(int* A, int* B, int* C){
  int Res[SIZE];
  int i = 0;
  Res[0] = A[0]*B[0] + A[1]*B[2];
  Res[1] = A[0]*B[1] + A[1]*B[3];
  Res[2] = A[2]*B[0] + A[3]*B[2];
  Res[3] = A[2]*B[1] + A[3]*B[3];

  for(i = 0; i<SIZE; ++i){
    C[i] = Res[i];
  }
}

void pow_mod(int* N, int k, int m){
  int i;
  int Prod[SIZE];
  int Mult[SIZE];
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


int main(){
  int A[4];
  int i, k, m;
  if (6 != scanf("%d%d%d%d%d%d", &A[0], &A[1], &A[2], &A[3], &k, &m)) abort();

  pow_mod(A, k,m);
  for(i=0; i<SIZE; ++i){
    printf("%d ", A[i]);
  }
  printf("\n");
  return 0;
}
