#include "input.h"
#include <string.h>
//resetting the user's current input state
void input_reset(CurrentInput *in)
{
    in->length = 0;
    in->buffer[0] = '\0';
}
//SDL events related to text entry
void input_handle_event(CurrentInput *in, SDL_Event *e)
{
    if (e->type == SDL_TEXTINPUT) {
        if (in->length < (int)sizeof(in->buffer) - 1) {
            strcat(in->buffer, e->text.text);
            in->length += strlen(e->text.text);
        }
    }
    else if (e->type == SDL_KEYDOWN) {
        // Handling backspace
        if (e->key.keysym.sym == SDLK_BACKSPACE && in->length > 0) {
            in->buffer[--in->length] = '\0';
        }
        
    }
}
//checks the users current input with the word targetted
int input_check_word(CurrentInput *in, const char *target)
{
    return strcmp(in->buffer, target) == 0;
}
