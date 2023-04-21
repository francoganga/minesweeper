#include <stddef.h>
#include <stdlib.h>

// https://stackoverflow.com/questions/54709981/how-to-initiliaze-a-dynamic-2d-array-inside-a-struct-in-c
typedef struct {
  size_t x;
  size_t y;
  int flex[];
} array2d_t;

#define get_array(arr2d) \
  _Generic( (arr2d),     \
            array2d_t*: (Cell(*)[(arr2d)->y])(arr2d)->flex )

typedef struct Game {
  array2d_t* cells;
} Game;

typedef struct Cell {
  enum {CELL_BLANK, CELL_BOMB, CELL_NUMBER} cell_type;

  int number;

} Cell;

Game *new_game(int rows, int cols) {
  Game *game = malloc(sizeof(Game));

  size_t x = cols;
  size_t y = rows;
  
  array2d_t* arr = malloc( sizeof *arr + sizeof(Cell[x][y]) );
  arr->x = x;
  arr->y = y;

  game->cells = arr;

  return game;
}

Cell *get_cell(Game* game, int x, int y) {
  return &get_array(game->cells)[x][y];
}


void set_cell(Game *game, size_t x, size_t y, Cell *cell) {
  get_array(game->cells)[x][y] = *cell;
}

Cell *cell_new_bomb() {
  Cell *cell = malloc(sizeof(Cell));

  cell->cell_type = CELL_BOMB;

  return cell;
}

Cell *cell_new_number(int number) {
  Cell *cell = malloc(sizeof(Cell));

  cell->cell_type = CELL_NUMBER;
  cell->number = number;

  return cell;
}

Cell *cell_new_blank() {
  Cell *cell = malloc(sizeof(Cell));

  cell->cell_type = CELL_BLANK;

  return cell;
}

void dumpCell(Cell* cell) {
  if (cell->cell_type == CELL_NUMBER) {
    printf("{ cell_type: %d, cell_number: %d }", cell->cell_type, cell->number);
  } else {
    printf("{ cell_type: %d }", cell->cell_type);
  }
}
