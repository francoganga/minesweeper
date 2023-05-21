#include "raylib.h"
#include "stdio.h"
#include <stdlib.h>
#include <stddef.h>
#include "game.h"


void draw_board(Game *game, int bombs);

void draw_board(Game *game, int bombs) {
  for (size_t i = 0; i < game->cells->x; i++) {
    for (size_t j = 0; j < game->cells->y; j++) {

    }
  }
}


int main(void)
{

  Vector2 mp = {0, 0};
  int m_x = 0;
  int m_y = 0;

  Game* game = new_game(8, 8);

  InitWindow(800, 600, "MineSweeper");
  SetTargetFPS(24);
  Image img = LoadImage("tiles.png");
  ImageResize(&img, 50, 50 * 16);

  //Texture2D texture = LoadTexture("tiles.png");
  Texture2D texture = LoadTextureFromImage(img);


  while (!WindowShouldClose())
  {

    mp = GetMousePosition();

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      Cell* cell = findCellClicked(game, mp);

      if (cell != NULL ) {
        TraceLog(LOG_INFO, "FOUND CELL!");
        TraceLog(LOG_INFO, "cell: {type: %d, rect: {x: %f, y: %f, width: %f, heigth: %f}}", cell->cell_type, cell->rect->x, cell->rect->y, cell->rect->width, cell->rect->height);
      } else {
        TraceLog(LOG_INFO, "No encontro ndad");
      }
      TraceLog(LOG_INFO, "Mouse button released at: X=%f, Y=%f", mp.x, mp.y);
    }
    /*  */
    /* TraceLog(LOG_INFO, "Mouse POs at X=%f, Y=%f", mp.x, mp.y); */

    BeginDrawing();

    //DrawTexture(texture, 100, 100, WHITE);
    //DrawTextureRec(texture, (Rectangle){0,100, 50,50}, (Vector2){100,100}, WHITE);
    
    ClearBackground(RAYWHITE);
    DrawLine(100, 100, 500, 100, BLACK);
    DrawLine(500, 100, 500, 500, BLACK);
    DrawLine(500, 500, 100, 500, BLACK);
    DrawLine(100, 500, 100, 100, BLACK);


    for(size_t i=0; i < game->cells->y; i++) {
      for(size_t j=0; j < game->cells->x; j++) {
        DrawLine(100 + (j * 50), 100 + (i*50), 100 + (j * 50), 150 + (i * 50), BLACK);

        Rectangle rect = (Rectangle){0,0, 50,50};

        DrawTextureRec(texture, rect, (Vector2){100 + j * 50, 100 + i*50}, WHITE);
        Cell* cell = get_cell(game, i, j);
        
        set_cell_rect(cell, rect);

        int length = snprintf(NULL, 0, "%d", get_cell(game, j, i)->number);

        char* str = malloc( length + 1 );
        snprintf(str, length + 1, "%d", get_cell(game, j, i)->number);

        DrawText(str, 100 + (j * 50) + 20, 100 + (i * 50) + 20, 10, RED);
      }
      DrawLine(100, 100 + (i * 50), 500, 100 + (i * 50), BLACK);
    }
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
