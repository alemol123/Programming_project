#ifndef UI_SDL_H
#define UI_SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "input.h"   //  full definition for CurrentInput

// Forward declarations for structures used but defined elsewhere
struct GameState;    

typedef struct UIContext {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
} UIContext;


// Function declarations
int ui_init(UIContext *ui);
void ui_render_game(UIContext *ui, struct GameState *game, CurrentInput *input);
void ui_draw_text(UIContext *ui, const char *text, int x, int y, SDL_Color color);
void ui_render_results(UIContext *ui, struct GameState *game);
void ui_cleanup(UIContext *ui);
void ui_render_game_over(UIContext *ui, struct GameState *game);


#endif
