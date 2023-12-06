#include<stdlib.h>
#include<stdio.h>



int pow_mod(int n, int k, int m){
  int mult = n%m;
  int prod = 1;
  while(k>0){
    if (k%2 == 1){
      prod = (prod * mult)%m;
    }
    mult = (mult * mult)%m;
    k /= 2;
  }
  return prod;
}

int spow_mod(int n, int k, int m){
  int mult = n%m;
  int prod = mult;
  while(k>0){
    if (k%2 == 1){
      prod = pow_mod(prod,mult,m);
    }
    mult = pow_mod(mult, mult, m);
    k /= 2;
  }
  return prod;
}


int res(int a, int b, int m){
  return spow_mod(a, b, m);
}


int main(){
  int a, b, m, s;

  s = scanf("%d%d%d", &a, &b, &m);
  if (s != 3) abort();

  printf("%d", res(a,b,m));

  return 0;
}
