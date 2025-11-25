#include "game.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    const char *words_path = "assets/words.txt";
    GameState game;

    if (!game_init(&game, words_path)) {
        fprintf(stderr, "Error: failed to initialize game.\n");
        return 1;
    }

    printf("Typing Race started! (Press the window close button to quit)\n");

    game_start(&game);

    game_cleanup(&game);

    printf("Game exited cleanly.\n");
    return 0;
}
