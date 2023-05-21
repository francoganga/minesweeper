
#include "munit/munit.h"
#include "game.h"
#include "math.h"
#include "stdio.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

void test_smt() {
  Game *game = new_game(3, 3);

  munit_assert_size(3, ==, game->cells->x);
  munit_assert_size(3, ==, game->cells->y);
}


int main(void) {

  Game* game = new_game(8, 8);

  Cell* cell = get_cell(game, 0, 0);

  Cell* fcell = findCellClicked(game, (Vector2){100,100});

  printf("fcell: {type: %d, rect: {x: %f, y: %f, width: %f, heigth: %f}}", fcell->cell_type, fcell->rect->x, fcell->rect->y, fcell->rect->width, fcell->rect->height);

  int res = 1 > 3;

  printf("res=%d", res);
}

int random_n() {

  srand(time(NULL));
  int r = rand();
  printf("random=%d", r%10);
  return r;
}
