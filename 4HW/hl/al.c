#include<stdio.h>
#include<stdlib.h>
#include"al.h"


void delete_list(struct node_t *top) {
  struct node_t *list = top, *tmp;
  while(list -> next != top) {
    list = list -> next; 
  }
  list -> next = NULL;
  list = top;
  while(NULL != list) {
    printf("deleting %d\n", list -> data);
    tmp = list -> next;
    list -> next = NULL;
    free(list);
    list = tmp;
  }
  
  top = NULL;
}

struct node_t *read_list(FILE *inp) {
  struct node_t *even_begin = NULL;
  struct node_t *odd_begin = NULL;
  struct node_t *even = even_begin, *odd = odd_begin;
  int n; 
  while(1 == fscanf(inp, "%d", &n)) {
    struct node_t *node = calloc(1, sizeof(struct node_t));
    node -> data = n;
    if(n % 2 == 0) {
      (NULL == even_begin) ? (even_begin = node) : (even -> next = node);
      even = node;
    } else {
      (NULL == odd_begin) ? (odd_begin = node) : (odd -> next = node);
      odd = node;
    }
  }
  if (NULL == even_begin)
    return odd_begin;
  even -> next = odd_begin;
  return even_begin;
}
