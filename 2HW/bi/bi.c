#include<stdio.h>
#include<stdlib.h>


unsigned char invert_bit(unsigned char byte, unsigned char i){
  return byte ^ (1u << i);
}

unsigned char read_bit(unsigned char byte, unsigned char i){
  return (byte >> i) & 1u;
}

int main(){
  unsigned n;
  unsigned i, idx, q, r;
  unsigned char *p;


  if ( 1 != scanf("%u", &n)) abort();// number if elements

  p = calloc(n, sizeof(unsigned char));
  if (NULL == p) abort();

  for (i=0; i<n; ++i){
    if(1 != scanf("%hhu", p)) abort(); //reading elements
    ++p;
  }
  p = p-n; //returning to the initial address
  if(1 != scanf("%u", &idx)) abort(); //reading index

  q = idx/8; //each *p has 1 byte = 8 bites = sizeof(char)
  r = idx%8; // index in q-th byte
  
  //printf("byte %u in %u is %u\n", idx, p[q], read_bit(p[q], r));
  
  if (idx < n * 8) p[q] = invert_bit(p[q], r);// bites chunk

  for (i = 0; i<n; ++i){
    printf("%u ", p[i]);
  }
  printf("\n");


  free(p);

  return 0;
}
