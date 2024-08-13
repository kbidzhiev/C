

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strstrci(char const *needle, char const *haystack) {
  const int haystack_size = strlen(haystack);
  const int needle_size = strlen(needle);
  for(int i = 0; i < haystack_size - needle_size; ++i) {
    int match = 0;
    for(int j = 0; j < needle_size; ++j) {
      if (tolower(haystack[i + j]) != tolower(needle[j])) {
        match = 0;
        break; 
      }
      match = 1;
    }
    if (match == 1)
      return haystack + i; 
  }
  return NULL;
}

static char *read_word(int *len) {
  char *text;
  int res, n, i;

  res = scanf("%d", len);
  assert(res == 1);

  n = *len;
  assert(n > 0);

  text = (char *)calloc(n + 1, sizeof(char));
  assert(text != NULL);

  scanf("%*c");

  for (i = 0; i < n; ++i) {
    res = scanf("%c", text + i);
    assert(res == 1);
  }

  return text;
}

int main() {
  int nlen, hlen, res;
  char *needle, *haystack, *sres;

  haystack = read_word(&hlen);
  needle = read_word(&nlen);

  sres = strstrci(needle, haystack);

  printf("%s\n", sres);

  free(haystack);
  free(needle);
}


