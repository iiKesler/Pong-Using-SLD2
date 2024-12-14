//
// Created by kesler on 4/18/24.
//

#ifndef POWERUP_SIZE_H
#define POWERUP_SIZE_H

#include "PowerUp.h"
#include "Paddle.h"

typedef struct{
    PowerUp super;
    Paddle *paddle;
} PowerUp_Size;

void PowerUp_Size_Init(PowerUp_Size * const me, Paddle *paddle);

#endif //POWERUP_SIZE_H
