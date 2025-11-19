#ifndef TIMER_H
#define TIMER_H
#include <pthread.h>
typedef struct {
    int duration;
    int remaining;
    int running;
    pthread_mutex_t lock;
} Timer;
void timer_init(Timer *t, int seconds);
void *timer_thread_func(void *arg);
#endif