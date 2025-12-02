#ifndef WORD_LIST_ASYNC_H
#define WORD_LIST_ASYNC_H

#include "word_list.h"
#include <pthread.h>

typedef struct {
    WordList list;              // The actual word list
    const char *filename;       // File to load from
    pthread_t load_thread;      // Background loading thread
    pthread_mutex_t lock;       // Protects loading state
    int loading;                // 1 = still loading, 0 = done
    int success;                // 1 = loaded successfully, 0 = failed
    int quit;                   // 1 = cancel loading
} WordListAsync;

int word_list_async_start_load(WordListAsync *async, const char *filename);
int word_list_async_is_ready(WordListAsync *async);
int word_list_async_get_result(WordListAsync *async);
int word_list_async_wait(WordListAsync *async);
void word_list_async_cleanup(WordListAsync *async);
WordList *word_list_async_get_list(WordListAsync *async);

#endif

