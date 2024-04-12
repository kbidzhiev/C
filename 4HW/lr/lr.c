#include "lr.h"


struct node_t *reverse(struct node_t *top) {
  struct node_t * i, *i_n, *i_p;
  if (NULL == top) return NULL;
  if (NULL == top->next) return top;
  i = top;
  i_n = top -> next;
  i_p = NULL; 
  while (NULL != i_n) {
    i -> next = i_p; 
    
    i_p = i;
    i = i_n;
    i_n = i_n -> next;
  }
  i -> next = i_p; 
  return i;

}
