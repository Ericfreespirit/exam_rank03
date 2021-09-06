#include <stdio.h>

int main(int ac, char **av)
{
	int a;
	int b;
	float res;

	a = 25;
	b = 10;
	res = (float)a / (float)b;
	printf("%f\n", res);

	return (0);
}