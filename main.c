#include "raylib.h"

int main(void)
{
    int posX = 0;

    InitWindow(800, 450, "MineSweeper");
    SetTargetFPS(24);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(posX, 100, 100, 100, BLUE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
