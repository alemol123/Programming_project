#ifndef GAME_H
#define GAME_H
#include "word_list.h"
#include "timer.h"
#include "stats.h"
#include "input.h"
#include "ui_sdl.h"
typedef struct {
    WordList words;
    Timer timer;
    Stats stats;
    const char *current_word;
    int is_running;
    int quit;
} GameState;
void game_init(GameState *game, const char *filepath);
void game_start(GameState *game);
void game_reset(GameState *game);
#endif