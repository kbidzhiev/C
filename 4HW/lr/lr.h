#ifndef lr
#define lr

#include <stdlib.h>
#include <stdio.h>

struct node_t {
  struct node_t *next;
  int data;
};

struct node_t *reverse(struct node_t *top);

#endif
