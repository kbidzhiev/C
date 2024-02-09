
#include "me.h"


int majority_element(const int *parr, int len);


int majority_element(const int *parr, int len) {
  int i,elem, counter = 0;
  for(i = 0; i < len; ++i) {
    if(0 == counter) {
      elem = parr[i];
      ++counter;
      continue;
    }
    parr[i] == elem ? ++counter : --counter;
  }
  counter = 0;
  for( i = 0; i < len; ++i) 
    if(elem == parr[i])
        ++counter;
   
  return counter > (len/2) ? elem : -1;
}

