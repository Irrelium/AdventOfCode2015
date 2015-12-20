# This Makefile is probably bad

CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-Wall
EXECUTABLE=1-1

.PHONY: clean

$(EXECUTABLE): main.o
	$(CC) $(LDFLAGS) $< -o$@

main.o: main.c
	$(CC) $(CFLAGS) $< -o$@

clean:
	rm -f *.o $(EXECUTABLE)
