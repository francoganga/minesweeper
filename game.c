#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include <unistd.h>

// TODO: Agregar parametro de posicion
Game *new_game(int rows, int cols) {
  Game *game = malloc(sizeof(Game));

  size_t x = cols;
  size_t y = rows;
  
  array2d_t* arr = malloc( sizeof *arr + sizeof(Cell[x][y]) );

  arr->x = x;
  arr->y = y;

  game->cells = arr;

  for(size_t i=0; i<game->cells->x; i++)
  {
    for(size_t j=0; j<game->cells->y; j++)
    {

      set_cell(game, i, j, cell_new_number((Rectangle){i, j, 50, 50}, i + j));
      Cell *cell = get_cell(game, i, j);

    }
  }

  return game;
}

Cell *get_cell(Game* game, int x, int y) {
  return &get_array(game->cells)[x][y];
}


void set_cell(Game *game, size_t x, size_t y, Cell *cell) {
  get_array(game->cells)[x][y] = *cell;
}

Cell *findCellClicked(Game *game, Vector2 pos) {

  for (size_t j = 0; j < game->cells->y; j++) {
    for (size_t i = 0; i < game->cells->x; i++) {
      Cell* cell = get_cell(game, i,j);

      float width = cell->rect->width;

      printf("X1=%f, X2=%f, Y1=%f, Y2=%f\n\n", cell->rect->x, cell->rect->x + cell->rect->width, cell->rect->y, cell->rect->y + cell->rect->width);
      printf("POS: (%f, %f)\n", pos.x, pos.y);
      int between_x = cell->rect->x < pos.x && pos.x < cell->rect->x + 50;

      int between_y = cell->rect->y < pos.y && pos.y < cell->rect->y + 50;

      printf("between_x=%d, between_y=%d\n", between_x, between_y);
      if (cell->rect->x < pos.x && pos.x < cell->rect->x + 50 && cell->rect->y < pos.y && pos.y < cell->rect->y + 50) {
        return cell;
      }
    }
  }

  return NULL;
}


void set_cell_rect(Cell *cell, Rectangle rect) {
  cell->rect = &rect;
}

Cell *cell_new_bomb(Rectangle rect) {
  Cell *cell = malloc(sizeof(Cell));
  //cell->rect = malloc(sizeof(Rectangle));
  cell->cell_type = CELL_BOMB;
  cell->rect = &rect;

  return cell;
}

Cell *cell_new_number(Rectangle rect, int number) {
  Cell *cell = malloc(sizeof(Cell));
  cell->rect = malloc(sizeof(Rectangle));
  cell->cell_type = CELL_NUMBER;
  cell->number = number;
  cell->rect->x = rect.x;
  cell->rect->y = rect.y;
  cell->rect->width = rect.width;
  cell->rect->height = rect.height;

  return cell;
}

Cell *cell_new_blank(Rectangle rect) {
  Cell *cell = malloc(sizeof(Cell));
  cell->rect = malloc(sizeof(Rectangle));
  cell->cell_type = CELL_BLANK;
  cell->rect->x = rect.x;
  cell->rect->y = rect.y;
  cell->rect->width = rect.width;
  cell->rect->height = rect.height;

  return cell;
}

void dumpCell(Cell* cell) {
  if (cell->cell_type == CELL_NUMBER) {
    printf("{ cell_type: %d, cell_number: %d }", cell->cell_type, cell->number);
  } else {
    printf("{ cell_type: %d }", cell->cell_type);
  }
}
