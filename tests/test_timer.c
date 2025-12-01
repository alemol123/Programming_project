#include "timer.h"
#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>

int main(void)
{
    printf("Running test_timer...\n");

    // Initialise SDL timer subsystem
    if (SDL_Init(SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    Timer t;
    timer_init(&t, 2);   // 2-second timer

    // Basic invariants after init
    assert(t.duration == 2);
    assert(t.remaining == 2);
    assert(t.running == 1);

    SDL_Quit();
    printf("test_timer passed.\n");
    return 0;
}
