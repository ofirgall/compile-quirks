#include <stdio.h>

#define MY_DATA_SIZE (2056)
#define MAX_SIZE (1024)

struct my_struct {
	unsigned char data[MY_DATA_SIZE];
};

constexpr size_t MAX_SIZE_CONSTEXPR = 1024;

#if MY_DATA_SIZE > MAX_SIZE
	#error "size of my_struct exceeding MAX_SIZE"
#endif

static_assert(sizeof(my_struct) < MAX_SIZE_CONSTEXPR, "size of my_struct exceeding MY_SIZE_CONSTEXPR");

int main(int argc, char *argv[])
{
	printf("sizeof my_struct: %lu\r\n", sizeof(my_struct));
	printf("MAX_SIZE: %u\r\n", MAX_SIZE);
	printf("MAX_SIZE_CONSTEXPR: %zu\r\n", MAX_SIZE_CONSTEXPR);
	return 0;
}
