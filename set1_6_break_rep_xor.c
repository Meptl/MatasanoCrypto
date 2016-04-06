/* Set 1. Challenge 5. Read base64 encoded file. Decode and decrypt the result
 * which was encrypted using a repeating XOR.
 */
#include <stdio.h>
#include <stdlib.h>
#include "set1_utils.h"

#define MAX_BUFF 1024
#define KEY_MIN 2
#define KEY_MAX 40

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

/* Returns the number of bytes in a file.
 */
int get_file_size(FILE *in)
{
    if (fseek(in, 0, SEEK_END) != 0) {
	fprintf(stderr, "Error reading file.\n");
	exit(EXIT_FAILURE);
    }

    int size = ftell(in);
    rewind(in);

    return size;
}

/* Reads a file and stores all its data in buff which must be free'd by the
 * user. Returns the length of this buffer.
 */
int read_file(char *file, char **buff)
{

    FILE *infile = fopen(file, "r");
    if (!infile) {
	fprintf(stderr, "Could not open file %s\n", file);
	exit(EXIT_FAILURE);
    }

    int fsize = get_file_size(infile);
    *buff = malloc(sizeof(char) * fsize);
    if (!*buff) {
	fprintf(stderr, "Out of memory.\n");
	exit(EXIT_FAILURE);
    }

    if (fread(*buff, fsize, 1, infile) != 1) {
	fprintf(stderr, "Failed to read file.\n");
	exit(EXIT_FAILURE);
    }

    fclose(infile);
    return sizeof(char) * fsize;
}

void decode64(char *chars, int len)
{
    for (int i = 0; i < len; i++) {
	chars[i] = base64_to_num(chars[i]);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
	fprintf(stderr, "break_rep_xor [FILE]\n");
	exit(EXIT_FAILURE);
    }

    char *bytes = NULL;
    int size = read_file(argv[1], &bytes);
    decode64(bytes, size);

    free(bytes);
    return EXIT_SUCCESS;
}
