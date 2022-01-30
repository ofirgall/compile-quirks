#include <stdio.h>

#include "sum.h"

int main(int argc, char *argv[])
{
	printf("Sum of -3 + 5:%d\r\n", sum(-3, 5));
	printf("Sum Abs of -3 + 5:%d\r\n", sum_abs(-3, 5));
	return 0;
}
