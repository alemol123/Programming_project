#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include <pthread.h>

typedef struct {
    int duration;
    int remaining;
    int running;      // 1 = counting down, 0 = finished
    Uint32 startTime;

    pthread_mutex_t lock;
    pthread_t thread;
    int thread_created; // 1 = thread created successfully, 0 = not created or failed
    int quit;         // 1 = ask thread to exit
} Timer;

void timer_init(Timer *t, int seconds);
void timer_restart(Timer *t, int seconds);
void *timer_thread_func(void *arg);
void timer_shutdown(Timer *t);

#endif
