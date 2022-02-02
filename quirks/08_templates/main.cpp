#include <stdio.h>

#include "sum.h"
#include "Counter.h"

int main(int argc, char *argv[])
{
	printf("3 + 5: %d\r\n", sum(3, 5));
	Counter<size_t>::PrintCounter();
	Counter<size_t>::IncreaseCounter();
	Counter<size_t>::PrintCounter();
	return 0;
}
