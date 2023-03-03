#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>

#define SCREEN_WIDTH  1200.00
#define SCREEN_HEIGHT  900.00

void control_paddle();
void accelarate();
void reset_ball_speed();
void reset_score();

Rectangle paddle1 = {10.0, 10.0, 20.0, 80.0};
Rectangle paddle2 = {SCREEN_WIDTH - 30.0, SCREEN_HEIGHT - 70.0, 20.0, 80.0};

Rectangle ball = {SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0, 15.0, 15.0};
Vector2 ball_speed = {10, 10};

const float paddle_speed = 12;
const float accelaration_rate = 0.2;

int paddle1_score = 0;
int paddle2_score = 0;
int blink_counter = 0;

bool pause = 0;

int main() 
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "refactored pong");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_SPACE)) pause = !pause;		
		if (IsKeyDown(KEY_R)) reset_score();

		if (!pause) {
			control_paddle();
			if (CheckCollisionRecs(paddle1, ball)) {
				accelarate();
				ball_speed.x = - ball_speed.x;
				ball.x += ball_speed.x;
			}
			if (CheckCollisionRecs(paddle2, ball)) {
				accelarate();
				ball_speed.x = - ball_speed.x;
				ball.x += ball_speed.x;
			}
			if (paddle1_score != 10 && paddle2_score != 10) {
				if (ball.x + ball.width >= SCREEN_WIDTH) {
					reset_ball_speed();
					ball.x = SCREEN_WIDTH  / 2;
					ball.y = SCREEN_HEIGHT / 2;
					paddle1_score++;
				}
				else if (ball.x <= 0) {
					reset_ball_speed();
					ball_speed.y = - ball_speed.y;
					ball_speed.x = - ball_speed.x;
					ball.x = SCREEN_WIDTH  / 2;
					ball.y = SCREEN_HEIGHT / 2;
					paddle2_score++;
				}
				if (ball.y + ball.height >= SCREEN_HEIGHT) {
					ball_speed.y = - ball_speed.y;
					ball.y = SCREEN_HEIGHT - ball.height;
				}
				else if (ball.y <= 0) {
					ball_speed.y = - ball_speed.y;
					ball.y = 0;
				}
				ball.x += ball_speed.x;
				ball.y += ball_speed.y;
			}
			blink_counter = 0;
		}
		else 
			blink_counter++;

		BeginDrawing();
			ClearBackground(BLACK);
			for (int i = 0; i < SCREEN_HEIGHT; i += 3)
				if (i % 2) DrawPixel(SCREEN_WIDTH / 2, i, GRAY);

			if (pause && (blink_counter / 30) % 2) 
				DrawText("paused", SCREEN_WIDTH / 2.0 + 20, SCREEN_HEIGHT / 2.0 + 200, 80, WHITE);

			if (paddle1_score >= 10) {
				DrawText(TextFormat("%d", paddle1_score), SCREEN_WIDTH / 2 - 95, SCREEN_HEIGHT / 2 - 30, 80, GREEN);
				DrawText(TextFormat("%d", paddle2_score), SCREEN_WIDTH / 2 + 60, SCREEN_HEIGHT / 2 - 30, 80, GRAY);
				DrawText("press R to restart", SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 + 150, 40, PURPLE);
			}
			else if (paddle2_score >= 10) {
				DrawText(TextFormat("%d", paddle1_score), SCREEN_WIDTH / 2 - 95, SCREEN_HEIGHT / 2 - 30, 80, GRAY);
				DrawText(TextFormat("%d", paddle2_score), SCREEN_WIDTH / 2 + 60, SCREEN_HEIGHT / 2 - 30, 80, GREEN);
				DrawText("press 'r' to restart", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 80, GRAY);
			} 
			else {
				DrawText(TextFormat("%d", paddle1_score), SCREEN_WIDTH / 2 - 95, SCREEN_HEIGHT / 2 - 30, 80, GRAY);
				DrawText(TextFormat("%d", paddle2_score), SCREEN_WIDTH / 2 + 60, SCREEN_HEIGHT / 2 - 30, 80, GRAY);
				DrawRectangleRec(ball, WHITE);
			}
			DrawRectangleRec(paddle1, WHITE);
			DrawRectangleRec(paddle2, WHITE);
		EndDrawing();
	}


	return 0;
}

void control_paddle() {
	if (IsKeyDown(KEY_S) && (paddle1.y + paddle1.height) <= SCREEN_HEIGHT)
		paddle1.y += paddle_speed;
	else if (IsKeyDown(KEY_W) && paddle1.y >= 0)
		paddle1.y -= paddle_speed;
	
	if (IsKeyDown(KEY_DOWN) && (paddle2.y + paddle2.height) <= SCREEN_HEIGHT)
		paddle2.y += paddle_speed;
	else if (IsKeyDown(KEY_UP) && (paddle2.y >= 0)) 
		paddle2.y -= paddle_speed;
}

void accelarate() {
	if (ball_speed.x < 0) ball_speed.x -= accelaration_rate;
	else if (ball_speed.x > 0) ball_speed.x += accelaration_rate;

	if (ball_speed.y < 0) ball_speed.y -= accelaration_rate;
	else if (ball_speed.y > 0) ball_speed.y += accelaration_rate;
}

void reset_ball_speed() {
	ball_speed.x = 10;
	ball_speed.y = 10;
}

void reset_score() {
	paddle1_score = 0;
	paddle2_score = 0;
}
