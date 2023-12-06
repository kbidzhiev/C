#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef long long int long_t;

long_t iabs(long_t x){
  if (x<0) x = -x;
  return x;
}

long_t gcd(long_t x, long_t y) {
  while(x != 0){
    if( iabs(y) > iabs(x)){
      long_t tmp = x;
      x = y;
      y = tmp;
    }
    assert(iabs(x) > iabs(y));
    assert(y != 0);
    //printf("%lld %lld\n", x, y);
    x = x % y;
  }
  return y;
}


int main() {
  long_t x = 0, y = 0, g;
  int res;
  
  res = scanf("%lld %lld", &x, &y); //%llu - long long unsigned
  assert(res == 2);
  g = gcd(x, y);
  printf("%lld\n", iabs(g));
  return 0;
}
