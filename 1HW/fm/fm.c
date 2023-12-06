#include<stdio.h>
#include<stdlib.h>


unsigned long long fib(unsigned long long n, unsigned m){
  unsigned long long fnm1, fnm2;
  fnm1 = 1ull;
  fnm2 = 0ull;
  if (n == 0) return fnm2;
  for(; n > 1; --n){
    unsigned long long tmp = fnm1 % m ;
    fnm1 = (fnm1 + fnm2)%m;
    fnm2 = tmp;
    //fnm2 = (fnm1 - fnm2%m)%m;
  }
  return fnm1;
}


int main(){
  unsigned long long x;
  unsigned m;
  int scf;
  if(scanf("%llu%u",&x,&m) != 2){
    abort();
  }
  printf("%llu\n", fib(x,m));

  return 0;
}
