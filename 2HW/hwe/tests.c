#include<assert.h>
#include<math.h>
#include<stdio.h>
#include"sieve.h"
#include"hwe.h"

void test(){
  int size = 70000000;//25000000;
  struct sieve_t sv;
  init_sieve(&sv, size);

  fill_sieve(&sv);

  assert(29 == nth_prime(&sv, 10));
  assert(71 == nth_prime(&sv, 20));
  assert(113 == nth_prime(&sv, 30));
  assert(173 == nth_prime(&sv, 40));

  assert(7919 == nth_prime(&sv, 1000));
  assert(1400305337 == nth_prime(&sv, 70000000));
  assert(472882027 == nth_prime(&sv, 25000000));

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

  //printf("mod1[0] = %02hhx\n", sv.mod1[0]);
  //printf("mod5[1] = %02hhx\n", sv.mod5[0]);

  free_sieve(&sv);
  printf("tests are DONE\n");
}
