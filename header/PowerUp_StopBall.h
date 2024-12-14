//
// Created by kesler on 4/20/24.
//

#ifndef POWERUP_STOPBALL_H
#define POWERUP_STOPBALL_H

#include "PowerUp.h"
#include "Ball.h"

typedef struct{
    PowerUp super;
    Ball *ball;
} PowerUp_StopBall;

void PowerUp_StopBall_Init(PowerUp_StopBall * const me, Ball *ball);

#endif //POWERUP_STOPBALL_H
