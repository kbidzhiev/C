#include <stdio.h>
#include <stdlib.h>

#define MAIN 1

#if MAIN
typedef int (*get_hash_t)(const char *s);

int simple_hash(const char *s) {
  int hash = 0;
  while(*s) {
    hash += *s++;
  }
  return hash;
}

#endif

struct list_t {
  struct list_t *next;
  int data;
};

struct list_t *add_node(struct list_t *list, const int data) {
  struct list_t *node = calloc(1, sizeof(struct list_t));
  node -> next = list;
  node -> data = data;
  return node; 
}

int find(const struct list_t *list, const int data) {
  for(; list != NULL; list = list -> next) {
    if(list -> data == data)
      return 1;
  }
  return 0;
}
#if MAIN
void print_list(const struct list_t *list);
#endif

int ncollisions(char **strs, int n, get_hash_t f) {
  int cols = 0;
  struct list_t *list = NULL;
  for(int i = 0; i < n; ++i) {
    int hash = f(strs[i]);
    if (find(list, hash)){
      ++cols;
    } else {
      list = add_node(list, hash);
    }
  }
  return cols;
}

#if MAIN
void print_list(const struct list_t *list) {
  const struct list_t *current = list;
  for(; current != NULL; current = current -> next) {
    printf("%d ", current -> data);
  }
  printf("\n");

    
}

int main(void) {
  
  char *strings[3];
  strings[0] = "moo";
  strings[1] = "2oo";
  strings[2] = "moo";
  //strings[3] = "moo";
  struct list_t *list = NULL;
  list = add_node(list, 2);
  list = add_node(list, 7);
  list = add_node(list, 9);
  if(!find(list, 7))
    abort();
  if(find(list, 3))
    abort();
  print_list(list);

  printf("%d ", ncollisions(strings, 3, simple_hash));

}
#endif


