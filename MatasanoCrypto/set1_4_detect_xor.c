/* Set 1. Challenge 4. Reads a file with hex strings separated by new lines.
 * Determines which hex strings may have been XOR'd with a byte character.
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "set1_utils.h"

#define ENGLISH_THRESHOLD 10
#define MAX_BUFF 1024


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

/* Performs a XOR cipher with every byte on line. Stores the best English
 * sentence in decode. Returns the score of this sentence.
 */
static double best_xor(char *line, char *best)
{
    int len = strlen(line);
    char *decoded;
    if ((decoded = malloc(len + 1)) == NULL) exit(EXIT_FAILURE);

    strncpy(decoded, line, len + 1);

    // Try to decode with every byte
    double best_score = 0;
    for (int i = 0; i < 255; i++) {
        strncpy(decoded, line, len + 1);

        char *r = xor_decode(decoded, i, len);
        if (!r) exit(EXIT_FAILURE);

        double score = english_score(decoded);
        if (score > best_score) {
            best_score = score;
            strncpy(best, decoded, (len / 2) + 1);
        }
    }

    free(decoded);
    return best_score;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "detect_xor [FILE]\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    if (!infile) {
        fprintf(stderr, "Failed to open %s: %s\n", argv[1], strerror(errno));
        return errno;
    }

    char *input = malloc(sizeof(char) * MAX_BUFF);
    char *best_decode = malloc(sizeof(char) * MAX_BUFF);
    while (get_line(infile, NULL, input, MAX_BUFF) == 0) {
        double score = best_xor(input, best_decode);
        if (score > ENGLISH_THRESHOLD) {
            fprintf(stdout, "%s -> %s\n", input, best_decode);
        }
    }

    free(input);
    free(best_decode);
    fclose(infile);
    return 0;
}
