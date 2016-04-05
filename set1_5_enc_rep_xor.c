/* Set 1. Challenge 5. Reads a line from stdin. Performs a XOR with the key
 * given as an argument and outputs this to stdout. Is not reversible because
 * outputs in ASCII, but that would be a quick fix.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "set1_utils.h"

#define MAX_BUFF 256

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "enc_rep_xor [KEY]\n");
        exit(EXIT_FAILURE);
    }

    char *input = malloc(sizeof(char) * MAX_BUFF);
    char *output = malloc(sizeof(char) * MAX_BUFF);
    if (!input || !output) {
        fprintf(stderr, "Out of Memory\n");
        exit(EXIT_FAILURE);
    }

    ssize_t read_size;
    int key_index = 0;
    int key_len = strlen(argv[1]);
    while ((read_size = read(STDIN_FILENO, input, MAX_BUFF)) > 0) {
        for (int i = 0; i < read_size; i++) {
            printf("%02x", input[i] ^ argv[1][key_index++]);
            if (key_index == key_len)
                key_index = 0;
        }
    }

    free(output);
    free(input);
    return 0;
}
