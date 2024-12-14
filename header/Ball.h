//
// Created by kesler on 4/11/24.
//

#ifndef BALL_H
#define BALL_H

#include "../header/GameObject.h"
#include "../header/Paddle.h"
#include "../header/constants.h"
#include "../header/SoundManager.h"

typedef struct {
    GameObject gameObject;
    float dx;
    float dy;
} Ball;

void Ball_Init (Ball *ball, float x, float y, float width, float height, float dx, float dy);
void Ball_Speed (Ball *ball, float speed, float time);
int Ball_CheckScore (Ball *ball, int windowWidth, int windowHeight, SoundManager *soundManager);
int Ball_CheckWin (int left_player_score, int right_player_score, int score_to_win);
void Ball_PaddleCollision (Ball *ball, Paddle *paddle, SoundManager *soundManager);
void Ball_BounceOfRectangles (Ball *ball, int window_width, int window_height, SoundManager *soundManager);
void Ball_BounceOfWalls (Ball *ball, int window_height, SoundManager *soundManager);

#endif //BALL_H
