#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


int is_prime(unsigned n){
  unsigned j;
  if (n<2) return 0;
  for(j = 2; j*j <= n; ++j){
    if(n%j == 0) return 0;
  }
  return 1;
}


int main(){
  int n, i;
  int counter = 0;
  if (scanf("%u",&n) != 1) abort();


  for (i =2; counter != n; ++i){
    printf("i = %d  ", i);
    if (is_prime(i)){
      printf("counter + 1 = %d\n", ++counter);
    }else {
      printf("counter = %d\n", counter);
    }

  }
  printf("%d\n", --i);


  return 0;
}
