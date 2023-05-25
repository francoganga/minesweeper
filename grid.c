#include <stdlib.h>

typedef struct Grid {
    int rows;
    int columns;
} Grid;

Grid* grid_create(int rows, int columns) {
    Grid* grid = malloc(sizeof(Grid));
    grid->rows = rows;
    grid->columns = columns;
    return grid;
}
