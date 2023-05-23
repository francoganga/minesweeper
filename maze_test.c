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
    Cell* cell = create_cell(0, 0);
    

    Cell* cell2 = create_cell(0, 1);

    link(cell, cell2);

    hash_table_print(print_bool_value, cell->links);
}

int main() {

  test_to_string();

  test_cell();


}
