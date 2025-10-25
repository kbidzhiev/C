#include <stdio.h>
#include <stdlib.h>

int read_number()
{
	int n;
	if (scanf("%d", &n) != 1)
		abort();
	return n;
}

int *read_array(const int size)
{
	int *arr = calloc(size, sizeof(int));
	if (!arr)
		abort();

	for (int i = 0; i < size; ++i)
		scanf("%d", arr + i);

	return arr;
}

void print_array(const int *arr, const int size)
{
	for (int i = 0; i < size; ++i)
		printf("%d ", arr[i]);
	printf("\n");
}

void print_matrix(const int *arr, const int rows, const int cols)
{
	for (int j = 0; j < rows; ++j) {
		for (int i = 0; i < cols; ++i) {
			int val = arr[i + j * (cols)];
			if (val != 0)
				printf("%d(%d,%d)| ",
				        arr[j * (cols) + i],
				        i,
				        j);
			else
				printf("_(%d,%d)| ", i, j);
		}
		printf("\n");
	}
	printf("\n");
}

int max(const int a, const int b)
{
	return a > b ? a : b;
}

int main(void)
{
	int nitems, *weights, capacity;

	capacity = read_number();
	nitems = read_number();
	weights = read_array(nitems);

	// printf("Capacity %d\n", capacity);
	// printf("%d items\n", nitems);
	// print_array(weights, nitems);
	capacity += 1;
	nitems += 1;

	int *V = calloc(capacity * nitems, sizeof(int));
	for (int c = 0; c < capacity; ++c) {
		int item = 0;
		V[item * capacity + c] = 0;
	}
	for (int i = 0; i < nitems; ++i) {
		int c = 0;
		V[i * capacity + c] = 0;
	}

	for (int item = 1; item < nitems; ++item) {
		// printf("filling item %d, weight %d\n", item,
		// weights[item-1]);
		for (int c = 1; c < capacity; ++c) {
			int idx_curr = item * capacity + c;
			int idx_not_incl = idx_curr - capacity;
			int idx_incl = idx_not_incl - weights[item - 1];

			V[idx_curr] = V[idx_not_incl];
			if (c - weights[item - 1] < 0)
				continue;
			V[idx_curr] = max(V[idx_curr], V[idx_incl] + 1);
		}
		// print_matrix(V, nitems + 1, capacity + 1);
	}

	printf("%d\n", V[nitems * capacity - 1]);

	free(weights);
	return 0;
}
