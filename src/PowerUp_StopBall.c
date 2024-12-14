//
// Created by kesler on 4/20/24.
//

#include "../header/PowerUp_StopBall.h"

static void PowerUp_StopBall_applyEffect_(PowerUp const * const me, Paddle* paddle);
static void PowerUp_StopBall_endEffect_(PowerUp const * const me, Paddle* paddle);

void PowerUp_StopBall_Init(PowerUp_StopBall * const me, Ball* ball){
    static struct PowerUpVtbl const vtbl = {
            &PowerUp_StopBall_applyEffect_,
            &PowerUp_StopBall_endEffect_
    };
    PowerUp_Init(&me -> super);
    me -> super.vptr = &vtbl;
    me -> ball = ball;
}

static void PowerUp_StopBall_applyEffect_(PowerUp const * const me, Paddle* paddle){
    PowerUp_StopBall *me_ = (PowerUp_StopBall*)me;
    me_ -> ball -> dx = 0;
    me_ -> ball -> dy = 0;
}

static void PowerUp_StopBall_endEffect_(PowerUp const * const me, Paddle* paddle){
    // Do nothing as the ball will be set in motion again when it is hit by a paddle
}
