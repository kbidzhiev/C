#ifndef al
#define al

struct node_t {
  struct node_t *next;
  int data;
};

struct node_t *read_list(FILE *inp);
void delete_list(struct node_t *top);
#endif
