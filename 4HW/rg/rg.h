#include <stdlib.h>
#include <stdio.h>


typedef int (*generator_t)(int);
unsigned cycle_len(generator_t gen);


