SHELL=/bin/sh

CC=gcc
CFLAGS=-c -w
LFLAGS=-lcurses

all: build

build: snake.o display.o output.o
	$(CC) -o snake *.o $(LFLAGS)

snake.o: snake.c
	$(CC) $(CFLAGS) snake.c $(LFLAGS)

display.o: display.c
	$(CC) $(CFLAGS) display.c $(LFLAGS)

output.o: output.c
	$(CC) $(CFLAGS) output.c $(LFLAGS)

clean:
	rm -rf *.o snake
