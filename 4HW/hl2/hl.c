#include<stdio.h>
#include<stdlib.h>
//#include"hl.h"
//#include"al.h"

struct node_t* next(struct node_t *list) {
  if (NULL != list)
    list = list -> next;
  return list;
}

int list_is_a_loop(struct node_t *top);
int loop_len(struct node_t *top) {
  return list_is_a_loop(top);
}
int list_is_a_loop(struct node_t *top) {
  int i = 0;
  struct node_t *hare, *turtle;
  turtle = top;
  hare = top;
  hare = next(hare);
  while(turtle != hare && NULL != hare) {
    hare = next(hare);
    hare = next(hare);
    turtle = next(turtle);
  }
  if(NULL == hare) 
    return 0;

  hare = turtle;  
  turtle = next(turtle);
  ++i;
  while(turtle != hare) {
    turtle = next(turtle);
    ++i;
  }
  return i;
}
