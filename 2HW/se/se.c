#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define OFFSET 2

struct sieve_t{
  unsigned char *sieve;
  unsigned size;
};

struct sieve_t init_sieve(unsigned size){
  struct sieve_t se;
  unsigned i;
  unsigned char *pe = calloc(size, sizeof(unsigned char));
  if (NULL == pe) abort();
  for (i = 0; i < size; ++i) pe[i] = 1; // all of the numbers are prime from the beginning
  se.sieve = pe;
  se.size = size;

  assert(se.sieve != NULL);
  assert(se.size>0);
  return se;
}

void free_sieve(struct sieve_t *s){
  free(s -> sieve);
  s -> size = 0;
}

unsigned firstp(struct sieve_t *s, unsigned p){
  for (unsigned i = p + 1 - OFFSET ; i < s->size; ++i){
    if ((s -> sieve[i]) == 1) return i;
  }
  return s->size;
}

void remove_factors(struct sieve_t *s, unsigned p){
  for (unsigned i = 2*p - OFFSET; i < s->size; i += p){ // sieve[0] labels 2;
    s -> sieve[i] = 0;
  }
}

void build_sieve(struct sieve_t *s){
  // prime numbers start from 2
  unsigned prime = 2;
  while ( prime-OFFSET < (s -> size)){ // array [2:N] -> N-1 element
    remove_factors(s, prime);
    prime = firstp(s, prime) + OFFSET;
  }
}

int main(){
  unsigned n, j=0;
  struct sieve_t s;
  if (1 != scanf("%u", &n)) abort();

  s = init_sieve(n-1); // we need n-1 numbers for sieve

  build_sieve(&s);


  for(unsigned i = 0; i < s.size; ++i){
    if (s.sieve[i] == 1){
      //printf("%u ", i+OFFSET);
      ++j;
    }
  }
  //printf("\n");
  printf("%u\n",j);
  free_sieve(&s);


  return 0;
}
