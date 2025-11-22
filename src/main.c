/**
 * @file main.c
 * @brief Entry point of the Typing Race game.
 *
 * This file is responsible for:
 *  - Creating the GameState structure.
 *  - Initializing the game (loading words, setting stats, timer, and UI).
 *  - Starting the main game loop.
 *  - Returning an exit code to the operating system.
 */

#include "game.h"
#include <stdio.h>

/**
 * @brief Program entry point.
 *
 * High-level flow (to be implemented):
 *  1. Optionally parse command line arguments (e.g. custom duration).
 *  2. Initialize a GameState instance.
 *  3. Call game_init() with the path to the words file.
 *  4. If initialization succeeds, call game_start() to run the main loop.
 *  5. When the game finishes, clean any resources (if needed) and return.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return int 0 on success, non‑zero on failure.
 */
int main(int argc, char *argv[])
{
    /* TODO:
     *  - Create a GameState variable.
     *  - Choose the words file path (e.g. "assets/words.txt").
     *  - Call game_init(&game, path).
     *  - Handle errors (e.g. failed to load words or SDL error).
     *  - Call game_start(&game).
     *  - Return 0 on success.
     */
    return 0;
}
