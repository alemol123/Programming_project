/**
 * @file game.c
 * @brief High-level game control logic for the Typing Race game.
 *
 * This module coordinates:
 *  - Word list loading and random selection.
 *  - Timer setup and timer thread start.
 *  - Stats initialization and updates.
 *  - SDL2 / UI initialization and the main event loop.
 */

#include "game.h"
#include "utils.h"
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/**
 * @brief Initialize the GameState structure.
 *
 * Responsibilities:
 *  - Initialize the random seed (for random word selection).
 *  - Load the word list from the given file path into game->words.
 *  - Reset stats (score, counters, accuracy).
 *  - Initialize the timer with a default duration (or value passed from outside).
 *  - Set an initial current_word from the list.
 *  - Prepare any flags (is_running, quit) with default values.
 *
 * This function DOES NOT start the timer thread or SDL loop; it only prepares data.
 *
 * @param game Pointer to a GameState instance to initialize.
 * @param filepath Path to the word list file (e.g. "assets/words.txt").
 */
void game_init(GameState *game, const char *filepath)
{
    /* TODO:
     *  - Seed the random number generator.
     *  - Load words with word_list_load(&game->words, filepath).
     *  - Initialize and reset stats.
     *  - Initialize timer with a chosen duration.
     *  - Pick an initial random word for game->current_word.
     *  - Set game->is_running = 0 and game->quit = 0 (or similar defaults).
     */
}

/**
 * @brief Start the Typing Race game main loop.
 *
 * Responsibilities:
 *  - Initialize SDL2 and the UI (create window, renderer, etc.).
 *  - Start the timer thread so that the countdown runs in the background.
 *  - Enter the SDL event loop:
 *      * Poll events (keyboard input, quit events, etc.).
 *      * Forward keyboard events to the input module.
 *      * When the user validates a word (e.g. presses Enter), compare it against
 *        game->current_word and update stats (correct / total, score).
 *      * Choose a new random word when the user finishes one.
 *      * Re-render the UI each frame (current word, user input, time left, score).
 *  - Exit the loop when:
 *      * The timer reaches zero, or
 *      * The user requests to quit (e.g. closes the window).
 *  - Join the timer thread and clean up SDL resources.
 *
 * @param game Pointer to an initialized GameState.
 */
void game_start(GameState *game)
{
    /* TODO:
     *  - Create a UIContext instance and call ui_init().
     *  - Start the timer thread using pthread_create().
     *  - Create a CurrentInput instance to track what the user types.
     *  - While the game is running:
     *      · Poll SDL events.
     *      · Pass keyboard events to input_handle_event().
     *      · When the user finishes a word, update stats and pick a new one.
     *      · Call ui_render_game(&ui, game, &input).
     *  - After the loop, show final results via ui_render_results().
     *  - Join the timer thread and call ui_cleanup().
     */
}

/**
 * @brief Reset the game state to start a new round without exiting the program.
 *
 * Responsibilities:
 *  - Reset stats (score, counters, accuracy) to zero.
 *  - Reset timer values (remaining time back to full duration).
 *  - Pick a new starting word.
 *  - Clear any flags related to game end (set is_running appropriately).
 *
 * This function is optional depending on whether you support restarting the game.
 *
 * @param game Pointer to GameState to reset.
 */
void game_reset(GameState *game)
{
    /* TODO:
     *  - Reset stats via stats_reset(&game->stats).
     *  - Reset timer values.
     *  - Pick a new current_word.
     *  - Set flags such as is_running / quit to their default values.
     */
}
