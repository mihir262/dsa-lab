CC = gcc
CFLAGS = -Wall -Wextra -std=c11

structs: main.c complex.c point.c complex.h point.h
	$(CC) $(CFLAGS) main.c complex.c point.c -o structs -lm

clean:
	rm -f structs
