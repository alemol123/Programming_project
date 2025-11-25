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
} Timer;

void timer_init(Timer *t, int seconds);
void timer_update(Timer *t);        // ✅ add this line
void *timer_thread_func(void *arg);

#endif
