#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

int main()
{
    Vector2 player1 = {10, 10};
    Vector2 player2 = {SCREEN_WIDTH - 30, SCREEN_HEIGHT - 70};
    Vector2 box_size = {20, 60};

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        if (IsKeyDown(KEY_S) && (player1.y + box_size.y) <= SCREEN_HEIGHT) 
            player1.y += 15;

        else if (IsKeyDown(KEY_W) && player1.y >= 0) 
            player1.y -= 15;

        if (IsKeyDown(KEY_DOWN) && (player2.y + box_size.y) <= SCREEN_HEIGHT)
            player2.y += 15;
        
        else if (IsKeyDown(KEY_UP) && player2.y >= 0) 
            player2.y -= 15;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, GRAY);
        DrawRectangleV(player1, box_size, WHITE);
        DrawRectangleV(player2, box_size, WHITE);
        EndDrawing();
    }
    return 0;
}