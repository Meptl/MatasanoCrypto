/* Some utility functions for hex, character, and base64 conversions.
 * char is used as a byte datatype
 */

/* Receives a number under 64 and returns an integer that would represents it.
 * If called on non-64 digit behavior is undefined
 */
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

/* Converts a hex character to a value from 0-15, its numerical interpretation.
 * Returns -1 on failure;
 */
char char_to_hex(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return -1;
}

/* Converts the hex characters in a given string to a byte array. Modifies the
 * chars array in place. Each hex char is 4 bits, so the size of the returned
 * array is effectively half that of the given array.
 *
 * Returns a pointer to the modified chars array or NULL on failure
 */
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

/* Converts a value in from 0 - 15 and represents it as a character.
 */
char hex_to_char(char hex)
{
    // 10 = 'a', 'a' = 97
    if ((int)hex < 10)
        return hex + 48;
    else
        return hex + 87;
}

/* Converts an array of bytes into a string of hex characters. Because
 * converting from hex to bytes, then back to hex is so common, this function
 * modifies the hex variable beyond the given len. Use alloc_hex_to_chars to
 * receive a new array.
 *
 * Returns a pointer to the hex array or NULL on failure.
 */
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

/* Converts an array of bytes into a string of hex characters.
 *
 * Returns a char array that must be free'd by the user or NULL on failure
 */
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
