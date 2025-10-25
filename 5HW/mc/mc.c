#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(const int a, const int b)
{
	return a < b ? a : b;
}

int max(const int a, const int b)
{
	return a > b ? a : b;
}

int main(void)
{
	int Ntot, ncoins, *coins, *V;

	if (scanf("%d", &Ntot) != 1)
		abort();

	if (scanf("%d", &ncoins) != 1)
		abort();

	coins = calloc(ncoins, sizeof(int));
	if (!coins)
		abort();

	for (int i = 0; i < ncoins; ++i)
		scanf("%d", coins + i);

	V = calloc(Ntot + 1, sizeof(int));
	if (!V)
		abort();

	for (int i = 0; i < Ntot + 1; ++i)
		V[i] = INT_MAX;

	V[0] = 0;
	for (int i = 0; i < Ntot + 1; ++i) {
		if (V[i] == INT_MAX)
			continue;
		for (int j = 0; j < ncoins; ++j) {
			int idx = i + coins[j];
			if (idx < Ntot + 1) {
				V[idx] = min(V[idx], V[i] + 1);
			}
		}
	}

	printf("%d\n", V[Ntot]);

	free(V);
	free(coins);
	return 0;
}
