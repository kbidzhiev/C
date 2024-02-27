#include <stdlib.h>
#include <stdio.h>


int find_max(int *p, int size) {
  int i, res = p[0];
  for(i = 0; i < size; ++i) {
    res = res > p[i] ? res : p[i];
  }
  return res;
}

int main(void) {
  int counter = 0, size, *p;

  if(1 != scanf("%d", &size)) 
    abort();
  p = calloc(size, sizeof(int)); 
  if (NULL == p)
    abort();

  for (int i = 0; i < size; ++i) {
    counter += scanf("%d", p + i); 
  }
  if(counter != size) 
    abort();


  for(int i = 0; i < size; ++i) { 
    printf("%d ", p[i]);
  }
  printf("\n");
  return 0;
}
