#include "utils.h"
#include <stdlib.h>

int utils_rand_int(int min, int max)
{
    if (max <= min)
        return min;  // safety fallback for invalid range

    return rand() % (max - min + 1) + min;
}
