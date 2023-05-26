#include <stdlib.h>
#include "cell.c"

typedef struct Grid {
  int rows;
  int columns;
  Cell** cells;
} Grid;

Grid* grid_create(int rows, int columns) {
  Grid* grid = malloc(sizeof(Grid));
  grid->cells = malloc(rows * columns * sizeof(Cell*));
  grid->rows = rows;
  grid->columns = columns;
  return grid;
}

void grid_destroy(Grid* grid) {
  free(grid->cells);
  free(grid);
}

Cell* grid_get_cell(Grid* grid, int row, int col) {
  Cell* cell = grid->cells[row * grid->columns + col];
  printf("getting cell=%s", cell_to_string(cell));

  return cell;
}

void grid_prepare(Grid* grid) {
  for (int i = 0; i < grid->rows; i++) {
    for (int j = 0; j < grid->columns; j++) {
      grid->cells[i * grid->columns + j] = cell_create(i, j);
    }
  }
}

void grid_configure_cells(Grid* grid) {

  Cell* cell = NULL;

  for (int i = 0; i < grid->rows; i++) {
    for (int j = 0; j < grid->columns; j++) {
      cell = grid->cells[i * grid->columns + j];

      if (i > 0) {
        cell->north = grid->cells[(i - 1) * grid->columns + j];
      }
      if (i < grid->rows - 1) {
        cell->south = grid->cells[(i + 1) * grid->columns + j];
      }
      if (j > 0) {
        cell->west = grid->cells[i * grid->columns + (j - 1)];
      }
      if (j < grid->columns - 1) {
        cell->east = grid->cells[i * grid->columns + (j + 1)];
      }
    }
  }
}
