#include "word_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//reads words from the file and dynamically allocates memory to store them in the structure
int word_list_load(WordList *list, const char *filename)
{
    //error handling for opening file in read mode
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open words file");
        return 0;
    }

    list->count = 0;
    list->words = NULL;
    char buffer[128];
    //loop through the file word by word
    while (fscanf(file, "%127s", buffer) == 1) {
        //resize array of pointers to put one more word
        char **temp = realloc(list->words, (list->count + 1) * sizeof(char *));
        if (!temp) {
            perror("Memory allocation failed");
            fclose(file);
            return 0;
        }
        list->words = temp;//update pointer
        //allocate memory for the word string (consider \0)
        list->words[list->count] = malloc(strlen(buffer) + 1);
        //error handling
        if (!list->words[list->count]) {
            perror("Memory allocation failed");
            fclose(file);
            return 0;
        }
        strcpy(list->words[list->count], buffer);
        list->count++;
    }

    fclose(file);
    srand((unsigned int)time(NULL));
    return list->count > 0;
}
//selects word from the loaded list using random
const char *word_list_get_random(WordList *list)
{
    if (list->count == 0) return "";
    int index = rand() % list->count;
    return list->words[index];
}
//freeing all dyamically allocated memory 
void word_list_free(WordList *list)
{
    for (int i = 0; i < list->count; i++) {
        free(list->words[i]);
    }
    free(list->words);
    list->words = NULL;
    list->count = 0;
}
