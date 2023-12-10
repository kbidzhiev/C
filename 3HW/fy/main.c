#include<stdio.h>
#include<stdlib.h>

int myrand() {
  static unsigned long int seed = 1;
  seed = seed * 1103515245 + 12345;
  return (unsigned int)(seed / 65536) % 32768;
}

void shuffle(int* p, unsigned len) {
  int rand, tmp;
  unsigned i;
  for (i = len; i > 0; --i) {
    rand = myrand() % i;
    tmp = p[i-1];
    p[i-1] = p[rand];
    p[rand] = tmp;
  }
}

int main() {
  unsigned len, i;
  int *p;

  if(1 != scanf("%u", &len))
    abort();
  if(0 == len) {
    printf("0\n");
    return 0;
  }
  p = (int *) malloc(len * sizeof(int));
  if(NULL == p)
    abort();

  for(i = 0; i < len; ++i) {
    scanf("%d", &(p[i]));
  }
  shuffle(p, len);

  for(i = 0; i < len; ++i) {
    printf("%d ", p[i]);
  }
  printf("\n");

  free(p);
  return 0;
}

