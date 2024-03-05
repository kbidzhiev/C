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
  if (1 != scanf("%d", &size))
    abort();
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

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
void inclusive_scan(struct arr_t *arr) {
  int tmp0;
  int tmp = arr -> p[0];
  arr -> p[0] = 0;
  for (int i = 1; i < arr -> size; ++i) {
    tmp0 = arr -> p[i];
    arr -> p[i] = arr -> p[i-1] + tmp;
    swap(&tmp, &tmp0);
  }
}

int n_digit(int num, int base, int digit) {
  for (int i = 0; i < digit; ++i) {
    num /= base; 
  }
  return num % base;
}

struct arr_t rs(struct arr_t *arr, int digit) {
  struct arr_t buckets = arr_calloc(base);
  struct arr_t res = arr_calloc(arr -> size);
  int num = 0;
  int future_position;

  //digit = pow_base(base, digit);
  for (int i = 0; i < arr -> size; ++i) {
    num = n_digit(arr -> p[i], base, digit);
    if (num > 9 || num < 0) {
      printf("remainder cannot be %d\n", num);
      abort();
    }
    buckets.p[num] += 1;
  }
  inclusive_scan(&buckets);

  for(int i = 0; i < arr -> size; ++i) {
    num = n_digit(arr -> p[i], base, digit);
    future_position = buckets.p[num]; 
    res.p[future_position] = arr -> p[i];
    ++buckets.p[num];
  }
 
  arr_free(arr);
  arr_free(&buckets);
  return res;
}

int main(void) {
  int digit;
  struct arr_t arr = read_array();
  {
    assert(10 == pow_base(10, 0)); 
    assert(100 == pow_base(10, 1)); 
    assert(1000 == pow_base(10, 2)); 
    assert(2 == pow_base(2, 0)); 
    assert(4 == pow_base(2, 1)); 

    assert(3 == n_digit(123, 10, 0));
    assert(2 == n_digit(123, 10, 1));
    assert(1 == n_digit(123, 10, 2));
  }

  
  if (1 != scanf("%d", &digit))
    abort();
  
  arr = rs(&arr, digit);

  arr_printf(arr);
  arr_free(&arr);
  return 0;
}
