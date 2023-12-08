#include<stdio.h>
#include<stdlib.h>
#include"sieve.h"
#include"hwe.h"
#include"tests.c"

void print_nth_prime(){
  unsigned n, p, size;
  struct sieve_t sv;

  printf("Enter n:\n");
  if(1 != scanf("%u", &n)) abort();

  size = sieve_size(n);
  init_sieve(&sv, size);
  fill_sieve(&sv);

  p = nth_prime(&sv, n);
  printf("%u-th prime is %u\n", n, p);
}

int main(){
  //test();
  print_nth_prime();
  return 0;
}

