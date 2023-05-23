
#include "munit/munit.h"
#include "game.h"
#include "math.h"
#include "stdio.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "hash.h"


uint64_t hash_c(const char* str, size_t length) {

  uint64_t hash_value = 0;

  return hash_value;

}

uint64_t hash(const char* str, size_t length) {

  uint64_t hash_value = 0;

  for (int i = 0; i < length; i++) {

    hash_value += str[i];
    hash_value = hash_value * str[i];
  }

  return hash_value;

}

void my_print(void* val) {

  printf("[MY_PRINT]\t value: %d\n", *(int*) val);
}


int main(void) {


  const int tablesize = (1<<20);

  hash_table* table = hash_table_create(tablesize, hash_c);


  int val1 = 99;
  int val2 = 77;




  
  hash_table_insert(table, "a1", (void*) &val1);
  hash_table_insert(table, "a2", (void*) &val2);

  hash_table_print(my_print, table);


}

int random_n() {

  srand(time(NULL));
  int r = rand();
  printf("random=%d", r%10);
  return r;
}
