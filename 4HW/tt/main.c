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

Tree * build_tree_recurs(const Array preorder, const Array inorder) {
  Tree *top;
  build_tree(top, preorder, inorder);
  return top;
}



void build_tree(const Array preorder, const Array inorder) {
  Array preorder_left, preorder_right;
  Array inorder_left, inorder_right;
  if (0 == preorder.size) 
    return;
  int elem = preorder.data[0];
  int pos = find_pos(inorder, elem);
  printf("%d -> %d\n", elem, pos);

  inorder_left.data = inorder.data;
  inorder_left.size = pos;

  inorder_right.data = inorder.data + pos + 1;
  inorder_right.size = inorder.size - pos - 1 ;

  preorder_left.data = preorder.data + 1;
  preorder_left.size = inorder_left.size;
  
  preorder_right.data = preorder.data + 1 + preorder_left.size;
  preorder_right.size = inorder_right.size;

  print_array(inorder_left);
  print_array(inorder_right);

  build_tree(preorder_left, inorder_left);
  build_tree(preorder_right, inorder_right);
  //print_array(preorder_left);
  //print_array(preorder_right);

}

int main(void) {
  int size = 0;
  Array preorder, inorder;
  
  scanf("%d", &size);
   
  preorder = read_array(size);
  inorder = read_array(size);

  print_array(preorder);
  print_array(inorder);
  build_tree(preorder, inorder);

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
}


