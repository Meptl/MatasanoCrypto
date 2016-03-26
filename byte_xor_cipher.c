#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hex_utils.h"

#define TEST_STRING1 "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

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
    char *mystery, *decoded;
    if ((mystery = malloc(len + 1)) == NULL) return 1;
    if ((decoded = malloc(len + 1)) == NULL) return 1;

    strncpy(mystery, TEST_STRING1, len + 1);
    strncpy(decoded, TEST_STRING1, len + 1);

    // Try to decode with every byte
    for (int i = 0; i < 255; i++) {
        strncpy(decoded, mystery, len + 1);

        char *r = xor_decode(decoded, i, len);
        if (!r) return 2;

        printf("%s\n", decoded);

        // TODO: Perform frequency analysis to determine English phrase.
    }

    free(mystery);
    free(decoded);
    return 0;
}
