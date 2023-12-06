#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<limits.h>
#include<math.h>

#define HWE 0

#if HWE
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
#endif

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

#if HWE
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

void test(){
  int size = 70000000;//25000000;
  struct sieve_t sv;
  //init_sieve(&sv, 25000000);
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

  printf("mod1[0] = %02hhx\n", sv.mod1[0]);
  printf("mod5[1] = %02hhx\n", sv.mod5[0]);

  free_sieve(&sv);
  printf("tests are DONE\n");
}

int main(){
  test();

  return 0;
}

#endif //HWE
