#include<stdio.h>
#include<stdlib.h>


int is_prime(int n){
  int j;
  if (n == 2) return 1;
  if ((n < 2) || (n%2 == 0)) return 0;
  for (j = 3; j*j <= n; j+=2){
    if((n%j) == 0) return 0;
  }
  return 1;
}

int seq_size(int a, int b, int N){
  int n,counter = 0;
  int p;
  for(n = 0; n < N; ++n){
    p = n*n + a*n + b;
    if(p<=0 || !is_prime(p)) return counter;
    ++counter;
  }
  return counter;
}

int find_sequence(int N,int *pa, int *pb){
  int a, b, seq_length = 0;
  int tmp;
  for(a = -N+1; a < N; ++a){
    for (b = -N+1; b < N; ++b){
      tmp = seq_size(a, b, N);
      if(tmp > seq_length) {
        seq_length = tmp;
        *pa = a;
        *pb = b;
      }
    }
  }
  return seq_length;
}


int main(){
  int N = 0;
  int a, b, l;

  if (1 != scanf("%d", &N)) abort();

  l = find_sequence(N, &a, &b);
  printf("%d %d %d\n", a, b, l);


  return 0;
}



