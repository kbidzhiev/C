#include<stdio.h>
#include<stdlib.h>
#include"al.h"


void delete_list(struct node_t *top) {
  struct node_t *list = top;
  while(NULL != list) {
    struct node_t *tmp = list -> next;
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
      if(NULL == even_begin) {
        even_begin = node;
        even = node;
      } else {
        even -> next = node; 
        even = node;
      }
      
    } else {
      if(NULL == odd_begin) {
        odd_begin = node; 
        odd = node;
      } else {
        odd -> next = node; 
        odd = node;
      } 
    }
  }
  if (NULL == even_begin) {
    return odd_begin;
  }
  even -> next = odd_begin;
  return even_begin;
}
