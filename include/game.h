#ifndef GAME_H
#define GAME_H

#include "input.h"      // Must come first
#include "stats.h"
#include "timer.h"
#include "word_list.h"
#include "ui_sdl.h"     // Must come after the full type definitions

typedef struct GameState {
    UIContext ui;
    struct WordList *words;
    CurrentInput input;
    Stats stats;
    Timer timer;
    char currentWord[64];
    int running;
} GameState;

int game_init(GameState *game, const char *words_path);
void game_start(GameState *game);
void game_cleanup(GameState *game);

#endif
