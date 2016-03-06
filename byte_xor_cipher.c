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
    char *bytes, *decoded;
    if ((bytes = malloc(len + 1)) == NULL)
        return NULL;
    if ((decoded = malloc(len / 2 + 1)) == NULL)
        return NULL;

    strncpy(bytes, encoded, len + 1);
    //chars_to_hex(bytes, len);

    // Each hex char is 4 bits so take every other data point and merge them
    for (int i = 0; i < len; i += 2)
        bytes[i / 2] = ((bytes[i] << 4) | bytes[i + 1]);

    for (int i = 0; i < len / 2; i++) {
        printf("%d ", bytes[i]);
        decoded[i] = bytes[i] ^ byte;
    }

    decoded[len / 2] = '\0';
    free(bytes);
    return decoded;
}

int is_english(char *sentence, int len)
{
    for (int i = 0; i < len; i++) {
        if ((sentence[i] < 'a' || sentence[i] > 'z') &&
            (sentence[i] < 'A' || sentence[i] > 'Z') &&
            (sentence[i] != '\r' && sentence[i] != '\n' && sentence[i] != ' '))
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    int len = strlen(TEST_STRING1);
    char *decoded = xor_decode(TEST_STRING1, 0, len);
    // Try to decode with every character
    /*
    for (int i = 0; i < 255; i++) {
        char *decoded = xor_decode(TEST_STRING1, i, len);

        //printf("%s\n", decoded);

        // TODO: Perform frequency analysis to determine English phrase.
        // I'm not entirely sure what must be decoded.
        free(decoded);
    }
    */

    return 0;
}
