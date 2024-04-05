#include "stdio.h"
#include "stdlib.h"

struct node_t {
  struct node_t *next;
  int data;
};

int find_max(const int * arr, int len) {
  int res;
  if (NULL == arr) {
    abort();
  }
  res = arr[0];
  for(int i = 1; i < len; ++i)
    res = arr[i] > res ? arr[i] : res;
  return res;
}

struct node_t * build_buckets(const int *arr, const int len) {
  int max = find_max(arr, len);
  int n_buckets = max/len;
  struct node_t * buckets = calloc(n_buckets, sizeof(struct node_t));

  for (int i = 0; i < len; ++i) {
  
  }
  return buckets;
}

void print_list(const struct node_t *list) {
  struct node_t *i;
  for (i = list; i != NULL; i = i -> next) {
    printf("%d ", i -> data);
  }
}

void

int main(void) {
  int len = 0, *arr;
  if (1 != scanf("%d", &len))
      abort();

  arr = calloc(len, sizeof(int));
  for(int i = 0; i < len; ++i) 
    if (1 != scanf("%d", arr + i))
      abort();
    

  free(arr);
  return 0;
}
