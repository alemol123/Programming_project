#include "word_list.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {
    printf("Running test_words...\n");

    WordList list;

    int result = word_list_load(&list, "assets/words.txt");
    assert(result > 0);          // SUCCESS = 1
    assert(list.count > 0);     

    const char *word = word_list_get_random(&list);
    assert(word != NULL);
    assert(strlen(word) > 0);    // Make sure it’s not empty

    word_list_free(&list);

    printf("test_words passed.\n");
    return 0;
}
