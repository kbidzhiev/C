#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include"hwe.h"


char read_bit(unsigned char n, char i){
  return (n >> i) & 1u;
}

int is_prime(struct sieve_t *sv, unsigned N){
  unsigned k, bucket;
  unsigned char bit, r;

  if(N == 1) return 0;
  if(N == 2 || N == 3) return 1;
  k = N/6, r = N%6;
  bucket = k/CHAR_BIT;
  bit = k%CHAR_BIT;

  if (r == 1) return read_bit(sv ->mod1[bucket], bit) == 0 ? 1: 0;
  if (r == 5) return read_bit(sv ->mod5[bucket], bit) == 0 ? 1: 0;

  return 0; //primes are 6k+1 or 6k+5 only;
}

void tozero(struct sieve_t *sv, unsigned long long j){
  unsigned bucket;
  char bit;
  bucket = j/(6*CHAR_BIT);
  bit = (j/6)%CHAR_BIT;
  if (j%6 == 1) (sv ->mod1[bucket]) |= (1u<<bit);
  if (j%6 == 5) (sv ->mod5[bucket]) |= (1u<<bit);
}

void fill_sieve(struct sieve_t *sv){
  unsigned long long i, j;
  sv -> mod1[0] = 0x11;

  for(i = 1; (i/(6*CHAR_BIT)) < (sv->n);++i)
    if(is_prime(sv, i))
      for(j = i*i; (j/(6*CHAR_BIT)) < (sv->n); j+=i)
        tozero(sv, j);
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

