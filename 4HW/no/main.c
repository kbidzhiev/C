#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
};

typedef struct tree_t Tree;

int *alloc_array(const int size);
void print_array(const int *data, int size);

void print_tree(const Tree *top);

void add_first_node(Tree **ptop, const int new_data) {
  if(!ptop)
    abort();
  assert(*ptop == NULL);
  *ptop = calloc(1, sizeof(Tree));
  (*ptop) -> data = new_data;
}

void add_node(Tree **ptop, const int new_data) {
  Tree *next_l, *next_r, *new_node, *current;
  if(*ptop == NULL) {
    add_first_node(ptop, new_data);
    return;
  }
  current = *ptop;
  next_l = current -> left;
  next_r = current -> right;
  new_node = calloc(1, sizeof(Tree));
  new_node -> data = new_data;
  while(1) {
    if(new_node -> data < current -> data) {
      if(current -> left == NULL) {
        current -> left = new_node;
        return; 
      }
      current = current -> left; 
    } else {
      if(current -> right == NULL) {
        current -> right = new_node;
        return; 
      }
      current = current -> right; 
    }
  }
}

void parse_tree(Tree **ptop, const int* data, const int size) {
  for(int i = 0; i < size; ++i)
    add_node(ptop, data[i]);
}

void free_tree(Tree *top) {

}

int main(void) {
  int size;
  int *data;
  Tree *top = NULL;

  scanf("%d", &size);
  data = alloc_array(size);
  parse_tree(&top, data, size);
  print_tree(top);


  //print_array(data, size);
  free(data);
  return 0;
}

int *alloc_array(const int size) {
  int *data = calloc(size, sizeof(int));
  if (!data) {
    abort(); 
  }

  for(int i = 0; i < size; ++i) {
    scanf("%d", data + i);
  }
  return data;
}

void print_array(const int *data, int size) {
  printf("Array:\n"); 
  for(int i = 0; i < size; ++i) {
    printf("%d ", data[i]);
  }
  printf("\n"); 
}

void print_tree_recursion(const Tree *top) {
  if (!top)
    return;
  printf("%d ", top -> data);
  print_tree_recursion(top -> left);
  print_tree_recursion(top -> right);
}

void print_tree(const Tree *top) {
  //printf("Tree:\n");
  print_tree_recursion(top);
  printf("\n");
}


