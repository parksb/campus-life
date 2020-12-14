all: release debug

CC = gcc

release: main.c
	$(CC) -o release -O main.c -lpthread

debug: main.c checker.c
	$(CC) -DDEBUG -g -o debug main.c -lpthread
	$(CC) -DDEBUG -g -o checker checker.c

clean:
	rm -f *.o release debug
