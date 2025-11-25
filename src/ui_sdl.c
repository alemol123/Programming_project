#include "ui_sdl.h"
#include "game.h"
#include "input.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

int ui_init(UIContext *ui)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 0;
    }

    ui->window = SDL_CreateWindow(
        "Typing Race",               
        SDL_WINDOWPOS_CENTERED,      
        SDL_WINDOWPOS_CENTERED,      
        800,                         
        600,                         
        SDL_WINDOW_SHOWN
    );

    if (!ui->window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    ui->renderer = SDL_CreateRenderer(ui->window, -1, SDL_RENDERER_ACCELERATED);
    if (!ui->renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(ui->window);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    // Load a font (make sure assets/Roboto-Regular.ttf exists)
    ui->font = TTF_OpenFont("assets/Roboto_SemiCondensed-Black.ttf", 32);
    if (!ui->font) {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(ui->renderer);
        SDL_DestroyWindow(ui->window);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    return 1; // success
}

vvoid ui_draw_text(UIContext *ui, const char *text, int x, int y, SDL_Color color)
{
    if (!text || text[0] == '\0') return;

    SDL_Surface *surface = TTF_RenderText_Solid(ui->font, text, color);
    if (!surface) {
        fprintf(stderr, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(ui->renderer, surface);
    if (!texture) {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dest = {x, y, surface->w, surface->h};
    SDL_RenderCopy(ui->renderer, texture, NULL, &dest);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
 SDL_DestroyTexture(texture);
}

void ui_render_game(UIContext *ui, struct GameState *game, CurrentInput *input)
{
    // New background color
    SDL_SetRenderDrawColor(ui->renderer, 40, 40, 80, 255);  // dark blueish
    SDL_RenderClear(ui->renderer);

    // Define colors for different texts
    SDL_Color gold   = {255, 215, 0, 255};    // Score
    SDL_Color cyan   = {0, 255, 255, 255};    // Timer
    SDL_Color green  = {144, 238, 144, 255};  // "Type the word:"
    SDL_Color white  = {255, 255, 255, 255};  // Player input
    SDL_Color magenta= {255, 105, 180, 255};  // Current word

    // --- Labels and texts ---
    ui_draw_text(ui, "Type the word:", 50, 100, green);
    ui_draw_text(ui, game->currentWord, 330, 100, magenta);
    ui_draw_text(ui, "Your input:", 50, 200, white);
    ui_draw_text(ui, input->buffer, 250, 200, white);

    // --- Score ---
    char scoreText[64];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", game->stats.correct);
    ui_draw_text(ui, scoreText, 50, 20, gold);

    // --- Timer ---
    char timerText[64];
    snprintf(timerText, sizeof(timerText), "Time: %d s", game->timer.remaining);
    ui_draw_text(ui, timerText, 400, 20, cyan);

    SDL_RenderPresent(ui->renderer);
}

void ui_render_results(UIContext *ui, struct GameState *game)
{
    SDL_SetRenderDrawColor(ui->renderer, 0, 200, 100, 255);
    SDL_RenderClear(ui->renderer);

    ui_draw_text(ui, "Game Over!", 320, 250);

    SDL_RenderPresent(ui->renderer);
}

void ui_cleanup(UIContext *ui)
{
    if (ui->font)
        TTF_CloseFont(ui->font);
    if (ui->renderer)
        SDL_DestroyRenderer(ui->renderer);
    if (ui->window)
        SDL_DestroyWindow(ui->window);
    TTF_Quit();
    SDL_Quit();
}
void ui_render_game_over(UIContext *ui, struct GameState *game)
{
    SDL_Rect scoreBox = {40, 15, 150, 40};
    SDL_SetRenderDrawColor(ui->renderer, 0, 0, 0, 100); // semi-transparent black
    SDL_RenderFillRect(ui->renderer, &scoreBox);
    SDL_RenderClear(ui->renderer);

    char finalScore[64];
    snprintf(finalScore, sizeof(finalScore), "Final Score: %d", game->stats.correct);

    char accuracy[64];
    snprintf(accuracy, sizeof(accuracy), "Accuracy: %.1f%%", game->stats.accuracy);

    ui_draw_text(ui, "Game Over!", 300, 200);
    ui_draw_text(ui, finalScore, 300, 250);
    ui_draw_text(ui, accuracy, 300, 300);
    ui_draw_text(ui, "Press ESC or Close Window to Exit", 180, 380);
    ui_draw_text(ui, "Press ENTER to Restart or ESC to Exit", 150, 420);


    SDL_RenderPresent(ui->renderer);
}
