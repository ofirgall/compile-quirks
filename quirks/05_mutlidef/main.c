#include <stdio.h>

#include "math.h"
#include "sum.h"

int main(int argc, char *argv[])
{
	printf("sum of 3 and 5: %u\r\n", sum(3, 5));
	printf("abs of -5: %u\r\n", my_abs(-5));
	return 0;
}
