#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

unsigned find_min(const int *arr, unsigned len, unsigned begin){
  unsigned pos = len;
  int min = arr[begin];
  for(++begin ; begin < len; ++begin) {
    if(arr[begin] < min) {
      min = arr[begin];
      pos = begin;
    }
  }
  return pos;
}


void sort_iteration(int *arr, unsigned len, unsigned pos){
  unsigned min_pos;
  min_pos = find_min(arr, len, pos);
  if (min_pos == len) {
    return ;
  }
  swap(&arr[pos], &arr[min_pos]);
}

int main() {
  unsigned len, elem;
  unsigned i;
  int *arr;

  if (1 != scanf("%u", &len)) {
    abort();
  }
  arr = (int *) malloc(len * sizeof(int));
  if (NULL == arr) {
    abort();
  }

  for (i = 0; i < len; ++i) {
    scanf("%d", &(arr[i]));
  }
  scanf("%u", &elem);

  sort_iteration(arr, len, elem);
  for (i = 0; i < len; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  free(arr);

  return 0;
}
