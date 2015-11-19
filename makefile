CFLAGS=-Wall -g -std=c99 -lm
CC=gcc

all: hexto64 fixed_xor
clean:
	rm -rf *.o hexto64 fixed_xor
