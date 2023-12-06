#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

int iabs(int x){
  return x>0 ? x: -x;
}

int reminder(int r, int divisor){
  return (r>=0) ? r: r+iabs(divisor);
}

int eu_mod(int x, int y){
  int r;
  assert(y != 0);
  r = x%y;
  return reminder(r,y);
}

int floordiv(int x, int y){
  x -= eu_mod(x,y);
  return x/y;
}

int gcd(int a, int b, int* u0, int* v0){
  int q, tmp;

  int u2 = 1, v2 = 0; //uv2 == uv_{k-2}
  int u = 0, v = 1;
  int u1, v1; //uv1 == uv_{k-1}
  int aini = a, bini = b;
  int r;
  assert(b !=0 );
  for(; b != 0;){
    q = floordiv(a,b);
    tmp = a;  a = b; r = eu_mod(tmp,b);
    assert(tmp = q*b + r);
    u1 = u; v1 = v;
    u = u2 - q*u; v = v2 - q*v;
    u2 = u1; v2 = v1;
    assert(b == u2 * aini + v2 * bini);
    b = r;
  }
  if (a<0){
    u2 *= -1;
    v2 *= -1;
  }
  *u0 = u2;
  *v0 = v2;
  //assert(a>0);
  return iabs(a);
}

int mytests(){
  assert(eu_mod(7, 3) == 1);
  assert(eu_mod(7,-3) == 1);
  assert(eu_mod(-7,3) == 2);
  assert(eu_mod(-7,-3) == 2);

  assert(floordiv(7,3) == 2);
  assert(floordiv(7,-3) == -2);
  assert(floordiv(-7,3) == -3);
  assert(floordiv(-7,-3) == 3);


  return 0;
}


int main(){

  int scf;
  int a, b, c;
  int d, u, v;
  scf = scanf("%d%d%d", &a, &b, &c);
  if (scf != 3) abort();
  if (b == 0) abort();

  {
    mytests();
  }

  d = gcd(a, b, &u, &v);
  if ( eu_mod(c,d) != 0){
    printf("NONE\n");
    return 0;
  }
  assert(d == a * u + b * v);
  u *= c;
  v *= c;
  printf("%d %d\n", u, v);
  assert(c == a * u + b * v);

  return 0;
}
