#ifndef SIEVE_H
#define SIEVE_H

struct sieve_t;
unsigned sieve_size(unsigned N);
void init_sieve(struct sieve_t *sv, int n);
void free_sieve(struct sieve_t *sv);

#endif // SIEVE_H
