#include <stdlib.h>
#include <stdio.h>

struct arr_t {
  int size;
  int *p;
};

struct arr_t arr_calloc(int size) {
  struct arr_t arr;
  arr.size = size;
  arr.p = calloc(arr.size, sizeof(int)); 
  if (NULL == arr.p)
    abort();
  return arr;
}

void arr_free(struct arr_t *arr) {
  arr -> size = 0;
  free(arr -> p);
}

int find_max(const struct arr_t *arr) {
  int i, res = arr -> p[0];
  for(i = 0; i < arr -> size; ++i) {
    res = res > (arr -> p[i]) ? res : (arr -> p[i]);
  }
  return res;
}

int main(void) {
  int counter = 0;
  int max;
  struct arr_t arr1, arr2;
  if(1 != scanf("%d", &(arr1.size))) 
    abort();

  arr1 = arr_calloc(arr1.size);

  for (int i = 0; i < arr1.size; ++i) {
    counter += scanf("%d", arr1.p + i); 
  }
  if(counter != arr1.size) 
    abort();
  max = find_max(&arr1);  

  arr2 = arr_calloc(max + 1);

  for(int i = 0; i < arr1.size; ++i) {
    counter = arr1.p[i];
    arr2.p[counter] += 1;
  }


  for(int i = 0; i < arr2.size; ++i) { 
    printf("%d ", arr2.p[i]);
  }
  printf("\n");
  
  arr_free(&arr1);
  arr_free(&arr2);
  return 0;
}
