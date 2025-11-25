#include "game.h"
#include "word_list.h"
#include "input.h"
#include "stats.h"
#include "timer.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int game_init(GameState *game, const char *words_path)
{
    if (!ui_init(&game->ui)) {
        fprintf(stderr, "Failed to initialize UI.\n");
        return 0;
    }

    // Load the word list
    game->words = malloc(sizeof(WordList));
    if (!word_list_load(game->words, words_path)) {
        fprintf(stderr, "Error: Failed to load words from %s\n", words_path);
        return 0;
    }

    // Initialize input, stats, and timer
    input_reset(&game->input);
    stats_reset(&game->stats);
    timer_init(&game->timer, 60); // 60-second timer

    // Pick the first random word
    const char *first = word_list_get_random(game->words);
    strncpy(game->currentWord, first, sizeof(game->currentWord) - 1);
    game->currentWord[sizeof(game->currentWord) - 1] = '\0';

    game->running = 1;
    return 1;
}

void game_start(GameState *game)
{
    SDL_Event e;
    SDL_StartTextInput();

    while (game->running) {
        timer_update(&game->timer);

        // Stop when time is up
        if (!game->timer.running) {
            game->running = 0;
            break;
        }

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                game->running = 0;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    game->running = 0;
                } else if (e.key.keysym.sym == SDLK_RETURN) {
                    // ✅ Submit the word on Enter
                    if (input_check_word(&game->input, game->currentWord)) {
                        game->stats.correct++;
                        game->stats.score++; // only count correct words in score
                    }

                    game->stats.total++; // count all attempts
                    stats_update_accuracy(&game->stats);

                    // Get next word regardless of correctness
                    const char *newWord = word_list_get_random(game->words);
                    strncpy(game->currentWord, newWord, sizeof(game->currentWord) - 1);
                    input_reset(&game->input);
                }
            } else {
                input_handle_event(&game->input, &e);
            }
        }

        ui_render_game(&game->ui, game, &game->input);
        SDL_Delay(16); // ~60 FPS
    }

    // Game Over screen
    ui_render_game_over(&game->ui, game);

    // Wait for user action (ESC to exit, ENTER to restart)
    int waiting = 1;
    while (waiting) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                waiting = 0;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    waiting = 0;
                } else if (e.key.keysym.sym == SDLK_RETURN) {
                    // Restart
                    input_reset(&game->input);
                    stats_reset(&game->stats);
                    timer_init(&game->timer, 60);
                    const char *newWord = word_list_get_random(game->words);
                    strncpy(game->currentWord, newWord, sizeof(game->currentWord) - 1);
                    game->running = 1;
                    waiting = 0;
                    game_start(game); // restart recursively
                    return;
                }
            }
        }
        SDL_Delay(100);
    }

    SDL_StopTextInput();
}

void game_cleanup(GameState *game)
{
    word_list_free(game->words);
    free(game->words);
    ui_cleanup(&game->ui);
}
