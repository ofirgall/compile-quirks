#include <stdio.h>

#include "sum.h"
#include "c_sum.h"

int main(int argc, char *argv[])
{
	printf("3 + 5: %d\r\n", sum(3, 5));
	printf("3.2 + 5.1: %f\r\n", sum(3.2, 5.1));
	// printf("4 + 5: %d\r\n", c_sum(4, 5));
	return 0;
}
