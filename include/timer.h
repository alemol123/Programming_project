#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include <pthread.h>

/**
 * @brief Countdown timer updated by a background thread.
 *
 * Fields:
 *  - duration  : total countdown length in seconds
 *  - remaining : seconds left
 *  - running   : 1 while the countdown is active, 0 when time is up
 *  - startTime : SDL ticks at the moment this countdown started
 *  - lock      : protects concurrent access to the fields above
 *  - thread    : pthread handle for the timer worker thread
 *  - quit      : when set to 1, the worker thread exits its loop
 */
typedef struct {
    int duration;
    int remaining;
    int running;      // 1 = counting down, 0 = finished
    Uint32 startTime;

    pthread_mutex_t lock;
    pthread_t thread;
    int quit;         // 1 = ask thread to exit
} Timer;

/**
 * @brief Initialize the timer state and start the background thread.
 *
 * This also starts an initial countdown of `seconds`.
 */
void timer_init(Timer *t, int seconds);

/**
 * @brief Restart the timer countdown using the same background thread.
 *
 * Used when the player restarts the game.
 */
void timer_restart(Timer *t, int seconds);

/**
 * @brief Background thread function that repeatedly updates the timer.
 *
 * You do not call this directly; it is passed to pthread_create().
 */
void *timer_thread_func(void *arg);

/**
 * @brief Shut down the timer thread and clean up synchronization primitives.
 *
 * MUST be called once before the program exits (e.g. in game_cleanup()).
 */
void timer_shutdown(Timer *t);

#endif
