#ifndef STATS_H
#define STATS_H
typedef struct {
    int score;
    int correct;
    int total;
    float accuracy;
} Stats;
void stats_reset(Stats *s);
void stats_update_accuracy(Stats *s);
#endif