#include "word_list_async.h"
#include "word_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// experimental thread 
//function executed by background thread to load the word list
static void *word_list_load_thread_func(void *arg)
{
    //block input output 
    WordListAsync *async = (WordListAsync *)arg;

    
    int result = word_list_load(&async->list, async->filename);

    // Update state atomically
    pthread_mutex_lock(&async->lock);
    async->success = result;
    async->loading = 0; 
    pthread_mutex_unlock(&async->lock);

    return NULL;
}
//asynchronous word list loading process (new thread)
int word_list_async_start_load(WordListAsync *async, const char *filename)
{
    //async starts
    memset(async, 0, sizeof(WordListAsync));
    async->filename = filename;
    async->loading = 1;
    async->success = 0;
    async->quit = 0;

    // initialize the word list structure
    async->list.words = NULL;
    async->list.count = 0;

    // Initialize mutex for the thread sync
    if (pthread_mutex_init(&async->lock, NULL) != 0) {
        fprintf(stderr, "Failed to initialize word list mutex.\n");
        return 0;
    }

    // create and start the background loading thread
    if (pthread_create(&async->load_thread, NULL, word_list_load_thread_func, async) != 0) {
        fprintf(stderr, "Failed to create word list loading thread.\n");
        pthread_mutex_destroy(&async->lock);
        return 0;
    }

    return 1;
}
//checks if background laoding finished 
int word_list_async_is_ready(WordListAsync *async)
{
    //access shared loading flag
    pthread_mutex_lock(&async->lock);
    int ready = !async->loading;  
    pthread_mutex_unlock(&async->lock);
    return ready;
}
//retrieves success status of loading 
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
    return word_list_async_get_result(async);
}

//blocks calling thread until the loading has finished completely
void word_list_async_cleanup(WordListAsync *async)
{
    pthread_mutex_lock(&async->lock);
    async->quit = 1;
    pthread_mutex_unlock(&async->lock);

    // Wait for thread to finish
    if (async->load_thread) {
        pthread_join(async->load_thread, NULL);
    }
    word_list_free(&async->list);
    pthread_mutex_destroy(&async->lock);
}
//cleans thread and synchronization resources and frees the loaded word list data
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

