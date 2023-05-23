# TARGET = maze
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: maze tests
	
run: maze
	./maze_test.out

maze: maze.o hash.o munit.o
	$(CC) $(CFLAGS) maze_test.o hash2.o munit.o -o maze_test.out

tests: tests.o maze.o hash.o munit.o
	$(CC) $(CFLAGS) tests.o hash2.o munit.o -o tests.out

tests.o: tests.c
	$(CC) $(CFLAGS) -c tests.c

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $<
maze.o: maze.c
	$(CC) $(CFLAGS) -c maze_test.c

hash.o: hash2.c
	$(CC) $(CFLAGS) -c hash2.c

munit.o: munit/munit.c
	$(CC) $(CFLAGS) -c munit/munit.c

clean:
	rm a.out *.o *.out
