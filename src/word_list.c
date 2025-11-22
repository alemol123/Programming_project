/**
 * @file word_list.c
 * @brief Word list loading and random selection logic.
 *
 * This module is responsible for:
 *  - Loading words from a plaintext file into dynamic memory.
 *  - Storing them in a WordList structure (array of strings).
 *  - Providing a function to get a random word from the list.
 *  - Freeing the dynamic memory when it is no longer needed.
 */

#include "word_list.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Load words from a file into a WordList structure.
 *
 * File format:
 *  - One word per line.
 *  - Lines are expected to be reasonably short (e.g., < 64 chars).
 *
 * Responsibilities:
 *  - Open the file in read mode.
 *  - Count how many lines/words the file contains.
 *  - Allocate memory for an array of char* with that size.
 *  - Read each line, strip the newline, and copy it into the array.
 *  - Store the resulting array and count into the WordList parameter.
 *
 * @param list Pointer to a WordList to fill.
 * @param filename Path to the words file (e.g. "assets/words.txt").
 * @return int 1 on success, 0 on failure (file error or memory allocation failure).
 */
int word_list_load(WordList *list, const char *filename)
{
    /* TODO:
     *  - Implement the steps described above.
     *  - On error, set list->words = NULL and list->count = 0.
     */
    return 0;
}

/**
 * @brief Get a random word from the WordList.
 *
 * Responsibilities:
 *  - If the list is empty (count <= 0), return NULL.
 *  - Otherwise, pick an index in [0, count-1] using a random function
 *    and return the corresponding word.
 *
 * This function DOES NOT allocate new memory; it returns a pointer to
 * existing strings stored in the WordList.
 *
 * @param list Pointer to a valid WordList.
 * @return const char* Pointer to a random word, or NULL if list is empty.
 */
const char *word_list_get_random(WordList *list)
{
    /* TODO:
     *  - Use utils_rand_int(0, list->count - 1) to select an index.
     *  - Return list->words[index].
     */
    return NULL;
}

/**
 * @brief Free the dynamic memory used by a WordList.
 *
 * Responsibilities:
 *  - Free each string in the array.
 *  - Free the array of pointers.
 *  - Set count to 0 and words to NULL for safety.
 *
 * @param list Pointer to a WordList whose resources should be released.
 */
void word_list_free(WordList *list)
{
    /* TODO:
     *  - Loop over list->words and free each one.
     *  - Free the list->words array itself.
     *  - Set list->words = NULL and list->count = 0.
     */
}
