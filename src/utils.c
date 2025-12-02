#include "utils.h"
#include <stdlib.h>

 //generates pseudo random integer with specified range. for choosing random words
int utils_rand_int(int min, int max)
{
    //check for invalid 0 length range
    if (max <= min)
        return min;  

    return rand() % (max - min + 1) + min;
}
