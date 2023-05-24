#include "munit/munit.h"
#include <math.h>
#include <stdio.h>
#include "maze.c"


void test_to_string() {

    int row = 1;
    int col = 2;
    
    char* str = to_string(row, col);
    
    char* str2 = to_string(0, 1);

    munit_assert_string_equal(str, "12");
    munit_assert_string_equal(str2, "01");
}

void test_cell() {
    Cell* cell = cell_create(0, 0);
    Cell* cell2 = cell_create(0, 1);

    cell_link(cell, cell2);

    hash_table_print(print_bool_value, cell->links);
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
}

int main() {

  /* test_to_string(); */
  /* test_cell(); */
  test_it_returns_cell_links();


}
