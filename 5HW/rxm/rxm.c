#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

char *read_array(int *word_sz)
{
	char newline;
	if (!scanf("%d", word_sz))
		abort();

	if (scanf("%c", &newline) != 1 || newline != '\n')
		abort();

	char *word = calloc(*word_sz, sizeof(char));
	for (int i = 0; i < *word_sz; ++i)
		if (!scanf("%c", &word[i]))
			abort();
	return word;
}

void swaporder(char *word, int begin, int end)
{
	for (int i = 0; i < (end - begin) / 2; ++i) {
		char tmp = word[begin + i];
		word[begin + i] = word[end - 1 - i];
		word[end - 1 - i] = tmp;
	}
}

void print_array(const char *word, const int word_sz)
{
	for (int i = 0; i < word_sz; ++i)
		printf("%c", word[i]);
	printf("\n");
}

struct match_t {
	int begin;
	int end;
};

struct match_t findmatch(const char *pattern, const char *book)
{
	struct match_t m;
	regex_t reg;
	regmatch_t matches[1];
	int res;
	res = regcomp(&reg, pattern, REG_EXTENDED);
	if (res) {
		printf("not compiled");
		abort();
	}

	res = regexec(&reg, book, 1, matches, 0);
	if (!res) {
		m.begin = matches[0].rm_so;
		m.end = matches[0].rm_eo;
	}
	else if (res == REG_NOMATCH) {
		m.begin = 0;
		m.end = 0;
	}
	else {
		printf("match error");
		abort();
	}

	regfree(&reg);
	return m;
}

int main(void)
{
	struct match_t m = {0, 0};
	int word_sz, book_sz;
	char *word = read_array(&word_sz);
	char *book = read_array(&book_sz);

	for (char *start = book; m.begin == -1 && m.end == -1; start += m.end) {
		m = findmatch(word, start);
		swaporder(start, m.begin, m.end);
	}
	print_array(book, book_sz);

	free(book);
	free(word);

	return 0;
}
