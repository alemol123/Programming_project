#include "stats.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    printf("Running test_stats...\n");

    Stats s;
    stats_reset(&s);

    // After resetting everything should be zero.
    assert(s.score == 0);
    assert(s.correct == 0);
    assert(s.total == 0);
    assert(s.accuracy == 0.0f);

    // Simulate some game stats.
    s.correct = 3;
    s.total   = 5;
    stats_update_accuracy(&s);

    assert(s.accuracy > 59.0f && s.accuracy < 61.0f);

    printf("test_stats passed.\n");
    return 0;
}
