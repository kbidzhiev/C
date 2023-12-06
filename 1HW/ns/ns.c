#include<stdio.h>
#include<stdlib.h>


int convert(unsigned n, unsigned base, int* res){
  int q, counter;
  for (counter = 0; n != 0; ){
    q = n%base;
    n = n/base;
    res[counter++] = q;
  }
  return --counter; //cause ++counter will be executed when n!=0 and then statement n!=0 will be checked
}

void print_converted(unsigned n, unsigned base){
  int res[32];
  int counter;
  counter = convert(n, base, res);

  for (; counter >=0; --counter){
      printf("%d", res[counter]);
  }
  printf("\n");
}


int main(){
  int n, base, scaned;

  scaned = scanf("%d%d", &n, &base);
  if(scaned != 2) abort();
  print_converted(n, base);

  return 0;
}
