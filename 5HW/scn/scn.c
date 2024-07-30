#include<stdio.h>
#include<stdlib.h>


int main(void) {
  char c = 0;
  int acc = -10; //last EOL \n

  while(scanf("%c", &c) == 1) {
    acc += c; 
    printf("%c -> %d\n", c, c);
  }

  printf("%d\n", acc);
  return 0;
}
