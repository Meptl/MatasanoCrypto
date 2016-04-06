#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "set1_utils.h"

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
int get_line(FILE *stream, char *prompt, char *buff, size_t s) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prompt != NULL) {
        printf("%s", prompt);
        fflush(stdout);
    }

    if (fgets(buff, s, stream) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getc(stream)) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return OK;
}

/* A table of letter frequencies for English. 'a' is index 0.
 * These values roughly add up to 100.
 */
static double english_freq[26] = { 8.12, 1.49, 2.78, 4.25, 12.70, 2.23, 2.01, 6.09,
                            6.97, 0.15, 0.77, 4.02, 2.41, 6.75, 7.51, 1.93,
                            0.09, 5.98, 6.33, 9.06, 2.76, 0.98, 2.36, 0.15,
                            1.98, 0.07 };

double english_score(char *sentence)
{
    double freq[26] = { 0 };
    int chars = 0;
    for (char *s = sentence; *s; s++) {
        char c = *s;
        if (c >= 'A' && c <= 'Z')
            c = c + ('a' - 'A');

        if (c >= 'a' && c <= 'z') {
            chars++;
            freq[c - 'a']++;
        }
    }

    // No letters found
    if (chars == 0)
        return 0;

    // Convert absolute frequencies to relative frequencies in percent
    for (int i = 0; i < 26; i++)
        freq[i] = (freq[i] / chars) * 100;

    // Calculate errors
    double err = 0;
    for (int i = 0; i < 26; i++)
        err += fabs(english_freq[i] - freq[i]);

    if (err > 100)
        err = 100;

    return 100 - err;
}

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

char base64_to_num(char digit)
{
    if (digit >= 'A' && digit <= 'Z')
        return digit - 'A';
    else if (digit >= 'a' && digit <= 'z')
        return digit - 'a' + 26;
    else if (digit >= '0' && digit <= '9')
        return digit - '0' + 52;
    else if (digit == '+')
	return 62;
    else if (digit == '/')
        return 63;
    else if (digit == '-')
        return 64;
    else
	return 65;

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
