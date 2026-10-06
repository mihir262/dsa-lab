CC = gcc
CFLAGS = -Wall -Wextra -std=c11

.PHONY: all clean

all: array_menu list_menu infixtopostfix postfixeval

array_menu: array_menu.c stackarray.c stackarray.h
	$(CC) $(CFLAGS) array_menu.c stackarray.c -o array_menu

list_menu: list_menu.c stackll.c stackll.h
	$(CC) $(CFLAGS) list_menu.c stackll.c -o list_menu

infixtopostfix: infixtopostfix.c stackarray.c stackarray.h
	$(CC) $(CFLAGS) infixtopostfix.c stackarray.c -o infixtopostfix

postfixeval: postfixeval.c stackarray.c stackarray.h
	$(CC) $(CFLAGS) postfixeval.c stackarray.c -o postfixeval

clean:
	rm -f array_menu list_menu infixtopostfix postfixeval
