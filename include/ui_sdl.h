#include <SDL2/SDL.h>
#ifndef UI_SDL_H
#define UI_SDL_H


struct GameState;
struct CurrentInput;


typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} UIContext;

int ui_init(UIContext *ui);
void ui_render_game(UIContext *ui, struct GameState *game, struct CurrentInput *input);
void ui_render_results(UIContext *ui,  struct GameState *game);
void ui_cleanup(UIContext *ui);
void ui_render(struct GameState *state);
void ui_handle_input(struct CurrentInput *input);

#endif