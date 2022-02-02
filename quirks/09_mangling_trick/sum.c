
#include <stdint.h>
#include <stdio.h>

uint32_t sum(uint32_t a, uint32_t b)
{
	printf("A: 0x%x\r\n", a);
	printf("B: 0x%x\r\n", b);
	return a + b;
}
