#include "timer.h"
#include <SDL2/SDL.h>
#include <unistd.h>    // usleep
#include <stdio.h>

static void timer_update_locked(Timer *t)
{
    Uint32 now = SDL_GetTicks();
    int elapsed = (int)((now - t->startTime) / 1000);
    int remaining = t->duration - elapsed;

    if (remaining <= 0) {
        t->remaining = 0;
        t->running = 0;   // mark as finished
    } else {
        t->remaining = remaining;
        t->running = 1;
    }
}

void *timer_thread_func(void *arg)
{
    Timer *t = (Timer *)arg;

    while (1) {
        pthread_mutex_lock(&t->lock);

        if (t->quit) {
            // main thread requested shutdown
            pthread_mutex_unlock(&t->lock);
            break;
        }

        if (t->running) {
            timer_update_locked(t);
        }

        int still_running = t->running;
        pthread_mutex_unlock(&t->lock);

        // Sleep a bit between checks to avoid burning CPU
        (void)still_running;
        usleep(100000);  // 100 ms
    }

    return NULL;
}

void timer_init(Timer *t, int seconds)
{
    t->duration  = seconds;
    t->remaining = seconds;
    t->running   = 1;
    t->quit      = 0;
    t->thread_created = 0;
    t->startTime = SDL_GetTicks();

    if (pthread_mutex_init(&t->lock, NULL) != 0) {
        fprintf(stderr, "Failed to initialize timer mutex.\n");
        t->running = 0;
        return;
    }

    if (pthread_create(&t->thread, NULL, timer_thread_func, t) != 0) {
        fprintf(stderr, "Failed to create timer thread.\n");
        t->running = 0;
        pthread_mutex_destroy(&t->lock);
        return;
    }

    t->thread_created = 1;
}

void timer_restart(Timer *t, int seconds)
{
    pthread_mutex_lock(&t->lock);
    t->duration  = seconds;
    t->remaining = seconds;
    t->running   = 1;
    t->startTime = SDL_GetTicks();
    pthread_mutex_unlock(&t->lock);
}

void timer_shutdown(Timer *t)
{
    if (t->thread_created) {
        pthread_mutex_lock(&t->lock);
        t->quit = 1;
        pthread_mutex_unlock(&t->lock);

        // Wait for the worker thread to exit
        pthread_join(t->thread, NULL);
        t->thread_created = 0;
    }

    pthread_mutex_destroy(&t->lock);
}
