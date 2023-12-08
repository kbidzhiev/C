#include"sieve.h"
#include<limits.h>
#include<stdlib.h>

struct sieve_t{
  int n;
  unsigned char *mod1;
  unsigned char *mod5;
};

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

