#include "lr.h"


struct node_t * build_list(FILE *f) {
  struct node_t *top = NULL;
  struct node_t *list = NULL;
  int data = -1;
  while(1 ==  fscanf(f, "%d", &data)){
    if(NULL == list) {
      top = calloc(1, sizeof(struct node_t));
      top -> data = data;
      list = top;
      continue;
    }
    top -> next = calloc(1, sizeof(struct node_t));
    top = top -> next;
    top -> data = data;
  }
  return list;
}

void free_list(struct node_t *top) {
  struct node_t *tmp;
  while(top != NULL) {
    tmp = top -> next;
    top -> next = NULL;
    top -> data = 0;
    free(top);
    top = tmp;
  }
}

void print_list(const struct node_t * top) {
  while(NULL != top) {
    printf("%d ", top -> data);
    top = top -> next;
  }
  printf("\n");
}

int main(int argc, char **argv) {
  struct node_t *top;
  FILE *f = fopen(argv[1], "r");

  top = build_list(f);
  print_list(top);
  top = reverse(top);
  print_list(top);

  free_list(top);
  fclose(f);
  return 0;
}
