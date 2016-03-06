#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hex_utils.h"

#define TEST_STRING1 "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

/* XORs each character in encoded with byte. Returns an array of the decoded
 * string that must be free'd by the user.
 */
char *xor_decode(char *encoded, char byte, int len)
{
    char *decoded;
    if ((decoded= malloc(sizeof(char) * (len + 1))) == NULL)
        return NULL;

    strcpy(decoded, encoded);
    chars_to_hex(decoded, len);
    for (int i = 0; i < len; i++)
        decoded[i] = decoded[i] ^ byte;

    return decoded;
}

int main(int argc, char *argv[])
{
    // Try to decode with every character
    for (int i = 0; i < 255; i++) {
        char *decoded = xor_decode(TEST_STRING1, (char)i, strlen(TEST_STRING1));
        printf("%s\n\n", decoded);

        // TODO: Perform frequency analysis to determine English phrase.
        // I'm not entirely sure what must be decoded.
        free(decoded);
    }

    return 0;
}
