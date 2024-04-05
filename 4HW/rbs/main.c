#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

struct node_t {
  struct node_t *next;
  int data;
};

struct buckets_t {
  struct node_t **arr;
  int size;
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


struct buckets_t *build_buckets(const int *nums, const int len) {
  int max = find_max(nums, len);
  struct buckets_t *buckets = calloc(1, sizeof(struct buckets_t));
  buckets -> size = max/len;
  buckets -> arr = calloc(buckets -> size, sizeof(struct node_t *));

  for (int i = 0; i < len; ++i) {
    int bucket = nums[i]/max;
    append_to_list(buckets -> arr[bucket], nums[i]);
  }
  return buckets;
}

void free_buckets(struct buckets_t *buckets) {
  struct node_t * list;
  for(int i = 0; i < buckets -> size; ++i) {
    for(list = buckets -> arr[i]; NULL != list; list = list -> next) {
      struct node_t *tmp = list -> next;
      list -> next = NULL;
      free(list);
      list = tmp;
    }
  }

  for(int i = 0; i < buckets -> size; ++i)
    assert(NULL == buckets -> arr[i]);

  free(buckets -> arr);
  buckets -> arr = NULL;
  buckets -> size = 0;
  free(buckets);
  buckets = NULL;
}


void print_list(const struct node_t *list) {
  const struct node_t *i;
  for (i = list; i != NULL; i = i -> next) {
    printf("%d ", i -> data);
  }
}

void print_buckets(const struct buckets_t *buckets) {
  for(int i = 0; i < buckets -> size; ++i) {
    print_list(buckets -> arr[i]);
    printf("0 ");
  }
}

int main(void) {
  int len = 0, *arr;
  struct buckets_t *buckets;
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
