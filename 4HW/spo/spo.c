//#include "ipo.h"
#include <stdio.h>
#include <stdlib.h>

#if 0
struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
};
#endif

struct stack_t {
  struct stack_t *next;
  struct tree_t *data;
};

struct stack_t* push(struct stack_t *top, struct tree_t *data) {
  struct stack_t *node; 
  if (NULL == data)
    return top;
  node = calloc(1, sizeof(struct stack_t));
  node -> data = data;
  node -> next = top;
  return node;
}

struct tree_t* pop(struct stack_t **stack) {
  struct tree_t *data = (*stack) -> data;
  struct stack_t *next = (*stack) -> next;
  free(*stack);
  *stack = next;
  return data;
}

int empty(struct stack_t *s) {
  if(NULL == s)
    return 1;
  return 0;
}

struct stack_t* fill_stack(struct tree_t *top) {
  struct stack_t *s1=NULL, *s2=NULL;
  s1 = push(s1, top);
  while(!empty(s1)) {
    struct tree_t *node = pop(&s1);
    s2 = push(s2, node);
    s1 = push(s1, node -> left);
    s1 = push(s1, node -> right);
  }
  return s2;
}

void print_pre(struct tree_t *root) {
  struct stack_t *s = fill_stack(root);
  while(!empty(s)) {
    struct tree_t *node = pop(&s);
    printf("%d ", node -> data);
  }
}
