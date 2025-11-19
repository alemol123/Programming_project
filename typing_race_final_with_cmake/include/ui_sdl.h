#ifndef UI_SDL_H
#define UI_SDL_H
#include <SDL2/SDL.h>
typedef struct GameState GameState;
typedef struct CurrentInput CurrentInput;
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} UIContext;
int ui_init(UIContext *ui);
void ui_render_game(UIContext *ui, GameState *game, CurrentInput *input);
void ui_render_results(UIContext *ui, GameState *game);
void ui_cleanup(UIContext *ui);
#endif