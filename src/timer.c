#include "timer.h"
#include <SDL2/SDL.h>
#include <unistd.h>    
#include <stdio.h>
//recalculating remaining time and running time status
static void timer_update_locked(Timer *t)
{
    //current time and remaining time
    Uint32 now = SDL_GetTicks();
    int elapsed = (int)((now - t->startTime) / 1000);
    int remaining = t->duration - elapsed;

    if (remaining <= 0) {
        //time run out. timer finished
        t->remaining = 0;
        t->running = 0;   
    } else {
        //update state variables
        t->remaining = remaining;
        t->running = 1;
    }
}
//periodically checking for the current time, and updates the remaining duration (main thread)
void *timer_thread_func(void *arg)
{
    Timer *t = (Timer *)arg;

    while (1) {
        //lock mutex before reading or writing
        pthread_mutex_lock(&t->lock);

        if (t->quit) {
            // main thread requested quit
            pthread_mutex_unlock(&t->lock);
            break;
        }

        if (t->running) {
            //update only if timer is running
            timer_update_locked(t);
        }

        int still_running = t->running;
        pthread_mutex_unlock(&t->lock);

        // Sleep to prevent this thread from burning the cpu
        (void)still_running;
        usleep(100000);  // 100 microseconds
    }

    return NULL;
}
//initializes timer structure, mutex, and starts background thread
void timer_init(Timer *t, int seconds)
{
    //initial configurations
    t->duration  = seconds;
    t->remaining = seconds;
    t->running   = 1;
    t->quit      = 0;
    t->thread_created = 0;
    t->startTime = SDL_GetTicks();
    //initialize mutex for thrwad synchronization + error handling
    if (pthread_mutex_init(&t->lock, NULL) != 0) {
        fprintf(stderr, "Failed to initialize timer mutex.\n");
        t->running = 0;
        return;
    }
// create and start actual thread passing timer structure
    if (pthread_create(&t->thread, NULL, timer_thread_func, t) != 0) {
        fprintf(stderr, "Failed to create timer thread.\n");
        t->running = 0;
        pthread_mutex_destroy(&t->lock);
        return;
    }

    t->thread_created = 1;
}
//resets timer countdown when restarting the game
void timer_restart(Timer *t, int seconds)
{
    pthread_mutex_lock(&t->lock);
    t->duration  = seconds;
    t->remaining = seconds;
    t->running   = 1;
    t->startTime = SDL_GetTicks();
    pthread_mutex_unlock(&t->lock);
}
//timer thread exit
void timer_shutdown(Timer *t)
{
    if (t->thread_created) {
        pthread_mutex_lock(&t->lock);
        t->quit = 1;
        pthread_mutex_unlock(&t->lock);
        pthread_join(t->thread, NULL);
        t->thread_created = 0;
    }
    //destroy synchronization
    pthread_mutex_destroy(&t->lock);
}
