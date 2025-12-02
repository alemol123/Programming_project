#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include <pthread.h>

typedef struct {
    int duration;
    int remaining;
    int running;      
    Uint32 startTime;

    pthread_mutex_t lock;
    pthread_t thread;
    int thread_created; // 1 = success  0 = not created or failure
    int quit;         
} Timer;

//function declarations
void timer_init(Timer *t, int seconds);
void timer_restart(Timer *t, int seconds);
void *timer_thread_func(void *arg);
void timer_shutdown(Timer *t);

#endif
