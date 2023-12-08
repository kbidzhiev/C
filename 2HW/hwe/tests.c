#include<assert.h>
#include<math.h>
#include<stdio.h>
#include"sieve.h"
#include"hwe.h"


int is_prime_simple(unsigned long long n){
  if ((n ==2) || (n==3)) return 1;
  if ((n<2) || ((n%2)== 0) || ((n%3)==0)) return 0;

  for (unsigned long long j = 5; j*j <= n; j +=6)
    if (((n%j)==0) || (n%(j+2))==0) return 0;

  return 1;
}

void test_range(){
  int i, size = 1000;
  struct sieve_t sv;
  init_sieve(&sv, size);
  fill_sieve(&sv);

  for(i = 0; i<size; ++i){
    assert(is_prime_simple(i) == is_prime(&sv, i));
  }
  free_sieve(&sv);
  printf("tests range DONE\n");
}

void test_is_prime(){
  int size = sieve_size(7727);
  struct sieve_t sv;
  init_sieve(&sv, size);

  fill_sieve(&sv);

  assert(1 == is_prime(&sv, 13));
  assert(1 == is_prime(&sv, 17));
  assert(1 == is_prime(&sv, 37));
  assert(1 == is_prime(&sv, 71));
  assert(1 == is_prime(&sv, 97));
  assert(1 == is_prime(&sv, 7727));

  assert(0 == is_prime(&sv, 4681));
  assert(0 == is_prime(&sv, 87));
  assert(0 == is_prime(&sv, 15));
  assert(0 == is_prime(&sv, 30));
  assert(0 == is_prime(&sv, 77));
  assert(0 == is_prime(&sv, 96));

  free_sieve(&sv);
  printf("tests is_prime DONE\n");
}

void test_nth_prime(){
  int size = 70000000;
  struct sieve_t sv;
  init_sieve(&sv, size);
  fill_sieve(&sv);

  assert(29 == nth_prime(&sv, 10));
  assert(71 == nth_prime(&sv, 20));
  assert(113 == nth_prime(&sv, 30));
  assert(173 == nth_prime(&sv, 40));
  assert(7919 == nth_prime(&sv, 1000));
  assert(472882027 == nth_prime(&sv, 25000000));
  assert(1400305337 == nth_prime(&sv, 70000000));

  free_sieve(&sv);
  printf("tests nth_prime DONE\n");
}


void test(){
  test_range();
  test_is_prime();
  test_nth_prime();
  printf("tests all DONE\n");
}
