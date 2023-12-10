#include"si.h"

void swap(int *pa, int *pb){
  int tmp;
  tmp = *pa;
  *pa = *pb;
  *pb = tmp;
}

int moveright(int *arr, int key, int last) {
  --last;
  while ((last >= 0) && (key < arr[last])) {
    arr[last+1] = arr[last];
    --last;
  }
  return ++last;
}

