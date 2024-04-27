#include <stdio.h>
#include <stdlib.h>


typedef struct tree_t {
  struct tree_t *left; 
  struct tree_t *right;
  int data;
} Tree;

typedef struct arr {
  int *data;
  int size;
} Array;

Array read_array(const int size);
void print_array(const Array arr);
int find_pos(const Array arr, const int elem);

void build_tree(Tree **ptop, const Array preorder, const Array inorder);

Tree * make_node(const int data) {
  Tree* node = calloc(1, sizeof(Tree));
  if (!node)
    abort();
  node -> data = data;
  return node;
}

Tree * build_tree_recurs(const Array preorder, const Array inorder) {
  Tree *top = NULL;
  build_tree(&top, preorder, inorder);
  return top;
}



void build_tree(Tree **ptop, const Array preorder, const Array inorder) {
  Array preorder_left, preorder_right;
  Array inorder_left, inorder_right;
  Tree *node;
  int elem, pos;
  if (0 == preorder.size) 
    return;
  elem = preorder.data[0];
  pos = find_pos(inorder, elem);
  node = make_node(elem);
  *ptop = node;

  inorder_left.data = inorder.data;
  inorder_left.size = pos;

  inorder_right.data = inorder.data + pos + 1;
  inorder_right.size = inorder.size - pos - 1 ;

  preorder_left.data = preorder.data + 1;
  preorder_left.size = inorder_left.size;
  
  preorder_right.data = preorder.data + 1 + preorder_left.size;
  preorder_right.size = inorder_right.size;

  //print_array(inorder_left);
  //print_array(inorder_right);

  build_tree(&(node -> left), preorder_left, inorder_left);
  build_tree(&(node -> right), preorder_right, inorder_right);

}

void print_tree(Tree *top) {
  if (!top)
    return;
  print_tree(top -> left);
  printf("%d ", top -> data);
  print_tree(top -> right);
}

void free_tree(Tree *top) {
  Tree *right;
  if (!top)
    return;
  
  free_tree(top -> left);
  right = top -> right; 
  free(top);
  free_tree(right);
}


struct stack {
  struct stack *next;
  Tree * data;
};

struct stack *push(struct stack *top, Tree *data) {
  struct stack *node;
  if(!data)
    return top;
  node = calloc(1, sizeof(struct stack));
  node -> data = data;
  node -> next = top;
  return node;
}

Tree *pop(struct stack **pstack) {
  Tree *data = (*pstack) -> data;
  struct stack *next = (*pstack) -> next;
  free(*pstack);
  *pstack = next;
  return data;
}

struct stack *fill_stack(Tree *top) {
  struct stack *s1 = NULL, *s2 = NULL;
  s1 = push(s1, top);
  while(NULL != s1) {
    Tree *node = pop(&s1);
    s2 = push(s2, node);
    s1 = push(s1, node -> left);
    s1 = push(s1, node -> right);
  }
  return s2;
}

void print_post(Tree *top) {
  struct stack *s = fill_stack(top);
  while(NULL != s) {
    Tree *node = pop(&s);
    printf("%d ", node -> data);
  }
  printf("\n");
}

int main(void) {
  int size = 0;
  Array preorder, inorder;
  Tree * tree; 
  scanf("%d", &size);
   
  preorder = read_array(size);
  inorder = read_array(size);

  //print_array(preorder);
  //print_array(inorder);
  tree = build_tree_recurs(preorder, inorder);
  print_post(tree);

  free_tree(tree);
  free(inorder.data);
  free(preorder.data);

  return 0;
}


Array read_array(const int size) {
  Array arr = {NULL, size};
  arr.data = calloc(size, sizeof(int));
  if (!arr.data)
    abort(); 
  for(int i = 0; i < arr.size; ++i)
    scanf("%d", arr.data + i);

  return arr;
}

void print_array(const Array arr) {
  for(int i = 0; i < arr.size; ++i)
    printf("%d", arr.data[i]);
  printf("\n");
}

int find_pos(const Array arr, const int elem) {
  for(int i = 0; i < arr.size; ++i)
    if (elem == arr.data[i])
      return i;
  return -1;
}


