/**
 * @file str_utils.h
 * @brief String manipulation utilities
 * 
 * Provides helper functions for common string operations
 * such as removing spaces and converting to lowercase.
 */

#ifndef STR_UTILS_H
#define STR_UTILS_H

/**
 * Removes all spaces from a string in-place.
 * Modifies the original string by shifting characters.
 * 
 * @param s The string to modify (must be mutable)
 */
void remove_spaces(char *s);

/**
 * Converts a string to lowercase in-place.
 * Only affects ASCII uppercase letters (A-Z).
 * 
 * @param s The string to convert to lowercase (must be mutable)
 */
void tolower_str(char *s);

#endif // STR_UTILS_H