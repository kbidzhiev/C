#include <stdio.h>
#include <stdlib.h>



int main(void) {
  int ncities;
  int *distances;

  if(1 != scanf("%d", &ncities)) {
    abort();
  }
  distances = calloc(ncities, sizeof(int));
  if (!distances)
    abort();
  
  for(int i = 0; i < ncities; ++i) {
    if(1 != scanf("%d", distances + i))
      abort();
  }

  for(int i = 0; i < ncities; ++i)
    printf("%d ", distances[i]);
  free(distances);
  printf("\n%d", ncities);
  return 0;
}
