CC = gcc
CFLAGS = -Wall -Wextra -std=c11
RAYLIB = $(shell pkg-config --cflags --libs raylib)

visualizer: main.c list.c
	$(CC) $(CFLAGS) main.c list.c -o visualizer $(RAYLIB)

run: visualizer
	./visualizer

clean:
	rm -f visualizer
