#include<stdio.h>
#include<stdlib.h>
#include"al.h"
#include"hl.h"

void print_list(const struct node_t *list_in) {
  const struct node_t * list = list_in;
  for(;NULL != list; list = list -> next)
    printf("%d ", list -> data);
  printf("\n");
}

void make_a_loop(struct node_t *list) {
  struct node_t *top = list;
  while(NULL != top -> next)
    top = top -> next;

  top -> next = list;
}

int main(int argc, char **argv) {
  FILE *f;
  struct node_t *list;
  char *name;
  if (argc != 2) {
    fprintf(stderr, "Provie a file\n");
    abort();
  }
  name = argv[1];
  printf("%s\n", name);
  f = fopen(argv[1], "r");
  if(NULL == f) {
    perror("Error opening file");
    abort();
  }
  list = read_list(f);
  fclose(f);

  print_list(list);
  make_a_loop(list);
  delete_list(list);
  //print_list(list);
  return 0;
}
