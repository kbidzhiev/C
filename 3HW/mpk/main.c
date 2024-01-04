#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"tests.h"

void pol_mult_quadric(int *pol1, unsigned size1, int *pol2, unsigned size2, int *pol3, unsigned size3) {
  unsigned i, j, k;
  for(k = 0; k < size3; ++k)
    pol3[k] = 0;

  for(j = 0; j < size2; ++j) {
    k = j;
    for(i = 0; i < size1; ++i) {
      pol3[k] += pol2[j] * pol1[i];
      ++k;
    }
  }
}

void pol_split(int *A, unsigned lenA, int *A1, int *A2) {
  unsigned degA = lenA - 1;
  unsigned degA2 = degA/2; //degA-degdiv;
  unsigned shiftA1 = degA % 2;
  for(unsigned i = 0; i < lenA; ++i) {
    if(i <= degA2) {
      A2[i] = A[i];
    } else {
      //shiftA1 is requred to have degA1 == degA2
      //simply it makes constant term of the A1 polynomial == 0
      //Examples of A = A1*x + A2:
      // x2 + 2x + 1 == (x + 0)*x + (2x+1)
      // x3 + 3x2 + 4x + 7 == (x + 3x)*x2 + (4x + 7)
      A1[i-degA2-shiftA1] = A[i];
    }
  }
  if (shiftA1 == 0) {
    A1[0] = 0;
  }
}

//void pol_mult_karatsuba(int *plo1, int *pol2, unsigned size1, int *pol3, unsigned size){
  //unsigned deg = (size1 - 1)/2;
//}

unsigned canonic_form(int *pol, unsigned size) {
  --size; //size is length of pol
  for (; size >= 0; --size) {
    if (pol[size] != 0)
      // pol[size] is first nonzero elem,
      // i.e. size of arr is size+1
      return ++size;
  }
  return 0;
}

int main() {
  int size1, size2, size3;
  int *pol1, *pol2, *pol3;
  int i;

  test_karatsuba();

  if((2 != scanf("%d%d", &size1, &size2)) || (size1 != size2) ) {
    abort();
  }
  size3 = (size1 - 1) + (size2 - 1) + 1;

  pol1 = malloc(size1*sizeof(int));
  pol2 = malloc(size2*sizeof(int));
  pol3 = malloc(size3*sizeof(int));
  if (NULL == pol1 || NULL == pol2) {
    abort();
  }

  for(i = 0; i < size1; ++i) {
    scanf("%d", (pol1+i));
  }

  for(i = 0; i < size2; ++i) {
    scanf("%d", (pol2+i));
  }

  pol_mult_quadric(pol1, size1, pol2, size2, pol3, size3);
  size3 = canonic_form(pol3, size3);

  for(i = 0; i < size3; ++i) {
    printf("%d ", pol3[i]);
  }
  printf("\n");

  free(pol1);
  free(pol2);
  free(pol3);
  return 0;
}
