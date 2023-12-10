#include<stdio.h>
#include<stdlib.h>

int main() {
  int i, len, min = 0, max = 0;
  int arr;

  if( 1 != scanf("%d", &len))
    abort();

  //arr = (int*) malloc(len * sizeof(int));
  for(i = 0; i< len; ++i) {
    scanf("%d", &arr);
    if (i==0){
      min = arr;
      max = arr;
    }
    if(arr > max)
      max = arr;
    if(arr < min)
      min = arr;
  }

  printf("%d %d\n", min, max);


  return 0;
}
