CFLAGS=-std=c99 -Wall
CC=gcc

all: hexto64 fixed_xor byte_xor_cipher detect_xor enc_rep_xor break_rep_xor
hexto64: set1_1_hexto64.c set1_utils.c
	$(CC) $(CFLAGS) $^ -o hexto64
fixed_xor: set1_2_fixed_xor.c set1_utils.c
	$(CC) $(CFLAGS) $^ -o fixed_xor
byte_xor_cipher: set1_3_byte_xor_cipher.c set1_utils.c
	$(CC) $(CFLAGS) $^ -o byte_xor_cipher
detect_xor: set1_4_detect_xor.c set1_utils.c
	$(CC) $(CFLAGS) $^ -o detect_xor
enc_rep_xor: set1_5_enc_rep_xor.c set1_utils.c
	$(CC) $(CFLAGS) $^ -o enc_rep_xor
break_rep_xor: set1_6_break_rep_xor.c
	$(CC) $(CFLAGS) $^ -o break_rep_xor
clean:
	rm -rf *.o hexto64 fixed_xor byte_xor_cipher detect_xor enc_rep_xor \
	    break_rep_xor
