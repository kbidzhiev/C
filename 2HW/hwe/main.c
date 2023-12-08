#include<stdio.h>
#include<stdlib.h>
#include"sieve.h"
#include"hwe.h"
#include"tests.c"


int main(){
  //test();
  unsigned n, p, size;
  struct sieve_t sv;

  if(1 != scanf("%u", &n)) abort();

  size = sieve_size(n);
  init_sieve(&sv, size);
  fill_sieve(&sv);

  p = nth_prime(&sv, n);
  printf("%u-th prime is %u\n", n, p);

  return 0;
}

