#ifndef WORD_LIST_ASYNC_H
#define WORD_LIST_ASYNC_H

#include "word_list.h"
#include <pthread.h>

/**
 * @brief Asynchronous word list loader with thread-safe operations.
 *
 * This allows loading words from a file in a background thread
 * while the main thread can continue rendering a loading screen.
 */
typedef struct {
    WordList list;              // The actual word list
    const char *filename;       // File to load from
    pthread_t load_thread;      // Background loading thread
    pthread_mutex_t lock;       // Protects loading state
    int loading;                // 1 = still loading, 0 = done
    int success;                // 1 = loaded successfully, 0 = failed
    int quit;                   // 1 = cancel loading
} WordListAsync;

/**
 * @brief Start loading words asynchronously in a background thread.
 *
 * @param async The async loader to initialize
 * @param filename Path to the words file
 * @return 1 on success (thread started), 0 on failure
 */
int word_list_async_start_load(WordListAsync *async, const char *filename);

/**
 * @brief Check if loading is complete.
 *
 * Thread-safe check. Returns immediately.
 *
 * @param async The async loader
 * @return 1 if loading is complete (success or failure), 0 if still loading
 */
int word_list_async_is_ready(WordListAsync *async);

/**
 * @brief Get the loading result.
 *
 * Must call word_list_async_is_ready() first and ensure it returns 1.
 *
 * @param async The async loader
 * @return 1 if loaded successfully, 0 if failed
 */
int word_list_async_get_result(WordListAsync *async);

/**
 * @brief Wait for loading to complete and get the result.
 *
 * Blocks until loading is done.
 *
 * @param async The async loader
 * @return 1 if loaded successfully, 0 if failed
 */
int word_list_async_wait(WordListAsync *async);

/**
 * @brief Cancel loading and clean up.
 *
 * Waits for the thread to finish, then frees resources.
 *
 * @param async The async loader
 */
void word_list_async_cleanup(WordListAsync *async);

/**
 * @brief Get a pointer to the loaded WordList (thread-safe).
 *
 * Only call this after word_list_async_is_ready() returns 1 and
 * word_list_async_get_result() returns 1.
 *
 * @param async The async loader
 * @return Pointer to the WordList, or NULL if not ready/failed
 */
WordList *word_list_async_get_list(WordListAsync *async);

#endif

