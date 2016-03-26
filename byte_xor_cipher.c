#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hex_utils.h"

#define TEST_STRING1 "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

/* A table of letter frequencies for English. 'a' is index 0.
 * These values roughly add up to 100.
 */
double english_freq[26] = { 8.12, 1.49, 2.78, 4.25, 12.70, 2.23, 2.01, 6.09,
                            6.97, 0.15, 0.77, 4.02, 2.41, 6.75, 7.51, 1.93,
                            0.09, 5.98, 6.33, 9.06, 2.76, 0.98, 2.36, 0.15,
                            1.98, 0.07 };

/* Returns a value from 0 to 100 that a sentence is English. */
double english_score(char *sentence)
{
    double freq[26] = { 0 };
    int chars = 0;
    for (char *s = sentence; *s; s++) {
        char c = *s;
        if (c >= 'A' && c <= 'Z')
            c = c + ('a' - 'A');

        if (c >= 'a' && c <= 'z') {
            chars++;
            freq[c - 'a']++;
        }
    }

    // No letters found
    if (chars == 0)
        return 0;

    // Convert absolute frequencies to relative frequencies in percent
    for (int i = 0; i < 26; i++)
        freq[i] = (freq[i] / chars) * 100;

    // Calculate errors
    double err = 0;
    for (int i = 0; i < 26; i++)
        err += fabs(english_freq[i] - freq[i]);

    if (err > 100)
        err = 100;

    return 100 - err;
}

/* XORs every 8 bit segment in encoded with byte.
 * Returns an array of the decoded bytes that must be free'd by the user.
 *
 * len: length of the string excluding the null byte.
 */
char *xor_decode(char *encoded, char byte, int len)
{
    char *r = chars_to_hex(encoded, len);
    if (!r) return NULL;

    for (int i = 0; i < len / 2; i++)
        encoded[i] = (encoded[i] ^ byte) & 0xff;

    encoded[len / 2] = '\0';
    return encoded;
}

int main(int argc, char *argv[])
{
    int len = strlen(TEST_STRING1);
    char *original, *decoded, *best;
    if ((original = malloc(len + 1)) == NULL) return 1;
    if ((decoded = malloc(len + 1)) == NULL) return 1;
    if ((best = malloc(len + 1)) == NULL) return 1;

    strncpy(original, TEST_STRING1, len + 1);
    strncpy(decoded, TEST_STRING1, len + 1);
    strncpy(best, TEST_STRING1, len + 1);

    // Try to decode with every byte
    double best_score = 0;
    int byte = 0;
    for (int i = 0; i < 255; i++) {
        strncpy(decoded, original, len + 1);

        char *r = xor_decode(decoded, i, len);
        if (!r) return 2;

        double score = english_score(decoded);
        if (score > best_score) {
            byte = i;
            best_score = score;
            strncpy(best, decoded, (len / 2) + 1);
        }
    }

    printf("%s\n", best);
    printf("XOR encoded with %d byte\n", byte);


    free(original);
    free(decoded);
    free(best);
    return 0;
}
