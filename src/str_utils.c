#include "str_utils.h"

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

void tolower_str(char *s) {
    for (int i = 0; s[i]; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] + ('a' - 'A');
        }
    }
}