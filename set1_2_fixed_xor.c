/* Set 1. Challenge 2. Applies the XOR operation on two strings given as
 * command arguments.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hex_utils.h"

#define TEST_STRING0 "1c0111001f010100061a024b53535009181c"
#define TEST_STRING1 "686974207468652062756c6c277320657965"

/* Takes two hex strings and XORs their bytes.
 *
 * len: length of the strings excluding the null byte.
 *
 * Returns a pointer to str0 or NULL on failure
 */
char *fixed_xor(char *str0, char *str1, int len)
{
    char *r = chars_to_hex(str0, len);
    if (!r) return NULL;

    r = chars_to_hex(str1, len);
    if (!r) return NULL;

    for (int i = 0; i < len / 2; i++)
        str0[i] ^= str1[i];

    r = hex_to_chars(str0, len / 2);
    if (!r) return NULL;

    return str0;
}

int main(int argc, char *argv[])
{
    if (argc == 3) {
        char *result = fixed_xor(argv[1], argv[2], strlen(argv[1]));
        fprintf(stdout, "%s\n", result);
    } else {
        // Use default values
        int len = strlen(TEST_STRING0);
        char *str0, *str1;
        if ((str0 = malloc(len + 1)) == NULL) return 1;
        if ((str1 = malloc(len + 1)) == NULL) return 1;

        strncpy(str0, TEST_STRING0, len + 1);
        strncpy(str1, TEST_STRING1, len + 1);

        fixed_xor(str0, str1, len);
        fprintf(stdout, "%s\n", str0);

        free(str0);
        free(str1);
    }
    return 0;
}
