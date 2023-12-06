#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>


#define TEST 1

unsigned long long pow_mod(unsigned long long n, unsigned long long k, unsigned long long m){
  unsigned long long mult = n%m;
  unsigned long long prod = 1;
  while(k>0){
    if((k%2) == 1) {
      prod = (prod * mult) % m;
    }
    mult = (mult * mult)%m;
    k = k/2;
  }
  return prod;
}

unsigned long long gcd(unsigned long long x, unsigned long long y){
  unsigned long long tmp;
  assert(y != 0);
  while (y>0){
    tmp = x;
    x = y;
    y = tmp%y;
  }

  return x;
}


int fermat_test(unsigned long long n){
  unsigned long long r;
  unsigned long long res;
  int step = 0;
  for (step = 0; step < 100; ++step){
    r = rand()%100;
    while( r == 0 || !(1 == gcd(r,n))){
      r = rand()%100;
    }
    res = pow_mod(r, n-1, n);
    if (res != 1){
      printf("res(%llu,%llu,%llu) = %llu\n", r, n-1, n, res);
      return 0;
    }
  }
  return 1;
}

#if TEST
void test(){
  assert(1 == fermat_test(413958827741));


  assert(81 == pow_mod(24,220,221));
  assert(1 == pow_mod(38,220,221));

  assert(1 == fermat_test(11));
  assert(1 == fermat_test(13));

  assert(0 == fermat_test(100000001));
  assert(1 == fermat_test(100000007));
  assert(0 == fermat_test(413958827669));
  // so called Carmichael number
  assert(1 == fermat_test(561));
  //assert(1 == fermat_test(5394826801)); // is not prime == 7 * 13 * 17 * 23 * 31 * 67 * 73


}
#endif


int main(){
  unsigned long long n;
  int ft;
  srand(time(NULL));

#if TEST
  test();
#endif

  if (1 != scanf("%llu", &n)) abort();

  ft = fermat_test(n);

  printf("%d\n", ft);

  return 0;
}
