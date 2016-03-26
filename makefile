CFLAGS=-Wall -g -std=c99 -lm
CC=gcc

all: hexto64 fixed_xor byte_xor_cipher
hexto64: hexto64.c hex_utils.c
	$(CC) $(CFLAGS) hexto64.c hex_utils.c -o hexto64
fixed_xor: fixed_xor.c hex_utils.c
	$(CC) $(CFLAGS) fixed_xor.c hex_utils.c -o fixed_xor
byte_xor_cipher: byte_xor_cipher.c hex_utils.c
	$(CC) $(CFLAGS) byte_xor_cipher.c hex_utils.c -o byte_xor_cipher
clean:
	rm -rf *.o hexto64 fixed_xor byte_xor_cipher
