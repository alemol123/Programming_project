/**
 * @file input.c
 * @brief Input handling logic for the Typing Race game.
 *
 * This module is responsible for:
 *  - Tracking what the user is currently typing in a small buffer.
 *  - Handling SDL2 keyboard events (letters, backspace, enter, etc.).
 *  - Comparing the typed word with the target word.
 */

#include "input.h"
#include <string.h>

/**
 * @brief Reset the CurrentInput buffer to an empty string.
 *
 * Responsibilities:
 *  - Set all characters in buffer to '\0'.
 *  - Reset length to 0.
 *
 * @param in Pointer to a CurrentInput structure.
 */
void input_reset(CurrentInput *in)
{
    /* TODO:
     *  - Clear the buffer using memset.
     *  - Set length to 0.
     */
}

/**
 * @brief Handle a single SDL2 keyboard event and update the input buffer.
 *
 * Responsibilities:
 *  - If a normal character key is pressed (letter, number, etc.), append it
 *    to the buffer as long as there is space.
 *  - If Backspace is pressed, remove the last character (length--).
 *  - If Enter is pressed, the game logic (outside this function) can interpret
 *    that as: "user finished typing a word".
 *
 * This function DOES NOT compare the word or update stats directly; it only
 * maintains the user's current input.
 *
 * @param in Pointer to the CurrentInput structure to update.
 * @param e  Pointer to an SDL_Event representing a keyboard event.
 */
void input_handle_event(CurrentInput *in, SDL_Event *e)
{
    /* TODO:
     *  - Check e->type == SDL_KEYDOWN.
     *  - Inspect e->key.keysym.sym to detect which key was pressed.
     *  - Update the buffer and length accordingly.
     */
}

/**
 * @brief Check if the typed input matches the target word.
 *
 * Responsibilities:
 *  - Perform a string comparison between in->buffer and target.
 *  - Return 1 if they match, 0 otherwise.
 *
 * This function DOES NOT modify stats; it only answers the question
 * "Is the user input equal to the target word?".
 *
 * @param in Pointer to the CurrentInput to evaluate.
 * @param target Null-terminated C string representing the target word.
 * @return int 1 if equal, 0 otherwise.
 */
int input_check_word(CurrentInput *in, const char *target)
{
    /* TODO:
     *  - Use strcmp() to compare in->buffer and target.
     */
    return 0;
}
