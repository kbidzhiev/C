#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


struct sieve_t{
  int n;
  char *s;
};

struct sieve_t init_sieve(int size){
  struct sieve_t se;
  int i;
  char *pe = calloc(size, sizeof(char));
  if (NULL == pe) abort();
  for (i = 0; i < size; ++i) pe[i] = 0; // all of the numbers are prime from the beginning
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

int firstp(struct sieve_t *s, int p){
  for (int i = p + 1  ; i < s->n; ++i){
    if ((s -> s[i]) == 0) return i;
  }
  return s->n;
}

void remove_factors(struct sieve_t *s, int p){
  for (int i = 2*p ; i < s->n; i += p){ // sieve[0] labels 2;
    s -> s[i] = 1;
  }
}

void fill_sieve(struct sieve_t *sv){
  // prime numbers start from 2
  int prime = 2;
  while ( prime < (sv -> n)){ // array [2:N] -> N-1 element
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


void tests(){
  struct sieve_t s;
  int n1, n2, i;
  int j = 0;
  s = init_sieve(14);
  fill_sieve(&s);


  #if 1
  for (i = 1; i <=10; ++i){
    n1 = nth_prime(&s, i);
    n2 = is_prime(n1);
    if (1 != n2){
      printf("%d = %d-th prime\n", n1, i);
      abort();
    }
  }
#endif
  printf("tests are ok\n");

}

#if 0
int main(){
  tests();

  int n, j=0;
  struct sieve_t s;
  if (1 != scanf("%d", &n)) abort();

  s = init_sieve(n); // we need n-1 numbers for sieve

  fill_sieve(&s);


  for(int i = 2; i < s.n; ++i){
    //if (s.s[i] == 0)
    {
      printf("s[%d] == %d\t%d\n", i,s.s[i], ++j);
      //++j;
    }
  }
  //printf("\n");
  printf("%d\n",j);
  free_sieve(&s);


  return 0;
}
#endif
