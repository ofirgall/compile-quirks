#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>

template<typename T>
class Counter
{
public:
	Counter() = default;
	~Counter() = default;

	static void IncreaseCounter()
	{
		counter++;
	}

	static void PrintCounter()
	{
		printf("Counter: %u\r\n", counter);
	}

private:
	static T counter;
};


#endif // _COMMON_H_
