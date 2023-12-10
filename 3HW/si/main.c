#include<stdio.h>
#include<stdlib.h>
#include"si.h"


void inssort(int *arr, int len) {
  int i;
  for (i = 0; i < len; ++i) {
    int key, pos;
    key = arr[i];
    pos = moveright(arr, key, i);
    arr[pos] = key;
  }
}

int main() {
  //int arr[6] = {1,2,4,5,3,2};
  //int key = 3, last = 4;
  //int arr[6] = {5,2,4,1,3,2};
  //int key = 5, last = 0;
  int size = 10;
  int arr[10] = {1, 1, 3, 3, 4, 1, 9, 4, 9, 4};
  int key = 1, last = 5;
  key = moveright(arr, key, last);
  //inssort(arr, 6);

  for (int i = 0; i < size;++i){
    printf("%d ", arr[i]);
  }
  printf("\npos = %d\n", key);

  return 0;
}
