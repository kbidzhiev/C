#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
};

int *alloc_array(const int size);
void print_array(int *data, int size);




int main(void) {
  int size;
  int *data;

  scanf("%d", &size);
  data = alloc_array(size);
  print_array(data, size);
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

void print_array(int *data, int size) {
  for(int i = 0; i < size; ++i) {
    printf("%d ", data[i]);
  }
  printf("\n"); 
}

