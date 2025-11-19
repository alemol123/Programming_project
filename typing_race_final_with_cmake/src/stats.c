/**
 * @file stats.c
 * @brief Score and statistics handling for the Typing Race game.
 *
 * This module is responsible for:
 *  - Resetting the statistics at the beginning of a game.
 *  - Updating the accuracy percentage when values change.
 *  - (Optionally) providing helper functions to add correct/incorrect words.
 */

#include "stats.h"

/**
 * @brief Reset all statistics values to zero.
 *
 * Responsibilities:
 *  - Set score to 0.
 *  - Set correct and total counters to 0.
 *  - Set accuracy to 0.0.
 *
 * @param s Pointer to a Stats structure to reset.
 */
void stats_reset(Stats *s)
{
    /* TODO:
     *  - Set all fields of Stats to zero.
     */
}

/**
 * @brief Recalculate the accuracy percentage.
 *
 * Formula:
 *  - If total == 0 -> accuracy = 0.0
 *  - Else         -> accuracy = (correct / total) * 100.0
 *
 * @param s Pointer to a Stats structure to update.
 */
void stats_update_accuracy(Stats *s)
{
    /* TODO:
     *  - Implement the formula above.
     */
}
