#include "munit/munit.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "grid.c"


void test_to_string() {

    int row = 1;
    int col = 2;
    
    char* str = to_string(row, col);
    
    char* str2 = to_string(0, 1);

    munit_assert_string_equal(str, "12");
    munit_assert_string_equal(str2, "01");
}

void test_it_links_cells() {
    Cell* cell = cell_create(0, 0);
    Cell* cell2 = cell_create(0, 1);

    cell_link(cell, cell2);
    
    munit_assert_ptr_not_null(hash_table_lookup(cell->links, cell_to_string(cell2)));
}

void test_method_linked() {

  Cell* cell = cell_create(0, 0);
  Cell* cell2 = cell_create(0, 1);


  bool result = cell_linked(cell, cell2);

  munit_assert_false(result);

  cell_link(cell, cell2);

  bool result2 = cell_linked(cell, cell2);

  munit_assert_true(result2);
}

void test_it_returns_cell_links() {

  Cell* cell = cell_create(0, 0);
  Cell* cell2 = cell_create(0, 1);
  Cell* cell3 = cell_create(8, 8);

  cell_link(cell, cell2);
  cell_link(cell, cell3);

  char** links = cell_links(cell);
  /* int table_count = hash_table_count(cell->links); */
  
  munit_assert_string_equal(links[0], "01");
  munit_assert_string_equal(links[1], "88");

  free(links);
}

void test_grid() {
  Grid* grid = grid_create(10, 10);

  grid_prepare(grid);
  grid_configure_cells(grid);

  munit_assert_int(grid->rows,==, 10);
  munit_assert_int(grid->columns,==, 10);

  Cell* cell = grid_get_cell(grid, 0, 0);
  munit_assert_ptr_not_null(cell);



  //TODO: this one should be null
  munit_assert_ptr_null(cell->north);

  printf("cell=%s\n", cell_to_string(cell));
  printf("west=%s\n", cell_to_string(cell->east));
  printf("south=%s\n", cell_to_string(cell->south));
  /* printf("north=%s\n", cell_to_string(cell->north)); */
  /* printf("north of north=%s\n", cell_to_string(cell->north->north)); */

  /* munit_assert_ptr_null(cell->north->north); */



  printf("done");





}

int main() {

  test_to_string();
  test_it_links_cells();
  test_it_returns_cell_links();
  test_method_linked();
  test_grid();
}
