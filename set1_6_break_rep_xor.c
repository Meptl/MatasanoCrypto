/* Set 1. Challenge 5. Read base64 encoded file. Decode and decrypt the result
 * which was encrypted using a repeating XOR.
 */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "set1_utils.h"

#define MAX_BUFF 1024
#define KEY_MIN 2
#define KEY_MAX 40
#define KEY_TESTS 4

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

/* Converts the base64 characters to their numerical representation.
 */
void decode64(char *chars, int len)
{
    for (int i = 0; i < len; i++) {
	chars[i] = base64_to_num(chars[i]);
    }
}

/* key_size with the smallest hamming distance on the first key_size bytes with
 * the next key_size bytes is the most likely key. Returns key_sizes which must
 * be free'd by the user.
 */
int *candidate_key_sizes(char *bytes, int len)
{
    double distances[KEY_MAX - KEY_MIN] = { 0 };
    for (int key_size = KEY_MIN; key_size < KEY_MAX; key_size++) {
	int edit_dist = hamming_distance(bytes, bytes + key_size, key_size);
	distances[key_size - KEY_MIN] = edit_dist / ((double) key_size);
    }

    int *key_sizes = malloc(sizeof(int) * KEY_TESTS);
    if (!key_sizes) exit(EXIT_FAILURE);

    for (int i = 0; i < KEY_TESTS; i++)
	key_sizes[0] = -1;

    // Simple linear search for four smallest values.
    // First find smallest value to use as a bound for later searches.
    double prev_smallest = distances[0];
    int smallesti = 0;
    for (int key_index = 0; key_index < KEY_MAX - KEY_MIN; key_index++) {
	if (distances[key_index] < prev_smallest) {
	    prev_smallest = distances[key_index];
	    smallesti = key_index;
	}
    }
    key_sizes[0] = smallesti;

    for (int i = 1; i < KEY_TESTS; i++) {
	double small_val = DBL_MAX;
	for (int key_index = 0; key_index < KEY_MAX - KEY_MIN; key_index++) {
	    double dist = distances[key_index];
	    if (dist < small_val && dist > prev_smallest) {
		small_val = distances[key_index];
		smallesti = key_index;
	    }
	}
	key_sizes[i] = smallesti;
	prev_smallest = small_val;

	// Invalid used blocks
	distances[smallesti] = DBL_MAX;
    }

    return key_sizes;
}

/* Make a block that is the first byte of every key_size segment in bytes. Make
 * a second block that is the second byte of every key_size segment. Returns
 * a pointer to all these blocks which must be free'd by the user.
 */
char **transpose(char *bytes, int len, int key_size)
{
    char **transposition = malloc(sizeof(char *) * key_size);
    if (!transposition) exit(EXIT_FAILURE);

    for (int i = 0; i < key_size; i++) {
	// Theres some extra space for each block because there may be a
	// byte segments smaller than key_size at the end of the bytes array
	// Suppose len = 16 and key_size = 3. There exists 1 extra byte.
	transposition[i] = malloc(sizeof(char *) * len / key_size + 1);
	if (!transposition[i]) exit(EXIT_FAILURE);
    }

    for (int i = 0; i < key_size; i++) {
	for (int j = 0; j < len / key_size; j++) {
	    transposition[i][j] = bytes[j * key_size + i];
	}
    }

    // Add possible extra bytes at end of bytes array
    for (int i = 0; i < len % key_size; i++) {
	transposition[i][len / key_size] = bytes[len - (len % key_size) + i];
    }

    return transposition;
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

    int *smallest_keys = candidate_key_sizes(bytes, size);

    for (int i = 0; i < KEY_TESTS; i++) {
	char **transposition = transpose(bytes, size, smallest_keys[i]);
    }

    free(bytes);
    return EXIT_SUCCESS;
}
