#include "raylib.h"

int main(int argc, char **argv)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "r-type");

    Vector2 boxPosition = { (float)screenWidth/2, (float)screenHeight/2 };
    Vector2 boxDimension = { (float)50, (float)50 };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) boxPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) boxPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) boxPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) boxPosition.y += 2.0f;

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("move the box with arrow keys", 10, 10, 20, DARKGRAY);
        DrawRectangleV(boxPosition, boxDimension, MAROON);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
