#include<stdio.h>
#include<stdlib.h>


unsigned last_bit(int n){
  for(unsigned i = 0; i<32; ++i){
    if ( ((n << i)&0x80000000) == 0x80000000){
      return 31-i;
    }
  }
  return 0;
}


unsigned first_bit(int n){
  for(unsigned i = 0; i<32; ++i){
    if ( ((n >> i)&1u) == 1u){
      return i;
    }
  }
  return 0;
}

int main(){
  int n;
  unsigned i,f;

  if(1 != scanf("%d", &n)) abort();
  i = first_bit(n);
  f = last_bit(n);
  if (f == 0 && i == 0) {
    printf("-1\n");
    return 0;
  }
  printf("%u %u\n", f, i);


  return 0;
}
