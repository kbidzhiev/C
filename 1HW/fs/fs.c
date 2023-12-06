#include<stdio.h>
#include<stdlib.h>


int convert(unsigned n, int* res){
  int q, counter;
  int base = 2;
  for (counter = 0; n != 0; ){
    q = n%base;
    n = n/base;
    ++base;
    res[counter++] = q;
  }
  return --counter; //cause ++counter will be executed when n!=0 and then statement n!=0 will be checked
}

void print_converted(unsigned n){
  int res[32];
  int counter;
  counter = convert(n, res);

  for (; counter >=0; --counter){
      printf("%d.", res[counter]);
  }
  printf("\n");
}


int main(){
  int n, scaned;

  scaned = scanf("%d", &n);
  if(scaned != 1) abort();
  print_converted(n);

  return 0;
}
