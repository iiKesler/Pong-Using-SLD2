//
// Created by kesler on 4/11/24.
//

#ifndef PADDLE_H
#define PADDLE_H

#include "../header/GameObject.h"
#include "../header/constants.h"

typedef struct {
    GameObject gameObject;
    float speed;
} Paddle;

void Paddle_Init (Paddle *paddle, float x, float y, float width, float height);
void Paddle_Move (Paddle *paddle, float dx, float dy);
void Paddle_MovementRestriction (Paddle *paddle, int window_width, int window_height, int is_left_paddle);

#endif //PADDLE_H
