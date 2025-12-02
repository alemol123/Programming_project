#include "game.h"
#include <stdio.h>
//main entry point for the typing game
int main(int argc, char *argv[])
{
    //path to the words list
    const char *words_path = "assets/words.txt";
    GameState game;//declaring
    //initializing; setting up the game and error handling
    if (!game_init(&game, words_path)) {
        fprintf(stderr, "Error: failed to initialize game.\n");
        return 1;
    }

    printf("Typing Race started! (Press the window close button to quit)\n");
    //entering the main game loop
    game_start(&game);
    //clean allocated resources
    game_cleanup(&game);

    printf("Game exited cleanly.\n");
    return 0;
}
