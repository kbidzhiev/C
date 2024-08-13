#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strcpy_r(char *acc, int *acc_size,
                const char *src, const int size_src,
                const char *word, const int size_word) {
  char *new_str = calloc(*acc_size + size_src + size_word + 1, sizeof(char));
  memcpy(new_str, acc, *acc_size);
  memcpy(new_str + *acc_size, src, size_src);
  memcpy(new_str + *acc_size + size_src, word, size_word);
  *acc_size += size_src + size_word;
  return new_str;
}

char *replace(char *str, char const *from, char const *to) {
  const int len_from = strlen(from);
  const int len_to = strlen(to);
  char *acc = NULL;
  int acc_size = 0;
  
  for(;;) {
    char *pos = strstr(str, from);
    if (pos == NULL) {
      int remain = strlen(str);
      char *new_acc = strcpy_r(acc, &acc_size,
        str, remain,
        to, 0);
      free(acc);
      return new_acc;
    }
    char *new_acc = strcpy_r(acc, &acc_size,
        str, pos - str,
        to, len_to);
    free(acc);
    acc = new_acc;
    str = pos + len_from;
  }
  return acc;
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

  scanf("%*c"); //to skip the \n from input

  for (i = 0; i < n; ++i) {
    res = scanf("%c", text + i);
    assert(res == 1);
  }

  return text;
}

int main() {
  int i, nword, nrepl, nstr, res;
  char *word, *repl, *str, *newstr;

  word = read_word(&nword);
  repl = read_word(&nrepl);
  str = read_word(&nstr);

  newstr = replace(str, word, repl);

  printf("%s\n", newstr);

  free(word);
  free(repl);
  free(str);
  free(newstr);
}
