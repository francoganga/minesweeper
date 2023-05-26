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
  struct Cell* north;
  struct Cell* south;
  struct Cell* east;
  struct Cell* west;
  hash_table* links;
} Cell;

uint64_t hash(const char* str, size_t length) {

  uint64_t hash_value = 0;
  for (size_t i = 0; i < length; i++) {

    hash_value += str[i];
    hash_value = hash_value * str[i];
  }
  return hash_value;
}

// TODO: this segfaults find out why 
char* cell_to_string(Cell* cell) {
  return to_string(cell->row, cell->col);
}

Cell* cell_create(int row, int col) {
  Cell* cell = malloc(sizeof(Cell));
  cell->row = row;
  cell->col = col;
  cell->links = hash_table_create(1000, hash);
  cell->north = NULL;
  cell->west = NULL;
  cell->south = NULL;
  cell->east = NULL;
  return cell;
}

Cell* cell_link(Cell* self, Cell* target) {

  // TODO: investigate why i cant pass a pointer to a local defined int
  bool val = true;
  bool* val_ptr = &val;

  hash_table_insert(self->links, to_string(target->row, target->col), val_ptr);
  hash_table_insert(target->links, to_string(self->row, self->col), val_ptr);

  return self;
}

Cell* cell_link_bidi(Cell* self, Cell* target) {
  cell_link(self, target);
  cell_link(target, self);

  return self;
}


Cell* cell_unlink(Cell* self, Cell* target) {

  hash_table_delete(self->links, to_string(target->row, target->col));
  return self;
}

Cell* cell_unlink_bidi(Cell* self, Cell* target) {
  cell_unlink(self, target);
  cell_unlink(target, self);

  return self;
}

bool cell_linked(Cell* self, Cell* target) {

  return hash_table_lookup(self->links, to_string(target->row, target->col));
}

char** cell_links(Cell* self) {
  return hash_table_keys(self->links);
}

Cell** neighbors(Cell* self) {
  Cell** neighbors = malloc(sizeof(Cell*) * 4);

  neighbors[0] = self->north;
  neighbors[1] = self->south;
  neighbors[2] = self->east;
  neighbors[3] = self->west;

  return neighbors;
}
