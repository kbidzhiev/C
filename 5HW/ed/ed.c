#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int read_number()
{
	int res, scnf;
	scnf = scanf("%d", &res);
	if (scnf != 1)
		abort();
	return res;
}

struct String {
	char *data;
	int size;
};

struct String read_str()
{
	struct String str;

	str.size = read_number();
	str.data = calloc(str.size, sizeof(char));
	if (!str.data)
		abort();

	char c;
	for (int i = 0; i < str.size; ++i) {
		scanf(" %c", &c);
		str.data[i] = c;
	}
	return str;
}

void free_str(struct String *str)
{
	free(str->data);
	str->data = NULL;
	str->size = 0;
}

void print_str(const struct String str)
{
	for (int i = 0; i < str.size; ++i)
		printf("%c", str.data[i]);
	printf("\n");
}

int min(const int a, const int b)
{
	return a < b ? a : b;
}

struct Array2D {
	int *data;
	int cols;
	int rows;
};

void print_array2D(const struct Array2D arr)
{
	for (int i = 0; i < arr.rows; ++i) {
		for (int j = 0; j < arr.cols; ++j) {
			printf("%d ", arr.data[i * arr.cols + j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int ed_distance_impl(const struct String word1,
        const struct String word2,
        const int i,
        const int j,
        const int add,
        const int rm,
        const int rpl,
        struct Array2D *memo)
{
	const int idx2D = i * (memo->cols) + j;

	if (i == 0 && j == 0)
		return 0;
	if (i < 0 || j < 0)
		return INT_MAX;
	if (memo->data[idx2D] != INT_MAX)
		return memo->data[idx2D];

	//printf("i = %d, j = %d\n", i, j);

	int res = memo->data[idx2D];

	int to_rpl = ed_distance_impl(
	        word1, word2, i - 1, j - 1, add, rm, rpl, memo);
	if (to_rpl != INT_MAX && (i > 0 && j > 0)) {
		if (word1.data[j - 1] != word2.data[i - 1]) {
			to_rpl += rpl;
		}

		res = min(res, to_rpl);
	}

	int to_add =
	        ed_distance_impl(word1, word2, i, j - 1, add, rm, rpl, memo);
	if (to_add != INT_MAX) {
		to_add += add;
		res = min(res, to_add);
	}

	int to_rm =
	        ed_distance_impl(word1, word2, i - 1, j, add, rm, rpl, memo);
	if (to_rm != INT_MAX) {
		to_rm += rm;
		res = min(res, to_rm);
	}

	memo->data[idx2D] = res;

	// print_array2D(*memo);

	return res;
}

int ed_distance(const struct String word1,
        const struct String word2,
        const int add,
        const int rm,
        const int rpl)
{
	struct Array2D memo;
	memo.cols = word1.size + 1;
	memo.rows = word2.size + 1;
	memo.data = calloc(memo.cols * memo.rows, sizeof(int));
	for (int i = 0; i < memo.cols * memo.rows; ++i)
		memo.data[i] = INT_MAX;
	memo.data[0] = 0;

	int i_last = word2.size;
	int j_last = word1.size;
	int res = ed_distance_impl(
	        word1, word2, i_last, j_last, add, rm, rpl, &memo);

	//print_array2D(memo);
	free(memo.data);

	return res;
}

int main(void)
{
	int add_price, rm_price, replace_price;
	struct String word1, word2;
	add_price = read_number();
	rm_price = read_number();
	replace_price = read_number();

	word1 = read_str();
	word2 = read_str();

	//print_str(word1);
	//print_str(word2);

	int ed = ed_distance(word2, word1, add_price, rm_price, replace_price);
	printf("%d\n", ed);

	free_str(&word1);
	free_str(&word2);
	return 0;
}