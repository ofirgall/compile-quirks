#include "sum.h"
#include "my_abs.h"

int sum(int a, int b)
{
	return a + b;
}

int sum_abs(int a, int b)
{
	return my_abs(a) + my_abs(b);
}
