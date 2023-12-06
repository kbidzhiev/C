#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>

#define flag 1

#if flag
struct sieve_t{
  int n;
  char *s;
};
#endif

struct sieve_t init_sieve(int size){
  struct sieve_t se;
  int i;
  char *pe = calloc(size, sizeof(char));
  if (NULL == pe) abort();
  //for (i = 0; i < size; ++i) pe[i] = 0; // all of the numbers are prime from the beginning
  se.s = pe;
  se.n = size;

  assert(se.s != NULL);
  assert(se.n>0);
  return se;
}

void free_sieve(struct sieve_t *s){
  free(s -> s);
  s -> n = 0;
}

unsigned firstp(struct sieve_t *s, unsigned p){
  for (unsigned i = p + 1  ; i < s->n; ++i){
    if ((s -> s[i]) == 0) return i;
  }
  return s->n;
}

void remove_factors(struct sieve_t *s, unsigned long long p){
  for (unsigned long long i = p*p ; i < s->n; i += p){ // sieve[2] labels 2;
    s -> s[i] = 1;
  }
}

void fill_sieve(struct sieve_t *sv){
  // prime numbers start from 2
  unsigned long long prime = 2;
  while ( prime*prime < (sv -> n)){ // array [0:n-1] -> n elements
    remove_factors(sv, prime);
    prime = firstp(sv, prime)  ;
  }
}

int nth_prime(struct sieve_t *sv, int N){
    for (int i = 2; i <= sv ->n; ++i){
      if (sv ->s[i] == 0) --N;
      if (N == 0) return i;
    }
    return 0;
}

int is_prime(unsigned n){
  unsigned j;
  if (n<2) return 0;
  for(j = 2; j*j <= n; ++j){
    if(n%j == 0) return 0;
  }
  return 1;
}

#if flag

int sieve_size(int N){
  return (int)(N*(log(N) + log(log(N))));
}

void tests(){
  struct sieve_t s;
  int n1, n2, i;
  int N = 100000;
  int n = sieve_size(N);
  s = init_sieve(n);
  fill_sieve(&s);


  for (i = 1; i <=N; ++i){
    n1 = nth_prime(&s, i);
    n2 = is_prime(n1);
    if (1 != n2){
      printf("%d = %d-th prime\n", n1, i);
      abort();
    }
  }
  printf("tests are ok\n");

  free_sieve(&s);
}

void tests1(){
struct sieve_t s;
  int n1, n2, i;
  int N = 1000000;
  int n = sieve_size(N);
  s = init_sieve(n);
  fill_sieve(&s);

  n1 = nth_prime(&s, N);
  if (n1 != 15485863){
    printf("n1 = %d != 15485863\n", n1);
    abort();
  }
  assert(n1 == 15485863);
  printf("done\n");
}

int main(){
  //tests();
  tests1();

  return 0;
}
#endif
