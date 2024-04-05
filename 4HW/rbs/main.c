#include "assert.h"
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


void append_to_list(struct node_t *list, int new_data) {
  struct node_t *l = list;
  struct node_t *new_node = calloc(1, sizeof(struct node_t));
  new_node ->data = new_data;
  if (NULL == list) {
    list = new_node;
    return;
  }
  while(NULL != l -> next)
    l = l -> next;
  l -> next = new_node;
}


struct node_t ** build_buckets(const int *arr, const int len) {
  int max = find_max(arr, len);
  int n_buckets = max/len;
  struct node_t **buckets = calloc(n_buckets, sizeof(struct node_t *));

  for (int i = 0; i < len; ++i) {
    append_to_list(buckets[arr[i]/max], arr[i]);
  }
  return buckets;
}

void free_buckets(struct node_t **arr) {
  struct node_t * list;
  for(int i = 0; i < arr -> data; ++i) {
    for(list = arr[i]; NULL != list; list = list -> next) {
      struct node_t *tmp = list -> next;
      list -> next = NULL;
      free(list);
      list = tmp;
    }
  }

  for(int i = 0; i < arr -> data; ++i)
    assert(NULL == arr[i]);

  free(arr);
}

void print_list(const struct node_t *list) {
  struct node_t *i;
  for (i = list; i != NULL; i = i -> next) {
    printf("%d ", i -> data);
  }
}

void print_buckets(const struct node_t **arr) {
  for(int i = 0; i < arr -> data; ++i) {
    print_list(arr[i]);
    printf("0 ");
  }
}

int main(void) {
  int len = 0, *arr;
  struct node_t **buckets;
  if (1 != scanf("%d", &len))
      abort();

  arr = calloc(len, sizeof(int));
  for(int i = 0; i < len; ++i) 
    if (1 != scanf("%d", arr + i))
      abort();
   
  buckets = build_buckets(arr, len);
  print_buckets(buckets);
  free_buckets(buckets);
  free(arr);
  return 0;
}
