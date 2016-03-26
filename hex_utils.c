#include <stdlib.h>
#include "hex_utils.h"

char num_to_base64(char digit)
{
    if (digit < 26)
        return digit + 'A';
    else if (digit < 52)
        return digit + 'a' - 26;
    else if (digit < 62)
        return digit + '0' - 52;
    else if (digit == 62) return '+';
    else if (digit == 63)
        return '/';
    else
        return '-';
}

char char_to_hex(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return -1;
}

char *chars_to_hex(char *chars, int len)
{
    // We could pad by zeros, but it would be error prone on the user's end
    if (len % 2 != 0)
        return NULL;

    for (int i = 0; i < len / 2; i++) {
        char seg0 = char_to_hex(chars[2 * i]);
        char seg1 = char_to_hex(chars[2 * i + 1]);
        if (seg0 == -1 || seg1 == -1)
            return NULL;

        chars[i] = (seg0 << 4) | seg1;
    }

    return chars;
}

char hex_to_char(char hex)
{
    // 10 = 'a', 'a' = 97
    if ((int)hex < 10)
        return hex + 48;
    else
        return hex + 87;
}

char *hex_to_chars(char *hex, int len)
{
    for (int i = len * 2 - 1; i > 0; i -= 2) {
        char seg0 = (hex[i / 2] & 0xf0) >> 4;
        char seg1 = (hex[i / 2] & 0x0f);
        hex[i - 1] = hex_to_char(seg0);
        hex[i] = hex_to_char(seg1);
    }

    return hex;
}

char *alloc_hex_to_chars(char *hex, int len)
{
    char *string;
    if ((string = malloc(len * 2 + 1)) == NULL)
        return NULL;
    string[len * 2] = '\0';

    for (int i = 0; i < len; i++) {
        char seg0 = (hex[i] & 0xf0) >> 4;
        char seg1 = (hex[i] & 0x0f);
        string[2 * i] = hex_to_char(seg0);
        string[2 * i + 1] = hex_to_char(seg1);
    }

    return hex;
}
