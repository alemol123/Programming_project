/**
 * @file utils.c
 * @brief Utility helper functions for the Typing Race game.
 *
 * This module provides small helper functions that do not belong
 * to any specific module (e.g., random number utilities).
 */

#include "utils.h"
#include <stdlib.h>

/**
 * @brief Generate a random integer in the inclusive range [min, max].
 *
 * Precondition:
 *  - Assumes that srand() has been called once in the program (e.g. in game_init()).
 *
 * @param min Minimum value of the range (inclusive).
 * @param max Maximum value of the range (inclusive).
 * @return int A random integer N such that min <= N <= max.
 */
int utils_rand_int(int min, int max)
{
    if (max <= min)
        return min;  // safety fallback for invalid range

    return rand() % (max - min + 1) + min;
}
