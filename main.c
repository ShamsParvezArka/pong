#include <stdio.h>
#include <raylib.h>
#include <time.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

Vector2 player1_position = {10, 10};
Vector2 player2_position = {SCREEN_WIDTH - 30, SCREEN_HEIGHT - 70};

Vector2 box_size  = {20, 60};

Vector2 ball_size = {20, 20};
Vector2 ball_position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

Vector2 ball_speed = {5, 5};

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        if (IsKeyDown(KEY_S) && (player1_position.y + box_size.y) <= SCREEN_HEIGHT) 
            player1_position.y += 15;

        else if (IsKeyDown(KEY_W) && player1_position.y >= 0) 
            player1_position.y -= 15;

        if (IsKeyDown(KEY_DOWN) && (player2_position.y + box_size.y) <= SCREEN_HEIGHT)
            player2_position.y += 15;
        
        else if (IsKeyDown(KEY_UP) && player2_position.y >= 0) 
            player2_position.y -= 15;
        
        if (ball_position.x + ball_size.x >= SCREEN_WIDTH) {
            ball_speed.x = - ball_speed.x;
            ball_position.x = SCREEN_WIDTH - ball_size.x;
        } else if (ball_position.x <= 0) {
            ball_speed.x = - ball_speed.x;
            ball_position.x = 0;
        }
        if (ball_position.y + ball_size.y >= SCREEN_HEIGHT) {
            ball_speed.y = - ball_speed.y;
            ball_position.y = SCREEN_HEIGHT - ball_size.y;
        } else if (ball_position.y <= 0) {
            ball_speed.y = - ball_speed.y;
            ball_position.y = 0;
        }

        ball_position.x += ball_speed.x;
        ball_position.y += ball_speed.y;

        BeginDrawing();
			ClearBackground(BLACK);
			DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, GRAY);
			DrawRectangleV(player1_position, box_size, WHITE);
			DrawRectangleV(player2_position, box_size, WHITE);
            DrawRectangleV(ball_position, ball_size, WHITE);
        EndDrawing();
    }
    return 0;
}
