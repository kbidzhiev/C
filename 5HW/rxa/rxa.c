#include <stdio.h>
#include <stdlib.h>

char nextsym()
{
	char c;
	if (scanf("%c", &c) != 1)
		return 0;
	return c;
}

int nextstate(int state, const char c)
{
	int *r = NULL;
	switch (state) {
	case 1: { int res[] = {1, 2, 5}; r = res;}; break;
	case 2: { int res[] = {1, 2, 3}; r = res;}; break;
	case 3:
	case 4: { int res[] = {5, 4, 3}; r = res;}; break;
	case 5: return 5;
	}
	return r[c - 'a'];
}

int isabc(const char c)
{
	if (c == 'a' || c == 'b' || c == 'c')
		return 1;
	return 0;
}

int main(void)
{
	int state = 1;
	for (;;) {
		char c = nextsym();
		if (!isabc(c)) 
			break;
		state = nextstate(state, c);
	}
	if (state == 2 || state == 3 || state == 4)
		printf("1");
	else
		printf("0");

	return 0;
}
