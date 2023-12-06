#include<stdio.h>
#include<stdlib.h>
#include<assert.h>



void extract_digits(int N, char digits[], int length){
  int r, size, base = 10;
  assert(length !=0 );
  for(size = 0; size < length; ++size){
    r = N%base;
    digits[size] = r;
    N /= base;
  }
}

int digits_in(int n){
  int size, base = 10;
  assert(n>=0);

  for(size = 0; ; ++size){
    if (n == 0) return size;
    n /= base;
  }
  return size;
}

int powint(int base, int exp){
  int res = 1;
  for (; exp > 0; --exp){
    res *= base;
  }
  return res;
}

int is_prime(int n){
  int i;
  if (n == 2) return 1;
  if (n<2 || ((n%2) == 0)) return 0;

  for(i = 3; i*i <= n; i += 2){
    if((n%i) == 0) return 0;
  }
  return 1;
}

void circulate(char digits[], int size){
  int i;
  char last = digits[0];
  for (i=0; i<size-1; ++i) digits[i] = digits[i+1];
  digits[size-1] = last;
}

int digits_to_number(char digits[], int d){
  int i, n = 0;
  for (i = 0; i < d; ++i){
    n += powint(10, i) * digits[i];
  }
  return n;
}

int circulate_is_prime(int n){
  int i;
  int d = digits_in(n);
  char *digits = calloc(d,sizeof(char));
  extract_digits(n, digits, d);

  for(i=0; i<d; ++i){
    if( !is_prime(n)) return 0;
    circulate(digits, d);
    n = digits_to_number(digits, d);
  }

  free(digits);
  return 1;
}


int find_closest_prime(int N){
  int i;

  for(i=0; ; ++i){
    if((N+i > 0) && circulate_is_prime(N+i)){
      return N+i;
    }
    if((N-i-1 > 0) && circulate_is_prime(N-i-1)){
      return N-i-1;
    }
  }
  abort();
  return 0;
}

void tests(){
  int d = 3;
  char* pd = calloc(d, sizeof(char));

  assert(97 == find_closest_prime(100));
  assert(199 == find_closest_prime(200));

  extract_digits(157, pd, d);
  assert(1 == pd[2]);
  assert(5 == pd[1]);
  assert(7 == pd[0]);

  circulate(pd, d);
  assert(7 == pd[2]);
  assert(1 == pd[1]);
  assert(5 == pd[0]);

  assert(715 == digits_to_number(pd, d));
  circulate(pd, d);
  assert(571 == digits_to_number(pd, d));
  circulate(pd, d);
  assert(157 == digits_to_number(pd, d));

  free(pd);

  assert(1 == circulate_is_prime(199));
  assert(1 == circulate_is_prime(97));
  assert(1 == circulate_is_prime(197));
  assert(0 == circulate_is_prime(157));


  assert(100 == powint(10,2));
  assert(512 == powint(2,9));
  assert(-1 == powint(-1, 5));
  assert(1 == powint(-1, 8));

  assert(3 == digits_in(100));
  assert(5 == digits_in(12345));
  assert(0 == digits_in(0));

  assert(1 == is_prime(2));
  assert(1 == is_prime(3));
  assert(0 == is_prime(4));
  assert(1 == is_prime(17));
  assert(1 == is_prime(199));

  printf("tests are ok\n");
}

int main(){
  int N, p;
  //tests();

  if (1 != scanf("%d", &N)) abort();
  p = find_closest_prime(N);

  printf("%d\n", p);

}
