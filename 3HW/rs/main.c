#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int base = 10;

struct arr_t {
  int size;
  int *p;
};

struct arr_t arr_calloc(int size) {
  struct arr_t arr;
  arr.size = size;
  arr.p = calloc(size, sizeof(int));
  if (NULL == arr.p)
    abort();
  return arr;
}
void arr_free(struct arr_t *arr) {
  arr -> size = 0;
  free(arr -> p);
}

int arr_scanf(struct arr_t *arr) {
  int counter = 0;
  for(int i = 0; i < arr -> size; ++i) {
    counter += scanf("%d", (arr -> p) + i);
  }
  if (counter != (arr -> size))
    abort();
  return counter;
}

int arr_printf(const struct arr_t arr) {
  int counter = 0; 
  for(int i = 0; i < arr.size; ++i) {
    printf("%d ", arr.p[i]);
  }
  printf("\n");
  return counter;
}
struct arr_t read_array() {
  int size;
  struct arr_t arr;
  scanf("%d", &size);
  arr = arr_calloc(size);
  arr_scanf(&arr);
  return arr;
}

int pow_base(const int base, const int pow) {
  int res = 1;
  for (int i = 0; i <= pow; ++i)
    res *= base;
  return res;
}
void inclusive_scan(struct arr_t *arr) {
  for (int i = 1; i < arr -> size; ++i)
    arr -> p[i] += arr -> p[i-1];
}
void rs(struct arr_t *arr, int digit) {
  int num = 0;
  digit = pow_base(base, digit);
  struct arr_t buckets = arr_calloc(base);
  for (int i = 0; i < arr -> size; ++i) {
    num = (arr -> p[i]) % digit;
    buckets.p[num] += 1;
  }
  arr_printf(buckets);
  inclusive_scan(&buckets);
  arr_printf(buckets);
  arr_free(&buckets);
}

int main(void) {
  int digit;
  struct arr_t arr = read_array();
  arr_printf(arr);
  {
    assert(10 == pow_base(10, 0)); 
    assert(100 == pow_base(10, 1)); 
    assert(1000 == pow_base(10, 2)); 
    assert(2 == pow_base(2, 0)); 
    assert(4 == pow_base(2, 1)); 
  }

  
  scanf("%d", &digit);
  
  arr_printf(arr);
  rs(&arr, digit);

  arr_free(&arr);
  return 0;
}
