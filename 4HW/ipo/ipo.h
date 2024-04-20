#ifndef ipo
#define ipo

struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
}

void print_pre(struct tree_t *top);


#endif
