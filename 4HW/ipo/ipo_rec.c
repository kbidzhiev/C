#include <stdio.h>
#include <stdlib.h>


void print_pre(struct tree_t *top) {
  if (NULL == top) {
    return;
  }
  printf("%d ", top -> data);
  print_pre(top -> left);
  print_pre(top -> right);
}
