#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hex_con.h"

#define TEST_STRING1 "1c0111001f010100061a024b53535009181c"
#define TEST_STRING2 "686974207468652062756c6c277320657965"
/* Takes two hex strings and XORs their numerical representation and
 * places the values into the out.
 * Returns -1 on error
 */
int fixed_xor(const char *bff1, const char *bff2, char *out, int len)
{
    char *buff1, *buff2;
    if ((buff1 = malloc(len + 1)) == NULL)
        return -1;
    if ((buff2 = malloc(len + 1)) == NULL)
        return -1;

    strcpy(buff1, bff1);
    strcpy(buff2, bff2);
    chars_to_hex(buff1, len);
    chars_to_hex(buff2, len);
    for (int i = 0; i < len; i++)
        out[i] = buff1[i] ^ buff2[i];
    hex_to_chars(out, len);

    free(buff1);
    free(buff2);
    return 0;
}

int main(int argc, char *argv[])
{
    char *output;
    if ((output = malloc(strlen(TEST_STRING1) + 1)) == NULL) {
        fprintf(stderr, "Malloc error.\n");
        return 1;
    }
    fixed_xor(TEST_STRING1, TEST_STRING2, output, strlen(TEST_STRING1));
    fprintf(stdout, "%s\n", output);
    return 0;
}
