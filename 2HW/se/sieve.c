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

void build_sieve(struct sieve_t *s){
  // prime numbers start from 2
  int prime = 2;
  while ( prime < (s -> n)){ // array [2:N] -> N-1 element
    remove_factors(s, prime);
    prime = firstp(s, prime)  ;
  }
}

int main(){
  int n, j=0;
  struct sieve_t s;
  if (1 != scanf("%d", &n)) abort();

  s = init_sieve(n); // we need n-1 numbers for sieve

  build_sieve(&s);


  for(int i = 2; i < s.n; ++i){
    if (s.s[i] == 0){
      //printf("%d ", i+ );
      ++j;
    }
  }
  //printf("\n");
  printf("%d\n",j);
  free_sieve(&s);


  return 0;
}
