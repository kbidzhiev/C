//#include "ipo.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAIN 0

#if MAIN
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

int empty(struct stack_t *s) {
  if(NULL == s)
    return 1;
  return 0;
}

struct tree_t* pop(struct stack_t **pstack) {
  struct tree_t *data;
  struct stack_t *next;
  data = (*pstack) -> data;
  next = (*pstack) -> next;
  free(*pstack);
  *pstack = next;
  return data;
}

struct stack_t* fill_stack(struct tree_t *top) {
  struct stack_t *s1=NULL, *s2=NULL;
  s1 = push(s1, top);
  while(!empty(s1)) {
    struct tree_t *node = pop(&s1);
    if (NULL != node -> right) {
      s1 = push(s1, node);
      s1 = push(s1, node -> right);
      continue;
    }
    s2 = push(s2, node);
    if(empty(s1))
      continue;
    node = pop(&s1);
    s2 = push(s2, node);
    s1 = push(s1, node -> left);
  }
  return s2;
}

int list_is_ordered(struct stack_t *top) {
  struct stack_t *next;
  if (NULL == top)
    return 1;
  next = top -> next;
  if (NULL == next)
    return 1;
  while (NULL != next) {
    int data0 = top -> data -> data;
    int data1 = next -> data -> data;
    if(data0 > data1)
      return 0;
    top = next;
    next = top -> next;
  }
  return 1;
}

void free_stack(struct stack_t *top) {
  struct stack_t *tmp;
  while(NULL != top) {
    tmp = top ->next;
    free(top);
    top = tmp;
  }
}

int check_is_bst(struct tree_t *top) {
  struct stack_t *s = fill_stack(top);
  int res = list_is_ordered(s);
  free_stack(s);
  //printf("%d", res);
  return res;
}

void print_pre(struct tree_t *root) {
  struct stack_t *s = fill_stack(root);
  while(!empty(s)) {
    struct tree_t *node = pop(&s);
    printf("%d ", node -> data);
  }
}



#if MAIN
void test_ordered() {
    
}

int main() {


}

#endif
