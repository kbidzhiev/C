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

int find_max(const int * arr, const int len) {
  int res;
  if (NULL == arr) {
    abort();
  }
  res = arr[0];
  for(int i = 1; i < len; ++i) {
    //printf("choosing between %d and %d\n", res, arr[i]);
    res = arr[i] > res ? arr[i] : res;
    //printf("res = %d\n", res);
  }
  return res;
}

void append_to_list(struct node_t **plist, const int new_data) {
  struct node_t *new_node = calloc(1, sizeof(struct node_t));
  new_node -> data = new_data;
  
  while((NULL != *plist) && ((*plist) -> data < new_data))
    plist = &((*plist) -> next);

  if(NULL == *plist) {
    new_node -> next = NULL;
    *plist = new_node;
  } else {
    new_node -> next = *plist;
    *plist = new_node;
  }
}

struct buckets_t *build_buckets(const int *nums, const int len) {
  int bucket_id; 
  int max = find_max(nums, len);
  int batch_size = max/len;
  struct buckets_t *buckets = calloc(1, sizeof(struct buckets_t));
  if(NULL == buckets)
    abort();
  buckets -> size = len;
  buckets -> arr = calloc(buckets -> size, sizeof(struct node_t *));

  if(NULL == buckets -> arr)
    abort();

  for (int i = 0; i < len; ++i) {
    //printf("parsing loop %d : %d\n", i, nums[i]);
    bucket_id = nums[i]/batch_size;
    //printf("parsing %d to bucket %d\n", nums[i], bucket_id);
    if(bucket_id >= len) {
      bucket_id = len - 1;
    }
    append_to_list((buckets -> arr) + bucket_id, nums[i]);
  }
  return buckets;
}

void free_buckets(struct buckets_t *buckets) {
  struct node_t * list;
  for(int i = 0; i < buckets -> size; ++i) {
    for(list = buckets -> arr[i]; NULL != list; ) {
      struct node_t *tmp = list -> next;
      list -> next = NULL;
      free(list);
      list = tmp;
    }
    buckets -> arr[i] = NULL;
  }

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
  int len = 0, *arr , i;
  struct buckets_t *buckets;
  if (1 != scanf("%d", &len))
      abort();
  if(0 == len)
    abort();
  
  arr = calloc(len, sizeof(int));
  if(NULL == arr)
    abort();

  for(i = 0; i < len; ++i) {
    if (1 != scanf("%d", &arr[i])) {
      abort();
    }
  }
  
  //printf("array:\n");
  //for(i = 0; i < len; ++i) {
  //  printf("arr[%d]: %d \n", i, arr[i]);
  //}


  buckets = build_buckets(arr, len);
  print_buckets(buckets);
  printf("\n");
  free_buckets(buckets);
  free(arr);
  return 0;
}
