#include "stats.h"

void stats_reset(Stats *s)
{
    s->score = 0;
    s->correct = 0;
    s->total = 0;
    s->accuracy = 0.0f;
}

void stats_update_accuracy(Stats *s)
{
    if (s->total == 0)
        s->accuracy = 0.0f;
    else
        s->accuracy = ((float)s->correct / (float)s->total) * 100.0f;
}
