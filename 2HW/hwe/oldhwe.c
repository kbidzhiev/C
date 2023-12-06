#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<limits.h>
#include<math.h>

#define HWE 1

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

char read_bite(unsigned char n, char i){
  return (n >> i) & 1u;
}

int is_prime(struct sieve_t *sv, unsigned N){
  int bucket, k;
  unsigned char bite, r;
  unsigned long long tmp = 6*CHAR_BIT*(sv ->n);

  if(N == 1) return 0;
  if(N == 2 || N == 3) return 1;
  k = N/6, r = N%6;
  bucket = k/CHAR_BIT;
  bite = k%CHAR_BIT;
  if(bucket >= (sv -> n)){
    printf("sieve has numbers up to %llu; N = %u\n", tmp, N);
    abort();
  }
  if (r == 1)
    return read_bite(sv ->mod1[bucket], bite) == 0 ? 1: 0;
  if (r == 5)
    return read_bite(sv ->mod5[bucket], bite) == 0 ? 1: 0;

  return 0; //primes are 6k+1 or 6k+5 only;
}


void fill_sieve(struct sieve_t *sv){
  unsigned long long Nmax;
  unsigned long long bucket, i, j, q, r;
  char bite;
  Nmax = (sv -> n)* CHAR_BIT;

  sv -> mod1[0] = 0x11;
  //2 filters !

  for(i = 2; ; ++i){
    q = i/6;
    if(q > (sv ->n)*CHAR_BIT) break;
    if(is_prime(sv, i)){
      if((i/6) > (sv ->n)*CHAR_BIT/i) break;//overflow
      for(j = i+i; ; j+= i){
        q = j/6;
        r = j%6;
        bucket = q/CHAR_BIT;
        bite = q%CHAR_BIT;
        if(bucket >= (sv -> n)) break;
        if (r == 1) (sv ->mod1[bucket]) |= (1u<<bite);
        if (r == 5) (sv ->mod5[bucket]) |= (1u<<bite);

      }
    }
  }
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
  int size = 1<<20;//25000000;
  struct sieve_t sv;
  //init_sieve(&sv, 25000000);

  init_sieve(&sv, size);

  fill_sieve(&sv);


  //assert(29 == nth_prime(&sv, 10));
  //assert(71 == nth_prime(&sv, 20));
  //assert(113 == nth_prime(&sv, 30));
  //assert(173 == nth_prime(&sv, 40));

  //assert(7919 == nth_prime(&sv, 1000));
  //assert(1400305337 == nth_prime(&sv, 70000000));
  //assert(472882027 == nth_prime(&sv, 25000000));


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
