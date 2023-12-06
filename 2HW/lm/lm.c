#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#if 0
unsigned long long  iabs(unsigned long long  a){
  return (a<0)? -a: a;
}
#endif
unsigned long long  eu_mod(unsigned long long  a, unsigned long long  b){
  unsigned long long  r;
  assert(b != 0);
  r = a%b;
  //if (r<0) r+=iabs(b);
  return r;
}

unsigned long long  gcd(unsigned long long  a, unsigned long long  b){
  unsigned long long  tmp;
  while(b != 0){
    tmp = a;
    a = b;
    b = eu_mod(tmp,b);
  }
  return a;
}

unsigned long long  lcm(unsigned long long  a, unsigned long long  b){
  unsigned long long  d = gcd(a,b);
  assert(d != 0);
  return (a*b)/d;
}

unsigned long long lcm_range(unsigned long long N){
  unsigned long long acc = 1;
  for (; N>0; --N){
    acc = lcm(acc, N);
  }
  return acc;
}

#if 0
void tests(){
  assert(2520 == lcm_range(10));
  assert(2 == lcm_range(2));
  assert(6 == lcm_range(3));

  assert(232792560 == lcm_range(22));
  assert(232792560 == lcm_range(21));

}
#endif

int  main(){
  unsigned long long  N, res;
  //tests();


  if (1 != scanf("%llu", &N)) abort();
  res = lcm_range(N);

  printf("%llu\n", res);


}
