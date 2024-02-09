
//#include "me.h"


//int majority_element(const int *parr, int len);


int majority_element(const int *parr, int len) {
  int i, counter = 0;
  int elem = parr[0];
  for(i = 1; i < len; ++i) {
    if(0 == counter) {
      elem = parr[i];
      ++counter;
      continue;
    }
    if(parr[i] == elem) {
      ++counter; 
    } else {
      --counter;
    }
  }
  counter = 0;
  for( i = 0; i < len; ++i) {
    if(elem == parr[i])
        ++counter;
  } 
  if(counter > len/2 )
    return elem;
  
  return -1;
}

