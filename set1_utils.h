/* Some utility functions for hex, character, and base64 conversions.
 * char is used as a byte datatype
 */

#ifndef _SET1_UTILS_H
#define _SET1_UTILS_H

/* Sanitized getline from given stream.
 */
int get_line(FILE *stream, char *prompt, char *buff, size_t s);

/* Returns a value from 0 to 100 that a sentence is English. Assumes sentence
 * ends with a null character.
 */
double english_score(char *sentence);

/* Receives a number under 64 and returns an integer that would represents it.
 * If called on non-64 digit behavior is undefined.
 */
char num_to_base64(char digit);

/* Receives a character in base64 (in the range A-Za-z0-9+/) and returns its
 * numerical representation.
 */
char base64_to_num(char digit);

/* Modifies the given input. Takes every four base64 characters and converts
 * them into 3 bytes. Each base64 character is 6 bits. Modifies the values in
 * the given char *. The new length of the bytes is len * 3 / 4.
 *
 * Returns the new length of the input or -1.
 */
int base64_decode(char *input, int len);

/* Converts a hex character to a value from 0-15, its numerical interpretation.
 * Returns -1 on failure;
 */
char char_to_hex(char c);

/* Converts a value in from 0 - 15 and represents it as a character.
 */
char hex_to_char(char hex);

/* Converts the hex characters in a given string to a byte array. Modifies the
 * chars array in place. Each hex char is 4 bits, so the size of the returned
 * array is effectively half that of the given array.
 *
 * Returns new length of the output or -1.
 */
int chars_to_hex(char *chars, int len);

/* Converts an array of bytes into a string of hex characters. Because
 * converting from hex to bytes, then back to hex is so common, this function
 * modifies the hex variable beyond the given len. Use alloc_hex_to_chars to
 * receive a new array.
 *
 * Returns new length of the output or -1.
 */
int hex_to_chars(char *hex, int len);

/* Converts an array of bytes into a string of hex characters.
 *
 * Returns a char array that must be free'd by the user or NULL on failure
 */
char *alloc_hex_to_chars(char *hex, int len);

#endif
