#include <stdio.h>
#include <stdint.h>

uint64_t c_sum(uint64_t a, uint64_t b);

int main(int argc, char *argv[])
{
	uint64_t a = 0x8899AABBCCDDEEFF;
	uint64_t b = 0x0011223344556677;
	printf("0x%llx\r\n", c_sum(a, b));
	return 0;
}
