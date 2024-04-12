#include "lr.h"


struct node_t * build_list(FILE *f) {
  struct node_t *top = calloc(1, sizeof(struct node_t));
  struct node_t *list = top;
  while(1 == fscanf(f, "%d", &(top -> data))) {
    top -> next = calloc(1, sizeof(struct node_t));
    top = top -> next;
  }
  return list;
}

int main(int argc, char **argv) {
  int i = 0; 
  FILE *f = fopen(argv[1], "r");
  fclose(f);
  return 0;
}
