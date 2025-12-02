#include "stats.h"
//resets everything to 0 when starting a new game
void stats_reset(Stats *s)
{
    s->score = 0;//metric for high score
    s->correct = 0;//words typed correctly
    s->total = 0;//all words submitted
    s->accuracy = 0.0f;//percenatge of accuracy
}
//typing accuracy percentage calculation function
void stats_update_accuracy(Stats *s)
{
    if (s->total == 0)
        s->accuracy = 0.0f;
    else
        s->accuracy = ((float)s->correct / (float)s->total) * 100.0f;
}
