#ifndef SIEVE_H
#define SIEVE_H


struct sieve_t{
  int n;
  unsigned char *mod1;
  unsigned char *mod5;
};

unsigned sieve_size(unsigned N);
void init_sieve(struct sieve_t *sv, int n);
void free_sieve(struct sieve_t *sv);
unsigned nth_prime(struct sieve_t *sv, unsigned long long N);



#endif // SIEVE_H
