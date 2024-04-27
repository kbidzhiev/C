#include <stdio.h>
#include <stdlib.h>


typedef struct tree_t {
  struct tree_t *left; 
  struct tree_t *right;
  int data;
} Tree;

int *read_array(const int size);
void print_array(const int * arr, const int size);
int find_pos(const int *arr, const int begin, const int end, const int elem);


int main(void) {
  int size = 0;
  int *preorder, *inorder;
  
  scanf("%d", &size);
   
  preorder = read_array(size);
  inorder = read_array(size);

  print_array(preorder, size);
  print_array(inorder, size);
  free(inorder);
  free(preorder);

  return 0;
}


int *read_array(const int size) {
  int *arr = calloc(size, sizeof(int));
  if (!arr)
    abort(); 
  for(int i = 0; i < size; ++i)
    scanf("%d", arr + i);
  return arr;
}

void print_array(const int * arr, const int size) {
  for(int i = 0; i < size; ++i)
    printf("%d", arr[i]);
  printf("\n");
}

int find_pos(const int *arr, const int begin, const int end, const int elem) {
  for(int i = begin; i < end; ++i)
    if (elem == i)
      return i;
}


