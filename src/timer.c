/**
 * @file timer.c
 * @brief Timer logic and timer thread implementation.
 *
 * This module provides:
 *  - Initialization of the Timer structure.
 *  - A thread function that decrements remaining time every second.
 *  - A simple running flag to indicate when time has expired.
 */

#include "timer.h"
#include <unistd.h>

/**
 * @brief Initialize a Timer structure.
 *
 * Responsibilities:
 *  - Set the initial duration and remaining time.
 *  - Mark the timer as running (or stopped, depending on design).
 *  - Initialize the mutex used for thread-safe access to the timer fields.
 *
 * @param t Pointer to a Timer instance.
 * @param seconds Total duration of the timer in seconds.
 */
void timer_init(Timer *t, int seconds)
{
    /* TODO:
     *  - Set t->duration and t->remaining to 'seconds'.
     *  - Set t->running to 1 (active).
     *  - Initialize t->lock via pthread_mutex_init().
     */
}

/**
 * @brief Thread function that performs countdown logic.
 *
 * Responsibilities:
 *  - While the timer is running and remaining time is > 0:
 *      * Sleep for a fixed interval (usually 1 second).
 *      * Decrement the remaining time in a thread-safe way.
 *  - When time reaches 0, mark running as 0 to signal the game that
 *    time is over.
 *
 * Notes:
 *  - This function is meant to be passed to pthread_create().
 *  - It should accept a Timer* as its argument.
 *
 * @param arg Pointer passed from pthread_create, expected to be a Timer*.
 * @return void* Optional return value (usually NULL).
 */
void *timer_thread_func(void *arg)
{
    /* TODO:
     *  - Cast arg to (Timer*).
     *  - Loop while remaining > 0 and running == 1.
     *  - Use sleep(1) to wait one second per iteration.
     *  - Use the mutex to protect modifications to 'remaining'.
     *  - Set running = 0 when finished.
     */
    return NULL;
}
