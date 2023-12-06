#include<stdio.h>
#include<stdlib.h>

unsigned long long peano_period(unsigned long long m){
  unsigned long long pp = 0ull;
  unsigned long long fnm1 = 1ull;
  unsigned long long fnm2 = 0ull;

  if (m == 0) return pp;
  if (m == 1){
    pp = 1ull;
    return pp;
  }

  pp = 2ull;
  while(1){
    unsigned long tmp = fnm1;
    fnm1 = (fnm1 + fnm2)%m;
    fnm2 = tmp;
    if (fnm2 == 1ull && fnm1 == 0ull){ return pp;}
    ++pp;
  }
  return 0ull;
}

unsigned long long fib(unsigned long long n, unsigned m){
  unsigned long long fnm1, fnm2;
  fnm1 = 1ull;
  fnm2 = 0ull;
  if (n == 0) return fnm2;
  for(; n > 1; --n){
    unsigned long long tmp = fnm1 % m ;
    fnm1 = (fnm1 + fnm2)%m;
    fnm2 = tmp;
  }
  return fnm1;
}


int main(){
  unsigned long long x;
  unsigned long long m;
  unsigned long long pp;
  if(scanf("%llu%llu",&x,&m) != 2){
    abort();
  }

  pp = peano_period(m);
  printf("%llu %llu\n", fib(x%pp,m), pp);


  return 0;
}
