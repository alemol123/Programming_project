#include "game.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {
    printf("Running test_game_logic...\n");

    GameState game;

    int ok = game_init(&game, "assets/words.txt");
    assert(ok == 1);

    // Check word list loaded
    assert(game.words != NULL);
    assert(game.words->count > 0);

    // Stats initialized correctly
    assert(game.stats.score == 0);
    assert(game.stats.correct == 0);
    assert(game.stats.total == 0);
    assert(game.stats.accuracy == 0.0f);

    // Input empty
    assert(game.input.length == 0);
    assert(strlen(game.input.buffer) == 0);

    // Timer initialized
    assert(game.timer.duration > 0);
    assert(game.timer.remaining > 0);

    // Flag running state
    assert(game.running == 1);

    game_cleanup(&game);

    printf("test_game_logic passed.\n");
    return 0;
}
