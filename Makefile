# TARGET = maze
CC = gcc
CFLAGS = -Wall -Werror -Wextra
BUILD= build

all: maze tests
	
run: $(BUILD)/maze
	./$(BUILD)/maze

run_tests: $(BUILD)/tests
	./$(BUILD)/tests

$(BUILD)/maze: $(BUILD)/maze.o $(BUILD)/hash.o $(BUILD)/munit.o
	$(CC) $(CFLAGS) $(BUILD)/maze.o $(BUILD)/hash.o $(BUILD)/munit.o -o $@

$(BUILD)/tests: $(BUILD)/tests.o $(BUILD)/maze.o $(BUILD)/hash.o $(BUILD)/munit.o
	$(CC) $(CFLAGS) $(BUILD)/tests.o $(BUILD)/hash.o $(BUILD)/munit.o -o $@

$(BUILD)/tests.o: tests.c build
	$(CC) $(CFLAGS) -c tests.c -o $@

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $<
$(BUILD)/maze.o: maze.c build
	$(CC) $(CFLAGS) -c maze_test.c -o $@

$(BUILD)/hash.o: hash2.c build
	$(CC) $(CFLAGS) -c hash2.c -o $@

$(BUILD)/munit.o: munit/munit.c build
	$(CC) $(CFLAGS) -c munit/munit.c -o $@

build:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
