#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


void multiply_pols(int *pol1, unsigned size1, int *pol2, unsigned size2, int *pol3, unsigned size3) {
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

  if(2 != scanf("%d%d", &size1, &size2)) {
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

  multiply_pols(pol1, size1, pol2, size2, pol3, size3);
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
