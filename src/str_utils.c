#include "str_utils.h"

/**
 * Removes all spaces from a string in-place.
 * Modifies the original string by shifting characters.
 * 
 * @param s The string to modify (must be mutable)
 */
void remove_spaces(char *s) {
    int i = 0, j = 0;
    while (s[i]) {
        if (s[i] != ' ') {
            s[j++] = s[i];
        }
        i++;
    }
    s[j] = '\0';
}

/**
 * Converts a string to lowercase in-place.
 * Only affects ASCII uppercase letters (A-Z).
 * 
 * @param s The string to convert to lowercase (must be mutable)
 */
void tolower_str(char *s) {
    for (int i = 0; s[i]; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] + ('a' - 'A');
        }
    }
}