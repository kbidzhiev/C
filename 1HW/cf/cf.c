#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

int iabs(int x){
  return x>0 ? x: -x;
}

int eu_mod(int x, int y){
  int r;
  assert(y != 0);
  r = x%y;
  if (r<0) r+= iabs(y);
  return r;
}

void cf(int x, int y){
  int q, tmp;
  
  assert(y !=0 );
  for(; y != 0;){
    q = x/y;
    tmp = x;
    x = y;
    y = eu_mod(tmp,y);
    printf("%d ",q);
  }
}

int main(){

  int x;
  int y;
  int scf;
  scf = scanf("%d%d", &x, &y);

  //printf("%d, %d", x,y);
  if (scf != 2) abort();
  if (y == 0) abort();
  cf(x,y);

  return 0;
}
