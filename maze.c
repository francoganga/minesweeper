#include "hash.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>



char* to_string(int row, int col) {

  int length_row = snprintf(NULL, 0, "%d", row);

  int length_col = snprintf(NULL, 0, "%d", col);

  char* str = malloc(length_row + length_col + 1);

  sprintf(str, "%d%d", row, col);

  return str;
}

void print_bool_value(void* val) {

  printf("value: %s\n", *(bool*) val ? "true" : "false");

}

void print_str_value(void* val) {

  printf("value: %s\n", (char*) val);

}


typedef struct Cell {
  int row;
  int col;
  hash_table* links;
} Cell;

uint64_t hash(const char* str, size_t length) {

  uint64_t hash_value = 0;
  for (int i = 0; i < length; i++) {

    hash_value += str[i];
    hash_value = hash_value * str[i];
  }
  return hash_value;
}

Cell* create_cell(int row, int col) {
  Cell* cell = malloc(sizeof(Cell));
  cell->row = row;
  cell->col = col;
  cell->links = hash_table_create(1000, hash);
  return cell;
}

void link(Cell* self, Cell* target) {

  // TODO: investigate why i cant pass a pointer to a local defined int
  bool* val = malloc(sizeof(bool));
  *val = true;

  hash_table_insert(self->links, to_string(target->row, target->col), val);
}


void unlink(Cell* self, Cell* target) {

  hash_table_delete(self->links, to_string(target->row, target->col));
}

bool linked(Cell* self, Cell* target) {

  return hash_table_lookup(self->links, to_string(target->row, target->col));
}
