//
// Created by kesler on 4/18/24.
//

#ifndef POWERUP_SPEEDBOOST_H
#define POWERUP_SPEEDBOOST_H

#include "../header/PowerUp.h"
#include "../header/Paddle.h"

typedef struct{
    PowerUp super;
    Paddle* paddle;
} PowerUp_SpeedBoost;

void PowerUp_SpeedBoost_Init(PowerUp_SpeedBoost * const me, Paddle* paddle);

#endif //POWERUP_SPEEDBOOST_H
