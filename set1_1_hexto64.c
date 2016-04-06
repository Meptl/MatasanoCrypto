/* Set 1. Challenge 1. Converts a hex string given in stdin to base64 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set1_utils.h"

#define MAX_BUFF 256

/* Takes three hex digits and prints out their representation as two base64
 * digits.
 */
static void num3_to_base64(char num1, char num2, char num3)
{
    // Split the digits of num2 between num1 and num3
    char first = (num1 << 2) | ((num2 & 0xc) >> 2);
    char second = (num3) | (num2 & 0x3) << 4;
    printf("%c%c", num_to_base64(first), num_to_base64(second));
}

/* Receives lines from standard input and converts tries to convert the hex
 * characters to base64. Behavior is undefined when not given hex string
 */
static int stdin_to_double()
{
    char *input = malloc(sizeof(char) * MAX_BUFF);

    while (get_line(stdin, NULL, input, MAX_BUFF) == 0) {
        int len = strlen(input);
        int extra = (len % 3);

        // Every 3 hex holds 12 data bits and 2 base64
        if (extra == 1) {
            char hex = char_to_hex(*input++);
            printf("%c", num_to_base64(hex));
        }
        else if (extra == 2) {
            char hex1 = char_to_hex(*input++);
            char hex2 = char_to_hex(*input++);
            // We have 8 data bits so pad the leading 2.
            hex2 |= (hex1 & 0x3) << 4;
            hex1 = (hex1 >> 2) & 0x3;
            printf("%c%c", num_to_base64(hex1), num_to_base64(hex2));
        }
        while (*input != '\0') {
            char hex1 = char_to_hex(*input++);
            char hex2 = char_to_hex(*input++);
            char hex3 = char_to_hex(*input++);
            num3_to_base64(hex1, hex2, hex3);
        }
        printf("\n");

        input -= len;
    }

    free(input);
    return 0;
}

int main(int argc, char *argv[])
{
    return stdin_to_double();
}

