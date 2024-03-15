all: release debug

CC = gcc

release: hexdump.c
	$(CC) -o release -O hexdump.c

debug: hexdump.c
	$(CC) -DDEBUG -g -o debug hexdump.c

clean:
	rm -f *.o release debug