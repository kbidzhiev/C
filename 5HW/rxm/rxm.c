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

struct match_t {
	int begin;
	int size;
};

void swaporder(char *word, const size_t sz)
{
	for (int i = 0; i < sz / 2; ++i) {
		char tmp = word[i];
		word[i] = word[sz - 1 - i];
		word[sz - 1 - i] = tmp;
	}
}

void print_array(const char *word, const int word_sz)
{
	for (int i = 0; i < word_sz; ++i)
		printf("%c", word[i]);
	printf("\n");
}

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
	if (!res)
		m = (struct match_t){matches[0].rm_so, matches[0].rm_eo - matches[0].rm_so};
	else if (res == REG_NOMATCH)
		m = (struct match_t){-1, -1};

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

	for (char *start = book; m.size == -1; start += m.size) {
		m = findmatch(word, start);
    start += m.begin;
		swaporder(start, m.size);
	}
	print_array(book, book_sz);

	free(book);
	free(word);

	return 0;
}
