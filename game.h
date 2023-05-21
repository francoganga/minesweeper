#ifndef GAME
#define GAME

#include <stddef.h>
#include "raylib.h"

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

  Rectangle* rect;

  int number;

} Cell;


Game *new_game(int rows, int cols);
Cell *get_cell(Game* game, int x, int y);
void set_cell(Game *game, size_t x, size_t y, Cell *cell);
Cell *cell_new_bomb(Rectangle rect);
Cell *cell_new_number(Rectangle rect, int number);
Cell *cell_new_blank(Rectangle rect);

void set_cell_rect(Cell *cell, Rectangle rect);

void dumpCell(Cell* cell);

Cell *findCellClicked(Game *game, Vector2 pos);



#endif
