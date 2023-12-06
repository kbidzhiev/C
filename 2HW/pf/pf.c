#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>


#define TEST 0

unsigned long long mult_mod(unsigned long long n, unsigned long long k, unsigned long long m){
  unsigned long long acc = n%m;
  unsigned long long res = 0;
  // (n * k) % m == (n+n+n + .. n) %m
  // let k == 13 -> 13 = 8 + 4 + 1
  // [8420] == 1101
  while(k>0){
    if((k%2) == 1) {
      res = (res + acc) % m;
    }
    // n, 2n, , 4n, 8n
    acc = (acc*2)%m;
    k = k/2;
  }
  return res;
}

unsigned long long pow_mod(unsigned long long n, unsigned long long k, unsigned long long m){
  unsigned long long mult = n%m, multtmp = mult;
  unsigned long long prodtmp = 1, prod = 1;
  while(k>0){
    if((k%2) == 1) {
      prod = mult_mod(prod, mult, m);
      //prod = (prod * mult) % m;
    }
    mult = mult_mod(mult, mult, m);
    //mult = (mult * mult)%m;
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
  for (step = 0; step < 1000; ++step){
    r = rand()%100;
    while( r == 0 || r == 1 || !(1 == gcd(r,n))){
      r = rand()%100;
    }
    res = pow_mod(r, n-1, n);
    if (res != 1){
      //printf("res(%llu,%llu,%llu) = %llu\n", r, n-1, n, res);
      return 0;
    }
  }
  return 1;
}


unsigned long long fiblike_seq(unsigned k, unsigned n){
  unsigned long long f0 = 0, f1 = 1, f2, p = 0;
  int i;

  for(i = 0; ; i++){
    f2 = k * f1 + n * f0;
    if (f2 < f1 || f2 < f0){
      //printf("f0 = %llu\nf1 = %llu\nf2 = %llu\n", f0,f1,f2);
      break;
    }
    if (fermat_test(f2)){
      //printf("i = %d\n", i);
      p = f2 ;
    }
    f0 = f1;
    f1 = f2;
  }
  return p;
}


#if TEST
void test(){
  assert(99194853094755497 == fiblike_seq(1,1));
  assert(768614336404564651 == fiblike_seq(1,2));
  assert(1746860020068409 == fiblike_seq(2,1));
  assert(0 == fiblike_seq(4,4));


  assert( (1234*963)%17 == mult_mod(1234,963,17));

  assert(1 == fermat_test(433494437));
  assert(1 == fermat_test(2971215073));
  assert(1 == fermat_test(99194853094755497));

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
  assert(1 == fermat_test(5394826801)); // is not prime == 7 * 13 * 17 * 23 * 31 * 67 * 73

  printf("Test are DONE\n");
}
#endif


int main(){
  unsigned long long p;
  unsigned n,k;
  srand(time(NULL));

#if TEST
  test();
#endif
  if (2 != scanf("%u%u", &k, &n)) abort();

  p = fiblike_seq(k,n);
  printf("%llu\n", p);

  return 0;
}
