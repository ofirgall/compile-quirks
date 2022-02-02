#include "sum.h"
#include "Counter.h"

int sum(int a, int b)
{
	Counter<size_t>::IncreaseCounter();
	return a + b;
}
