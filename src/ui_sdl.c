// ui_sdl.c
#include "ui_sdl.h"
#include "game.h"
#include "input.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <math.h>


void ui_draw_text(UIContext *ui,
                         const char *text,
                         int x,
                         int y,
                         SDL_Color color)
{
    if (!text || text[0] == '\0') {
        return;
    }

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

    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;

    SDL_RenderCopy(ui->renderer, texture, NULL, &dest);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// center text horizontally on an 800-px wide window
static void ui_draw_text_centered(UIContext *ui,
                                  const char *text,
                                  int y,
                                  SDL_Color color)
{
    if (!text || text[0] == '\0') {
        return;
    }

    int w = 0, h = 0;
    if (TTF_SizeText(ui->font, text, &w, &h) != 0) {
        w = 0;
    }

    int x = (800 - w) / 2;
    ui_draw_text(ui, text, x, y, color);
}

// circular dot-style timer (no SDL2_gfx needed)
static void ui_draw_timer_ring(UIContext *ui,
                               int cx,
                               int cy,
                               int radius,
                               int remaining,
                               int duration)
{
    if (duration <= 0) {
        return;
    }

    int segments = duration;
    if (segments > 60) {
        segments = 60;  // avoid too many dots
    }

    int i;
    for (i = 0; i < segments; ++i) {
        float t = 1.0f - ((float)i / (float)segments);
        float angle = (float)(t * 2.0 * M_PI - M_PI / 2.0); // start at top
        int px = cx + (int)(cos(angle) * radius);
        int py = cy + (int)(sin(angle) * radius);

        int active = (i < remaining);

        if (active) {
            SDL_SetRenderDrawColor(ui->renderer, 220, 0, 0, 255); // red
        } else {
            SDL_SetRenderDrawColor(ui->renderer, 200, 200, 200, 255); // light gray
        }

        SDL_Rect dot;
        dot.x = px - 2;
        dot.y = py - 2;
        dot.w = 4;
        dot.h = 4;
        SDL_RenderFillRect(ui->renderer, &dot);
    }

    // timer text in the center
    char buf[16];
    SDL_Color red = {220, 0, 0, 255};
    snprintf(buf, sizeof(buf), "%d", remaining);
    ui_draw_text(ui, buf, cx - 15, cy - 25, red);
    ui_draw_text(ui, "sec", cx - 18, cy + 2, red);
}

// --------------- public API -----------------------

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

    // Use your condensed bold font
    ui->font = TTF_OpenFont("assets/Roboto_SemiCondensed-Black.ttf", 32);
    if (!ui->font) {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(ui->renderer);
        SDL_DestroyWindow(ui->window);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    return 1;
}

void ui_render_game(UIContext *ui, struct GameState *game, CurrentInput *input)
{
    // Background: #EDE8D0
    SDL_SetRenderDrawColor(ui->renderer, 237, 232, 208, 255);
    SDL_RenderClear(ui->renderer);

    SDL_Color black     = {0, 0, 0, 255};
    SDL_Color lightGrey = {120, 120, 120, 255};

    // ----- Score box (white with black border) -----

    SDL_Rect scoreBox;
    scoreBox.x = 40;
    scoreBox.y = 40;
    scoreBox.w = 200;
    scoreBox.h = 60;

    // fill
    SDL_SetRenderDrawColor(ui->renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(ui->renderer, &scoreBox);
    // border
    SDL_SetRenderDrawColor(ui->renderer, 0, 0, 0, 255);
    for (int i = 0; i < 4; i++) {  
        SDL_Rect outline = {
            scoreBox.x - i,
            scoreBox.y - i,
            scoreBox.w + i * 2,
            scoreBox.h + i * 2
        };
        SDL_RenderDrawRect(ui->renderer, &outline);
    }
    ui_draw_text(ui, "Score:", scoreBox.x + 15, scoreBox.y + 15, black);

    char scoreBuf[32];
    snprintf(scoreBuf, sizeof(scoreBuf), "%d", game->stats.correct);
    ui_draw_text(ui, scoreBuf, scoreBox.x + 120, scoreBox.y + 15, black);

    // ----- Circular timer (top right) -----
    ui_draw_timer_ring(ui,
                       700,         // center x
                       90,          // center y
                       45,          // radius
                       game->timer.remaining,
                       game->timer.duration);

    // ----- Centered "Write the word:" and word -----
    ui_draw_text_centered(ui, "Write the word:", 210, black);
    ui_draw_text_centered(ui, game->currentWord, 260, black);

    // ----- Input label + user input (lighter) -----
    ui_draw_text(ui, "Your input:", 80, 360, lightGrey);
    ui_draw_text(ui, input->buffer, 240, 360, lightGrey);

    SDL_RenderPresent(ui->renderer);
}

void ui_render_game_over(UIContext *ui, struct GameState *game)
{
    // Same background as game screen
    SDL_SetRenderDrawColor(ui->renderer, 237, 232, 208, 255);
    SDL_RenderClear(ui->renderer);

    SDL_Color black = {0, 0, 0, 255};

    ui_draw_text_centered(ui, "Game Over!", 180, black);

    char finalScore[64];
    snprintf(finalScore, sizeof(finalScore), "Final Score: %d", game->stats.correct);
    ui_draw_text_centered(ui, finalScore, 230, black);

    char accuracy[64];
    snprintf(accuracy, sizeof(accuracy), "Accuracy: %.1f%%", game->stats.accuracy);
    ui_draw_text_centered(ui, accuracy, 270, black);

    ui_draw_text_centered(ui,
                          "Press ENTER to Restart or ESC to Exit",
                          340,
                          black);

    SDL_RenderPresent(ui->renderer);
}

// If some code still calls ui_render_results, keep a simple wrapper.
void ui_render_results(UIContext *ui, struct GameState *game)
{
    ui_render_game_over(ui, game);
}

void ui_cleanup(UIContext *ui)
{
    if (ui->font) {
        TTF_CloseFont(ui->font);
        ui->font = NULL;
    }
    if (ui->renderer) {
        SDL_DestroyRenderer(ui->renderer);
        ui->renderer = NULL;
    }
    if (ui->window) {
        SDL_DestroyWindow(ui->window);
        ui->window = NULL;
    }

    TTF_Quit();
    SDL_Quit();
}
