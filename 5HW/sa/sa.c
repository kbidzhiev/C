#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strcat_r(char *dest, const char *src, int *bufsz) {
  const int len0 = strlen(dest);
  const int requiredlen = strlen(src) + len0 + 1;
  const int size = *bufsz;
  
  if (requiredlen > size) {
   char *newdest = calloc(requiredlen, sizeof(char));
   strcpy(newdest, dest);
   free(dest);
   dest = newdest;
   //printf("reallocation happened %s\n", newdest);
  }
  strcpy(dest + len0, src);
  //printf("NO reallocation %s\n", dest);
  return dest;
}

int main() {
  int buflen, res, catlen;
  char *buf, *catbuf;

  res = scanf("%d", &buflen);
  assert(res == 1);

  buf = (char *)calloc(buflen + 1, sizeof(char));
  assert(buf != NULL);

  catlen = 10;
  catbuf = (char *)calloc(catlen, sizeof(char));
  assert(catbuf != NULL);

  for (; ; ) {
    res = scanf("%s", buf);
    if (res != 1)
      break;
    catbuf = strcat_r(catbuf, buf, &catlen);
  }

  printf("%s\n", catbuf);
  free(buf);
  free(catbuf);
}
