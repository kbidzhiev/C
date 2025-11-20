#include<stdio.h>
#include<stdlib.h>

int foo(int x, int y) {
  if (x<0) return x*x*x;
  return x*x*x+17-2*x-y*y;
}

int main{
  printf("%d\n", foo())

  return 0;
}
