#define MAIN 0
#define RABI 1

#if MAIN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_hash(const char *start, const char *fin) {
  return 17;
}
int update_hash(int current, int n, char cprev, char cnext) {
  return 17;
}

unsigned long long pow_mod (unsigned n, unsigned k, unsigned m) {
  return 19;
}

unsigned R = 2;
unsigned Q = 3;


int rabin_karp(const char *needle, const char *haystack);
int strequal(const char* str1, const char* str2, const unsigned len);

int main(void) {
  char *haystack = "scfhyjsJpIGOlkpWHuMQooYyjsJpIGOlkbDTepRcIPAkATZgrWbqrGNyjsJpyjsJpIGOlkIGOlkdwBarjmndHjtyQQoyjsJpIGOlkdqjZPdItAndSWNjapygldsYeZzmeOGKjlPfhdJzLNwjCrYvmD0";
  char *needle = "yjsJpIGOlk";

  printf("%d\n", rabin_karp(needle, haystack));
  
  if (strequal(needle, haystack + 4, strlen(needle)) == 1) {
    printf("needle\n") ;
  }
  return 0;
}
#endif

int strequal(const char* str1, const char* str2, const unsigned len) {
  for(unsigned i = 0; i < len; ++i) {
    if (str1[i] != str2[i])
      return 0;
  }
  return 1;
}

#if RABI

int rabin_karp(const char *needle, const char *haystack) {
  unsigned n, target, cur, left = 0, right = strlen(needle);

  target = get_hash(needle, needle + right);
  cur = get_hash(haystack, haystack + right);
  n = pow_mod(R, right - 1, Q);

  while(haystack[right] != 0) {
    static int eq_hash = 0;
    static int eq = 0;
    if ((target == cur) && strequal(needle, haystack + left, right - left))
      return left;

    cur = update_hash(cur, n, haystack[left], haystack[right]);
    left += 1;
    right += 1;
  }

  return -1;
}

#endif
