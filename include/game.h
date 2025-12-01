#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_list.h"
#include "input.h"
#include "stats.h"
#include "timer.h"
#include "ui_sdl.h"   // <-- bring in UIContext definition

typedef struct GameState {
    UIContext ui;          // full, known type now
    WordList *words;
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
