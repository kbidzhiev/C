#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "me.h"

//srand(time(NULL));

int majority_element(const int *parr, int len);


struct Array {
  unsigned size;
  int *p;
};

struct Array Acalloc(unsigned len) {
  struct Array a = {len, NULL};
  a.p = calloc(len, sizeof(int));
  if (NULL == a.p) {
    printf("Acalloc calloc of %u failed\n", len);
    abort();
  }
  return a;
}

void Afree(struct Array *a) {
  free(a -> p);
  a -> size = 0;
  a -> p = NULL;
}

struct Array randArray(unsigned  i) {
  unsigned j;
  struct Array a = Acalloc(i);
  for(j = 0; j < a.size; ++j)
    a.p[j] = (rand() % 10) + 1;
  return a;
}
void Aprintf(const struct Array a) {
  for(unsigned i = 0; i < a.size; ++i)
    printf("%d ", a.p[i]);
  printf("\n");
}


void test_ex1() {
  int p[5] = {2, 3, 1, 2, 2};
  int m = majority_element(p, 5);
  assert( 2 == m);
  printf("Example 1\n");
}

void test_ex2() {
  int p[6] = {9, 1, 1, 9, 2, 2};
  int m = majority_element(p, 6);
  assert( -1 == m);
  printf("Example 2\n");
}

void test_ex3() {
  int p[9] = {3, 4, 3, 2, 4, 4, 2, 4, 4}; 
  int m = majority_element(p, 9);
  assert( 4 == m);
  printf("Example 3\n");
}

void test_ex4() {
  int p[8] = {3, 3, 4, 2, 4, 4, 2, 4}; 
  int m = majority_element(p, 8);
  assert( -1 == m);
  printf("Example 4\n");
}
void run_tests(void) {
  test_ex1();
  test_ex2();
  test_ex3();
  test_ex4();
  printf("Tests compled\n");
}

int main(void) {
  run_tests();
  
  return 0;
}
