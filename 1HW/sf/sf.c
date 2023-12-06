#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int fib(int n){
  int fnm1, fnm2;
  fnm1 = 1;
  fnm2 = 0;
  if (n == 0) return fnm2;
  for(; n > 1; --n){
    int tmp = fnm1;
    fnm1 = (fnm1 + fnm2);
    fnm2 = tmp;
  }
  return fnm1;
}

void tofib(int n){
  int r;
  int i = 2;
  int base = 1;
  int nini = n;
  int x = 0;

  //printf("i\tbase\tr\n");
  while(n/fib(i) > 0){
    ++i;
  }
  --i;

  while(i != 1){
    base = fib(i);
    r = n%base;

    if (n / base == 1){
      x += base;
      printf("1");
    } else {
      printf("0");
    }
    n = r;
    assert( n + x == nini);
    //printf("%d\t%d\t%d\n",i, base, r);
    i = i-1;
  }
  printf("\n");
  //printf("\n%d\n", x);

}


int main(){
  int x;
  if(scanf("%d",&x) != 1){
    abort();
  }

  tofib(x);
  //printf("%d\n", fib(x) );


  return 0;
}
