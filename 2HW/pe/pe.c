#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
#include<assert.h>

#define TESTS 1
#define MAIN 1

unsigned sieve_size(unsigned N){
  double n = (double) N;
  n = n*(log(N) + log(log(N)))/CHAR_BIT;
  return ceil(n);
}

#if MAIN
struct sieve_t{
  unsigned n;
  unsigned char *s;
};

struct sieve_t init_sieve(unsigned n){
  struct sieve_t s;
  unsigned N = n;//sieve_size(n);
  unsigned char* ps = calloc(N, sizeof(unsigned char));
  if(NULL == ps) abort();
  s.n = N;
  s.s = ps;

  assert(s.n > 0);
  assert(NULL != s.s);
  return s;
}

void free_sieve(struct sieve_t *s){
  s -> n = 0;
  free(s ->s);
}
#endif

int is_prime(struct sieve_t *sv, unsigned n){
  int bucket = n/CHAR_BIT;
  int bite = n%CHAR_BIT;

  int p = ((sv->s[bucket]) >> bite) & 1u;
  return (p == 0)? 1 : 0; // 0 for primes, 1 for composit
}

void set_prime(struct sieve_t *sv, unsigned n){
  int bucket = n/CHAR_BIT;
  int bite = n%CHAR_BIT;
  (sv -> s[bucket]) |= (1u<<bite);
}

void fill_sieve(struct sieve_t *sv){
  unsigned long long i,j;
  for (i = 2; i*i < (sv->n*CHAR_BIT); ++i)
    if(is_prime(sv, i))
      for(j = i*i; j < (sv->n*CHAR_BIT); j+=i)
        set_prime(sv,j);
}

#if TESTS
void test(){
  unsigned n = 100;
  struct sieve_t sv = init_sieve(100);
  fill_sieve(&sv);

  assert(1 == is_prime(&sv, 2));
  assert(1 == is_prime(&sv, 3));
  assert(1 == is_prime(&sv, 19));

  assert(0 == is_prime(&sv, 4));
  assert(0 == is_prime(&sv, 50));
  assert(0 == is_prime(&sv, 25));

  printf("s[0] = %02hhx\n", sv.s[0]);
  printf("s[1] = %02hhx\n", sv.s[1]);


  free_sieve(&sv);
  printf("tests complete\n");
}

#endif

#if MAIN

int main(){
#if TESTS
  test();
#endif

  return 0;
}

#endif
