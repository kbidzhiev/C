#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

long long iabs(long long x){
  return x>0 ? x: -x;
}

long long reminder(long long r, long long divisor){
  return (r>=0) ? r: r+iabs(divisor);
}

long long eu_mod(long long x, long long y){
  long long r;
  assert(y != 0);
  r = x%y;
  return reminder(r,y);
}

long long floordiv(long long x, long long y){
  x -= eu_mod(x,y);
  return x/y;
}

long long gcd(long long a, long long b, long long* u0, long long* v0){
  long long q, tmp;

  long long u2 = 1, v2 = 0; //uv2 == uv_{k-2}
  long long u = 0, v = 1;
  long long u1, v1; //uv1 == uv_{k-1}
  long long aini = a, bini = b;
  long long r;
  assert(b !=0 );
  for(; b != 0;){
    q = floordiv(a,b);
    tmp = a;  a = b; r = eu_mod(tmp,b);
    u1 = u; v1 = v;
    u = u2 - q*u; v = v2 - q*v;
    u2 = u1; v2 = v1;
    assert(b == u2 * aini + v2 * bini);
    b = r;
  }
  *u0 = u2;
  *v0 = v2;
  return a;
}

int main(){

  int scf;
  long long x, y;
  long long d, u, v;
  scf = scanf("%lld%lld", &x, &y);
  if (scf != 2) abort();
  if (y == 0) abort();

  d = gcd(x, y, &u, &v);
  printf("%lld %lld %lld\n", u, v, d);
  assert(d == x * u + y * v);

  return 0;
}
