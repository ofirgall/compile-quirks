#include <stdio.h>
#include "sum.h"

static int inner_sum(int a, int b);

int global_counter = 0;
static int static_global_counter = 0;
int global_counter_5 = 5;

int sum(int a, int b)
{
	return inner_sum(a, b);
}


static int inner_sum(int a, int b)
{
	static int function_counter = 0;

	global_counter++;
	static_global_counter++;
	global_counter_5++;
	function_counter++;

	return a + b;
}

void print_counters()
{
	static int function_counter = 0;

	printf("global_counter: %d\r\n", global_counter);
	printf("static_global_counter: %d\r\n", static_global_counter);
	printf("global_counter_5: %d\r\n", global_counter_5);
	printf("function_counter: %d\r\n", function_counter);
}
