#include<limits.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#include"sieve.h"
#include"hwe.h"

unsigned sieve_size(unsigned N){
  double n = (double) N;
  n = n*(log(N) + log(log(N)))/(3*CHAR_BIT);
  return ceil(n);
}

void init_sieve(struct sieve_t *sv, int n){
  unsigned char *p1 = calloc(n, sizeof(char));
  unsigned char *m1 = calloc(n, sizeof(char));
  if(NULL == p1 || NULL == m1) abort();
  sv -> n = n;
  sv -> mod1 = p1;
  sv -> mod5 = m1;
  assert(NULL != sv -> mod1);
  assert(NULL != sv -> mod5);
  assert((sv ->n) > 0);
}

void free_sieve(struct sieve_t *sv){
  sv -> n = 0;
  free(sv -> mod1);
  free(sv -> mod5);
}

unsigned nth_prime(struct sieve_t *sv, unsigned long long N){
  unsigned long long i;
  for (i = 1; N>0; ++i){
    if(is_prime(sv, i)){
      //printf("%u is %uth prime\n", i, N);
      --N;
    };
  }
  return --i;
}
