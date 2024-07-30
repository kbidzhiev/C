#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char* strscanf(const int len) {
  char *str = calloc(len + 1, sizeof(char));
  for(int i = 0; i < len; ++i) {
    scanf("%c", str + i);
  }
  str[len] = '\0';
  return str;
}

char* swapstr(char const *input) {
  const int len = strlen(input);
  char *str = calloc(len + 1, sizeof(char));
  for(int i = 0; i < len; ++i) {
    str[i] = input[len - 1 - i];
  }
  str[len] = '\0';
  return str;
}

char* replacestr(char *str, const char* substr) {
  const int len = strlen(substr);
  for(int i = 0; i < len; ++i) {
    str[i] = substr[i];
  }
  return str + len;
}


int main(void) {
  int slen, len;
  char *substr, *str, *match, *swpstr;
  
  scanf("%d ", &slen); //space after %d
  substr = strscanf(slen);

  scanf("%d ", &len); //space after %d
  str = strscanf(len);
  swpstr = swapstr(substr);
   
  match = str;
  while((match = strstr(match, substr)) != NULL && substr != NULL) {
    match = replacestr(match, swpstr);
  }
  printf("%s", str);
  printf("\n");

  free(swpstr);
  free(str);
  free(substr);
  return 0;
}
