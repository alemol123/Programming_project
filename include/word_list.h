#ifndef WORD_LIST_H
#define WORD_LIST_H
typedef struct {
    char **words;
    int count;
} WordList;
int word_list_load(WordList *list, const char *filename);
const char *word_list_get_random(WordList *list);
void word_list_free(WordList *list);
#endif