#include "raylib.h"
#include "keybinds.hpp"
#include <iostream>

void Jump()
{
    std::cout << "Player jumped!" << std::endl;
}

void DrawKeybindMenu(InputManager& manager)
{
    int y = 100;
    DrawText("KEYBINDS", 50, 50, 20, WHITE);

    for (const auto& [name, binding] : manager.getBindings()) {
        Rectangle rect = {50, (float)y, 300, 30};

        DrawRectangleRec(rect, DARKGRAY);
        DrawText(
            TextFormat("%s : %s", name.c_str(), GetKeyName(binding.getKey())),
            60, y + 5, 20, WHITE
        );

        if (CheckCollisionPointRec(GetMousePosition(), rect) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            manager.startRebind(name);
        }

        y += 40;
    }

    if (manager.rebinding()) {
        DrawText("Press a key...", 50, y + 10, 20, RED);
    }
}

int main()
{
    InitWindow(800, 450, "Keybinds Library Example");
    SetTargetFPS(60);

    InputManager input;
    input.add("Jump", KEY_SPACE, Jump);

    bool showMenu = false;

    while (!WindowShouldClose()) {
        int key = GetKeyPressed();

        if (IsKeyPressed(KEY_TAB))
            showMenu = !showMenu;

        input.handleKey(key);

        BeginDrawing();
        ClearBackground(BLACK);

        if (showMenu)
            DrawKeybindMenu(input);
        else
            DrawText("Press TAB to open keybind menu", 20, 20, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
