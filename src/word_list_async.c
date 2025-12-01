#include "word_list_async.h"
#include "word_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Background thread function that loads the word list.
 */
static void *word_list_load_thread_func(void *arg)
{
    WordListAsync *async = (WordListAsync *)arg;

    // Load the word list (this is the blocking I/O operation)
    int result = word_list_load(&async->list, async->filename);

    // Update state atomically
    pthread_mutex_lock(&async->lock);
    async->success = result;
    async->loading = 0;  // Mark as done
    pthread_mutex_unlock(&async->lock);

    return NULL;
}

int word_list_async_start_load(WordListAsync *async, const char *filename)
{
    // Initialize the async loader
    memset(async, 0, sizeof(WordListAsync));
    async->filename = filename;
    async->loading = 1;
    async->success = 0;
    async->quit = 0;

    // Initialize the word list
    async->list.words = NULL;
    async->list.count = 0;

    // Initialize mutex
    if (pthread_mutex_init(&async->lock, NULL) != 0) {
        fprintf(stderr, "Failed to initialize word list mutex.\n");
        return 0;
    }

    // Start the background loading thread
    if (pthread_create(&async->load_thread, NULL, word_list_load_thread_func, async) != 0) {
        fprintf(stderr, "Failed to create word list loading thread.\n");
        pthread_mutex_destroy(&async->lock);
        return 0;
    }

    return 1;
}

int word_list_async_is_ready(WordListAsync *async)
{
    pthread_mutex_lock(&async->lock);
    int ready = !async->loading;  // Ready when not loading
    pthread_mutex_unlock(&async->lock);
    return ready;
}

int word_list_async_get_result(WordListAsync *async)
{
    pthread_mutex_lock(&async->lock);
    int result = async->success;
    pthread_mutex_unlock(&async->lock);
    return result;
}

int word_list_async_wait(WordListAsync *async)
{
    // Wait for the thread to complete
    if (async->load_thread) {
        pthread_join(async->load_thread, NULL);
    }

    // Get the result
    return word_list_async_get_result(async);
}

void word_list_async_cleanup(WordListAsync *async)
{
    // Signal quit (if thread is still running)
    pthread_mutex_lock(&async->lock);
    async->quit = 1;
    pthread_mutex_unlock(&async->lock);

    // Wait for thread to finish
    if (async->load_thread) {
        pthread_join(async->load_thread, NULL);
    }

    // Free the word list
    word_list_free(&async->list);

    // Destroy mutex
    pthread_mutex_destroy(&async->lock);
}

WordList *word_list_async_get_list(WordListAsync *async)
{
    pthread_mutex_lock(&async->lock);
    WordList *list = NULL;
    if (!async->loading && async->success) {
        list = &async->list;
    }
    pthread_mutex_unlock(&async->lock);
    return list;
}

