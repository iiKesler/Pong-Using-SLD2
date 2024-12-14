//
// Created by kesler on 4/18/24.
//

#include "../header/PowerUp_Size.h"

static void PowerUp_Size_applyEffect_(PowerUp const * const me, Paddle* paddle);
static void PowerUp_Size_endEffect_(PowerUp const * const me, Paddle* paddle);

void PowerUp_Size_Init(PowerUp_Size * const me, Paddle *paddle){
    static struct PowerUpVtbl const vtbl = {
            &PowerUp_Size_applyEffect_,
            &PowerUp_Size_endEffect_
    };
    PowerUp_Init(&me -> super);
    me -> super.vptr = &vtbl;
    me -> paddle = paddle;
}

static void PowerUp_Size_applyEffect_(PowerUp const * const me, Paddle* paddle){
    PowerUp_Size* me_ = (PowerUp_Size*)me;
    paddle -> gameObject.width = POWERUP_SIZE_AMOUNT_WIDTH;
    paddle -> gameObject.height = POWERUP_SIZE_AMOUNT_HEIGHT;
    me_->super.onScreen = 0;
}

static void PowerUp_Size_endEffect_(PowerUp const * const me, Paddle* paddle){
    PowerUp* me_ = (PowerUp*)me;
    paddle -> gameObject.width = PADDLE_WIDTH;
    paddle -> gameObject.height = PADDLE_HEIGHT;
    me_->isActive = 1;
}