#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("========================================\n");
    printf(" RUNNING ALL TESTS\n");
    printf("========================================\n");

    printf("\n--- test_words ---\n");
    system("./test_words");

    printf("\n--- test_game_logic ---\n");
    system("./test_game_logic");

    printf("\n--- test_stats ---\n");
    system("./test_stats");

    printf("\n--- test_timer ---\n");
    system("./test_timer");

    printf("\n========================================\n");
    printf(" ALL TESTS COMPLETED\n");
    printf("========================================\n");

    return 0;
}
