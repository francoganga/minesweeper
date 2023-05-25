# TARGET = maze
CC = gcc
CFLAGS = -Wall -Werror -Wextra
BUILD= build

all: $(BUILD)/cell $(BUILD)/tests
	
run: $(BUILD)/cell
	./$(BUILD)/cell

run_tests: $(BUILD)/tests
	./$(BUILD)/tests

$(BUILD)/cell: $(BUILD)/maze_test.o $(BUILD)/hash.o $(BUILD)/munit.o
	$(CC) $(CFLAGS) $(BUILD)/maze_test.o $(BUILD)/hash.o $(BUILD)/munit.o -o $@

$(BUILD)/tests: $(BUILD)/tests.o $(BUILD)/cell.o $(BUILD)/hash.o $(BUILD)/munit.o
	$(CC) $(CFLAGS) $(BUILD)/tests.o $(BUILD)/hash.o $(BUILD)/munit.o -o $@

$(BUILD)/tests.o: tests.c build
	$(CC) $(CFLAGS) -c tests.c -o $@

$(BUILD)/cell.o: cell.c build
	$(CC) $(CFLAGS) -c cell.c -o $@

$(BUILD)/maze_test.o: cell.c build
	$(CC) $(CFLAGS) -c maze_test.c -o $@

$(BUILD)/hash.o: hash.c build
	$(CC) $(CFLAGS) -c hash.c -o $@

$(BUILD)/munit.o: munit/munit.c build
	$(CC) $(CFLAGS) -c munit/munit.c -o $@

$(BUILD)/grid.o: grid.c build
	$(CC) $(CFLAGS) -c grid.c -o $@

build:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
