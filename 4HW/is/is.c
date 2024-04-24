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
  struct tree_t *tree_node;
};

struct stack_t* push(struct stack_t *top, struct tree_t *new_tree_node) {
  struct stack_t *node; 
  if (NULL == new_tree_node)
    return top;
  node = calloc(1, sizeof(struct stack_t));
  node -> tree_node = new_tree_node;
  node -> next = top;
  return node;
}

int empty(struct stack_t *s) {
  return NULL == s;
}

struct tree_t* pop(struct stack_t **pstack) {
  struct tree_t *data = (*pstack) -> tree_node;
  struct stack_t *next = (*pstack) -> next;
  free(*pstack);
  *pstack = next;
  return data;
}

struct stack_t* fill_stack(struct tree_t *top) {
  struct stack *s1 = NULL, *s2 = NULL;
  struct tree_t *current = top;

  while(!empty(s1) || NULL != current) {
    while(NULL != current) {
      s1 = push(s1, current);
      current = current -> right;
    }
    current = pop(&s1);
    s2 = push(s2, current);
    current = current -> left;
  }
  return s2;
}
int list_is_ordered(struct stack_t *head) {
  struct stack_t *top = head;
  while ((NULL != top) && (NULL != top -> next)) {
    int data0 = top -> tree_node -> data;
    int data1 = top -> next -> tree_node -> data;
    if(data0 > data1)
      return 0;
    top = top -> next;
  }
  return 1;
}

void free_stack(struct stack_t *top) {
  struct stack_t *tmp;
  while(NULL != top) {
    tmp = top;
    top = top -> next;
    free(tmp);
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
