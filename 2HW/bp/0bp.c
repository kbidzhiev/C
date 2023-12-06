#include<stdio.h>
#include<stdlib.h>


int main(){
  int n, i; // int is 4 bytes
  unsigned char *p;
  unsigned char pi[4];

  if(1 != scanf("%d", &n)) abort();
  printf("\n");
  p = (unsigned char*)&n;
  for (i = 0; i<4; ++i){
    pi[i] = *p;
    printf("0x%.8X \t %p\n", pi[i], p);
    p++;
  }

  //for (i = 0; i<4; ++i){
  //  printf("%d => 0x%.2X\n", i, pi[i]);
  //}
  printf("\n%lu", sizeof(char));

  return 0;
}
