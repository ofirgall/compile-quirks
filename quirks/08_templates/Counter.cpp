#include "Counter.h"
#include <stdint.h>

template<> size_t Counter<size_t>::counter = 0;
