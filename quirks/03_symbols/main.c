#include <stdio.h>

#include "sum.h"

extern int global_counter;
static int static_global_counter;

int main(int argc, char *argv[])
{
	printf("Sum of 3 + 5:%d\r\n", sum(3, 5));
	printf("main::global_counter %u\r\n", global_counter);
	printf("main::static_global_counter %u\r\n", static_global_counter);

	printf("Sum of 4 + 6:%d\r\n", sum(4, 6));
	print_counters();

	return 0;
}
