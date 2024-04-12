#include "lr.h"


struct node_t * build_list(FILE *f);

int main(int argc, char **argv) {
  int i = 0; 
  FILE *f = fopen(argv[1], "r");
  while(1 == fscanf(f, "%d", &i)) {
    printf("%d ", i) ;
  }
  fclose(f);
  return 0;
}
