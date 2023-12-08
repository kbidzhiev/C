#ifndef HWE_H
#define HWE_H

#include"sieve.h"

char read_bit(unsigned char n, char i);
int is_prime(struct sieve_t *sv, unsigned N);
void tozero(struct sieve_t *sv, unsigned long long j);
void fill_sieve(struct sieve_t *sv);

#endif //HWE_H


