#include<stdio.h>
#include<stdlib.h>
//#include"hl.h"
//#include"al.h"

struct node_t* next(struct node_t *list) {
  if (NULL != list)
    list = list -> next;
  return list;
}

int list_is_a_loop(struct node_t *top) {
  struct node_t *hare, *turtle;
  turtle = top;
  hare = top;
  hare = next(hare);
  while(turtle != hare && NULL != hare) {
    hare = next(hare);
    hare = next(hare);
    turtle = next(turtle);
  }
  if(NULL != hare) 
    return 1;
  return 0;
}
