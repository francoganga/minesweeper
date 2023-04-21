#include "raylib.h"
#include "munit/munit.h"
#include "stdio.h"
#include <stddef.h>








int main(void)
{

  Game* game = new_game(3, 3);

  for(size_t i=0; i<game->cells->x; i++)
  {
    for(size_t j=0; j<game->cells->y; j++)
    {
      //get_array(game->cells)[i][j] = *cell_new_number(8);
      set_cell(game, i, j, cell_new_bomb());
      //Cell cell = get_array(game->cells)[i][j];
      Cell *cell = get_cell(game, i, j);

      dumpCell(cell);
      printf(", ");
    }
    printf("\n");
  }

    //int posX = 0;

    //InitWindow(800, 450, "MineSweeper");
    //SetTargetFPS(24);

    //while (!WindowShouldClose())
    //{
    //    BeginDrawing();
    //        ClearBackground(RAYWHITE);
    //        DrawRectangle(posX, 100, 100, 100, BLUE);
    //    EndDrawing();
    //}

    //CloseWindow();

    return 0;
}
