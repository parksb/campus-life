all: release debug

CC = gcc

release: student.c
	$(CC) -o release -O student.c

debug: student.c
	$(CC) -DDEBUG -g -o debug student.c

clean:
	rm -f *.o release debug