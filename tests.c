
#include "munit/munit.h"
#include "game.h"
#include "math.h"
#include "stdio.h"
#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "hash.h"


uint64_t hash_c() {

  uint64_t hash_value = 0;

  return hash_value;

}

uint64_t hash(const char* str, size_t length) {

  uint64_t hash_value = 0;

  for (size_t i = 0; i < length; i++) {

    hash_value += str[i];
    hash_value = hash_value * str[i];
  }

  return hash_value;

}

void my_print_int(void* val) {

  printf("[MY_PRINT]\t value: %d\n", *(int*) val);
}

void my_print_str(void* val) {
  printf("STR_VAL\t: val: %s\n", (char*)val);
}

void test_hash_table_without_collision() {

  const int tablesize = (1<<10);

  hash_table* table = hash_table_create(tablesize, hash);

  int val1 = 99;
  int val2 = 77;
  
  hash_table_insert(table, "a1", &val1);
  hash_table_insert(table, "a2", &val2);

  int* res1 = hash_table_lookup(table, "a1");
  int* res2 = hash_table_lookup(table, "a2");

  munit_assert_ptr_equal(res1, &val1);
  munit_assert_ptr_equal(res2, &val2);
}

void test_hash_table_with_collision() {

  const int tablesize = (1<<10);

  hash_table* table = hash_table_create(tablesize, hash_c);

  int val1 = 99;
  int val2 = 77;
  
  hash_table_insert(table, "a1", &val1);
  hash_table_insert(table, "a2", &val2);

  int* res1 = hash_table_lookup(table, "a1");
  int* res2 = hash_table_lookup(table, "a2");

  munit_assert_ptr_equal(res1, &val1);
  munit_assert_ptr_equal(res2, &val2);
}

void test_hash_table_keys() {

  const int tablesize = (1<<10);

  hash_table* table = hash_table_create(tablesize, hash_c);

  int val1 = 99;
  int val2 = 77;

  hash_table_insert(table, "a1", &val1);
  hash_table_insert(table, "a2", &val2);
  char** keys = hash_table_keys(table);
  int keys_size = hash_table_count(table);

  munit_assert_string_equal(keys[0], "a1");
  munit_assert_string_equal(keys[1], "a2");

}
void test_hash_table_size() {

  const int tablesize = (1<<10);
  hash_table* table = hash_table_create(tablesize, hash_c);
  int val1 = 99;
  int val2 = 77;
  hash_table_insert(table, "a1", &val1);
  hash_table_insert(table, "a2", &val2);

  munit_assert_int(hash_table_count(table), ==, 2);

  hash_table_delete(table, "a1");

  munit_assert_int(hash_table_count(table), ==, 1);
}


int main(void) {

  /* test_hash_table_without_collision(); */
  /* test_hash_table_with_collision(); */
  test_hash_table_keys();
  /* test_hash_table_size(); */

}

int random_n() {

  srand(time(NULL));
  int r = rand();
  printf("random=%d", r%10);
  return r;
}
