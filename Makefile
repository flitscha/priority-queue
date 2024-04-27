CC = gcc
CFLAGS = -Wall -Wextra

all: heap

heap: main.o heap.o 
	$(CC) $(CFLAGS) main.o heap.o -o heap

main.o: main.c heap.h
	$(CC) $(CFLAGS) -c main.c

heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c

clean:
	rm main.o heap.o heap