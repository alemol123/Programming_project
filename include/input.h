#ifndef INPUT_H
#define INPUT_H
#include <SDL2/SDL.h>


typedef struct {
    char buffer[64];
    int length;
} CurrentInput;

void input_reset(CurrentInput *in);
void input_handle_event(CurrentInput *in, SDL_Event *e);
int input_check_word(CurrentInput *in, const char *target);
#endif