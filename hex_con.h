/* Receives a number under 64 and returns an integern that would represents it.
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

/* Converts a character to a value from 0-15,
 * its numerical interpretation in hex.
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

/* Converts the hex characters in a given string to its numerical binary.
 * Returns a pointer to the given string.
 */
char *chars_to_hex(char *chars, int len)
{
    for (int i = 0; i < len; i++)
        chars[i] = char_to_hex(chars[i]);
    return chars;
}

/* Converts a value in hex and represents it as a number
 */
char hex_to_char(char hex)
{
    // a = 10
    return hex + 87;
}

char *hex_to_chars(char *hex, int len)
{
    for (int i = 0; i < len; i++)
        hex[i] = hex_to_char(hex[i]);
    return hex;
}
