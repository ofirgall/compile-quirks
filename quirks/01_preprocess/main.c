#include <stdio.h>

#define MY_NUM (50)

#ifdef MY_NUM_OVERRIDE
	#define MY_NUM (5000)
#endif

int main(int argc, char *argv[])
{
	printf("MY_NUM: %u\r\n", MY_NUM);
	return 0;
}
