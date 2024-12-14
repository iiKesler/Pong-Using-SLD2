//
// Created by kesler on 4/18/24.
//

#include "../header/PowerUp_SpeedBoost.h"
#include "../header/constants.h"

static void PowerUp_SpeedBoost_applyEffect_(PowerUp const * const me, Paddle* paddle);
static void PowerUp_SpeedBoost_endEffect_(PowerUp const * const me, Paddle* paddle);

void PowerUp_SpeedBoost_Init(PowerUp_SpeedBoost * const me, Paddle* paddle){
    static struct PowerUpVtbl const vtbl = {
        &PowerUp_SpeedBoost_applyEffect_,
        &PowerUp_SpeedBoost_endEffect_
    };
    PowerUp_Init(&me -> super);
    me -> super.vptr = &vtbl;
    me -> paddle = paddle;
}

static void PowerUp_SpeedBoost_applyEffect_(PowerUp const * const me, Paddle* paddle){
    paddle -> speed = POWERUP_SPEEDBOOST_AMOUNT;
}

static void PowerUp_SpeedBoost_endEffect_(PowerUp const * const me, Paddle* paddle){
    paddle -> speed = PADDLE_SPEED;
}