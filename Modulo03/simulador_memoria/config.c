#include "config.h"

#include <math.h>

int get_bits_len(int size)
{
    return ((floor(log(size * 1024) / log(2)) + 1));
}
