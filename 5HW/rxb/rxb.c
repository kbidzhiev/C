#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *read_input()
{
	size_t size = 0;
	char *word;
	char buffer[1024];
	if (scanf("%s", buffer) != 1)
		abort();

	size = strlen(buffer);
	word = (char *)malloc(size + 1);
	if (!word)
		abort();
	return strcpy(word, buffer);
}

const char *pattern = "^[A-Za-z0-9.]+@[A-Za-z.]+[.][A-Za-z.]+$";

int main(void)
{
	int res;
	char *s;
	regex_t regex;

	regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB );

	s = read_input();
	res = regexec(&regex, s, 0, NULL, 0);

	res = res == REG_NOMATCH ? 0 : 1;

	printf("%d", res);
	regfree(&regex);
	free(s);
	return 0;
}
