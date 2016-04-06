/* Set 1. Challenge 5.
 */
#include <stdio.h>

/* Calculate the number of differing bits in two strings.
 * XOR gets location of differing bits. Then use Brian Kernighan's algorithm
 * to count number of one bits.
 */
int hamming_distance(char *str1, char *str2, int len)
{
    int diff = 0;
    for (int i = 0; i < len; i++) {
	char x = str1[i] ^ str2[i];
	while (x) {
	    x &= x - 1;
	    diff++;
	}
    }
    return diff;
}

int main(int argc, char *argv[])
{
    printf("%d\n", hamming_distance("this is a test", "wokka wokka!!!", 14));
    return 0;
}
