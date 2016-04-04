/* Set 1. Challenge 3. Converts a hex string defined below and XORs it with
 * all possible byte values. Returns the result that most closely resembles
 * English. This is done simply by letter frequency analysis.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set1_utils.h"

#define TEST_STRING1 "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

/* XORs every 8 bit segment in encoded with byte.
 * Returns an array of the decoded bytes that must be free'd by the user.
 *
 * len: length of the string excluding the null byte.
 */
static char *xor_decode(char *encoded, char byte, int len)
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
    printf("Score of %f\n", best_score);
    printf("XOR encoded with %d byte\n", byte);


    free(original);
    free(decoded);
    free(best);
    return 0;
}
