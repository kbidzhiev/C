#include<stdio.h>


void initialize(int *arr, unsigned size, int val){
  for(; size>0; --size){
    arr[size-1] = val;
  }
}

int main(){
  unsigned size;
  int x;
  int idx;
  scanf("%u%d", &size,&x);
  
  int arr[size];
  initialize(arr,size, x);
  for(idx = 0; idx<size+10; ++idx){
    printf("%d\t%d\n", idx, arr[idx]);
  }

  return 0;
}
