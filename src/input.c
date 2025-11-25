#include "input.h"
#include <string.h>

void input_reset(CurrentInput *in)
{
    in->length = 0;
    in->buffer[0] = '\0';
}

void input_handle_event(CurrentInput *in, SDL_Event *e)
{
    if (e->type == SDL_TEXTINPUT) {
        // Append new characters
        if (in->length < (int)sizeof(in->buffer) - 1) {
            strcat(in->buffer, e->text.text);
            in->length += strlen(e->text.text);
        }
    }
    else if (e->type == SDL_KEYDOWN) {
        //  Handle backspace
        if (e->key.keysym.sym == SDLK_BACKSPACE && in->length > 0) {
            in->buffer[--in->length] = '\0';
        }
        // Do nothing for Enter here — it’s handled in game.c
    }
}

int input_check_word(CurrentInput *in, const char *target)
{
    return strcmp(in->buffer, target) == 0;
}
