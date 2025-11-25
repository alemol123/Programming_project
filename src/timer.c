#include "timer.h"
#include <SDL2/SDL.h>

void timer_init(Timer *t, int seconds)
{
    t->duration = seconds;
    t->remaining = seconds;
    t->running = 1;
    t->startTime = SDL_GetTicks();
}

void timer_update(Timer *t)
{
    if (!t->running) return;
    Uint32 now = SDL_GetTicks();
    int elapsed = (now - t->startTime) / 1000;
    t->remaining = t->duration - elapsed;
    if (t->remaining <= 0) {
        t->remaining = 0;
        t->running = 0;
    }
}
