#include <stdio.h>
#include <stdlib.h>

char nextsym()
{
	char c;
	if (scanf("%c", &c) != 1)
		return 0;
	return c;
}

int case1(int state, const char c)
{
  int r[] = {1,2,5};
	switch (c) {
	case 'a':
		state = 1;
		break;
	case 'b':
		state = 2;
		break;
	case 'c':
		state = 5;
		break;
	}
	return state;
}

int case2(int state, const char c)
{
	switch (c) {
	case 'a':
		state = 1;
		break;
	case 'b':
		state = 2;
		break;
	case 'c':
		state = 3;
		break;
	}
	return state;
}

int case34(int state, const char c)
{
	switch (c) {
	case 'a':
		state = 5;
		break;
	case 'b':
		state = 4;
		break;
	case 'c':
		state = 3;
		break;
	}
	return state;
}

int case5(int state, const char c)
{
	return 5;
}

int nextstate(int state, const char c)
{
	switch (state) {
	case 1:
		state = case1(state, c);
		break;
	case 2:
		state = case2(state, c);
		break;
	case 3:
	case 4:
		state = case34(state, c);
		break;
	case 5:
		state = case5(state, c);
		break;
	}
	return state;
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
  (state == 1 || state == 5) ? printf("0") : printf("1");

	return 0;
}
