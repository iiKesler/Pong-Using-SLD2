//
// Created by andre on 29/02/2024.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FALSE 0
#define TRUE 1

// Window constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Game constants
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)
#define COLLISION_TIMER 2000
#define SCORE_TO_WIN 5

// Ball constants
#define BALL_SPEED 300
#define RESPAWN_DELAY 2000

// Paddle constants
#define PADDLE_SPEED 6
#define PADDLE_WIDTH 18
#define PADDLE_HEIGHT 60

// Font constants
#define FONT_SIZE 24

// Power-ups
#define NUM_POWERUPS 3
#define POWERUP_TIMER_TO_SPAWN 10000
#define POWERUP_SPEEDBOOST_AMOUNT (int)(PADDLE_SPEED * 1.50)
#define POWERUP_SIZE_AMOUNT_WIDTH (int)(PADDLE_WIDTH * 1.50)
#define POWERUP_SIZE_AMOUNT_HEIGHT (int)(PADDLE_HEIGHT * 1.50)

#endif //CONSTANTS_H
