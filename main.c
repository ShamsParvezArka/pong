#include <stdio.h>
#include <raylib.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

void control_paddle();
bool collided(Vector2 paddle);

Vector2 paddle1 = {10, 10};
Vector2 paddle2 = {SCREEN_WIDTH - 30, SCREEN_HEIGHT - 70};
Vector2 paddle_size  = {20, 80};

Vector2 ball_size = {20, 20};
Vector2 ball = {(float) SCREEN_WIDTH / 2, (float) SCREEN_HEIGHT / 2};
Vector2 ball_speed = {10, 10};

int player1_score = 0;
int player2_score = 0;
const int font_size = 100;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60);
    
    while(!WindowShouldClose()) {
		DrawText(TextFormat("%d", player1_score), SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100, font_size, WHITE);
		DrawText(TextFormat("%d", player2_score), SCREEN_WIDTH / 2 +  25, SCREEN_HEIGHT / 2 - 100, font_size, WHITE);
		
        control_paddle();
        
		if (collided(paddle1)) {
			ball_speed.x = - ball_speed.x;
			ball.x += ball_speed.x;
		}
		else if (collided(paddle2)) {
			ball_speed.x = - ball_speed.x;
			ball.x += ball_speed.x;
		}
		else {
			if (ball.x + ball_size.x >= SCREEN_WIDTH) {
				player1_score += 1;
				ball.x = (float) SCREEN_WIDTH / 2;
				ball.y = (float) SCREEN_HEIGHT / 2;
			} else if (ball.x <= 0) {
				player2_score += 1;
				ball.x = (float) SCREEN_WIDTH / 2;
				ball.y = (float) SCREEN_HEIGHT / 2;
			}
			if (ball.y + ball_size.y >= SCREEN_HEIGHT) {
				ball_speed.y = - ball_speed.y;
				ball.y = SCREEN_HEIGHT - ball_size.y;
			} else if (ball.y <= 0) {
				ball_speed.y = - ball_speed.y;
				ball.y = 0;
			}
			ball.x += ball_speed.x;
			ball.y += ball_speed.y;
		}

        BeginDrawing();
			ClearBackground(BLACK);
			DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, GRAY);
			DrawRectangleV(paddle1, paddle_size, WHITE);
			DrawRectangleV(paddle2, paddle_size, WHITE);
            DrawRectangleV(ball, ball_size, WHITE);
        EndDrawing();
    }

    return 0;
}

void control_paddle() {
    if (IsKeyDown(KEY_S) && (paddle1.y + paddle_size.y) <= SCREEN_HEIGHT) 
        paddle1.y += 15;
    if (IsKeyDown(KEY_W) && paddle1.y >= 0) 
        paddle1.y -= 15;
    if (IsKeyDown(KEY_DOWN) && (paddle2.y + paddle_size.y) <= SCREEN_HEIGHT)
        paddle2.y += 15;
    if (IsKeyDown(KEY_UP) && paddle2.y >= 0) 
        paddle2.y -= 15;    
}

bool collided(Vector2 paddle) {
	if (
			paddle.x <= (ball.x + ball_size.x)   && 
			(paddle.x + paddle_size.x) >= ball.x &&
			paddle.y <= (ball.y + ball_size.y)   &&
			(paddle.y + paddle_size.y) >= ball.y 
	   ) 
	{
		return true;
	}
	return false;
}
