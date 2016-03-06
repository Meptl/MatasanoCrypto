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
    else if (digit == 62)
        return '+';
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

/* Converts the hex characters in a given string to its numerical equivalent.
 * Returns a pointer to the array.
 */
char *chars_to_hex(char *chars, int len)
{
    for (int i = 0; i < len; i++)
        chars[i] = (char)char_to_hex(chars[i]);
    return (char *)chars;
}

/* Converts a value in hex(0 - 15) and represents it as a character.
 */
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
    for (int i = 0; i < len; i++)
        hex[i] = hex_to_char(hex[i]);
    return hex;
}
