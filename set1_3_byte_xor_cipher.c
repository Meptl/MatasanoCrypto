/* Set 1. Challenge 3. Converts a hex string given in stdin and XORs it with
 * all possible byte values. Returns the result that most closely resembles
 * English. This is done simply by letter frequency analysis.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set1_utils.h"

#define MAX_BUFF 256

/* XORs every 8 bit segment in encoded with byte.
 * Returns an array of the decoded bytes that must be free'd by the user.
 *
 * len: length of the string excluding the null byte.
 */
static char *xor_decode(char *encoded, char byte, int len)
{
    int r = chars_to_hex(encoded, len);
    if (r == -1) return NULL;

    for (int i = 0; i < len / 2; i++)
        encoded[i] = (encoded[i] ^ byte) & 0xff;

    encoded[len / 2] = '\0';
    return encoded;
}

int main(int argc, char *argv[])
{
    char *input = malloc(sizeof(char) * MAX_BUFF);

    get_line(stdin, NULL, input, MAX_BUFF);
    int len = strlen(input);

    char *decoded, *best;
    if ((decoded = malloc(len + 1)) == NULL) return 1;
    if ((best = malloc(len + 1)) == NULL) return 1;

    strncpy(decoded, input, len + 1);
    strncpy(best, input, len + 1);

    // Try to decode with every byte
    double best_score = 0;
    int byte = 0;
    for (int i = 0; i < 255; i++) {
        strncpy(decoded, input, len + 1);

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


    free(input);
    free(decoded);
    free(best);
    return 0;
}
