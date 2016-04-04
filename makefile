CFLAGS=-Wall -g -std=c99 -lm
CC=gcc

all: hexto64 fixed_xor byte_xor_cipher
hexto64: set1_1_hexto64.c hex_utils.c
	$(CC) $(CFLAGS) $^ -o hexto64
fixed_xor: set1_2_fixed_xor.c hex_utils.c
	$(CC) $(CFLAGS) $^ -o fixed_xor
byte_xor_cipher: set1_3_byte_xor_cipher.c hex_utils.c
	$(CC) $(CFLAGS) $^ -o byte_xor_cipher
clean:
	rm -rf *.o hexto64 fixed_xor byte_xor_cipher
