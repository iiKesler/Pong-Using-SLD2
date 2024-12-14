//
// Created by kesler on 4/18/24.
//

#include <assert.h>
#include <stdlib.h>

#include "../header/PowerUp.h"

static void PowerUp_applyEffect_(PowerUp const * const me, Paddle* paddle);
static void PowerUp_endEffect_(PowerUp const * const me, Paddle* paddle);

void PowerUp_Init(PowerUp* const me){
    static struct PowerUpVtbl const vtbl = {
        &PowerUp_applyEffect_,
        &PowerUp_endEffect_
    };
    me -> vptr = &vtbl;
    GameObject_Init(&me -> gameObject, rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT, 20, 20);
    me -> isActive = 0;
    me -> onScreen = 0;
    me -> effectStartTime = 0;
}

static void PowerUp_applyEffect_(PowerUp const * const me, Paddle* paddle){
    assert(0);
}

static void PowerUp_endEffect_(PowerUp const * const me, Paddle* paddle){
    assert(0);
}

void PowerUp_CheckCollision(PowerUp* powerUp, Paddle* paddle, SoundManager *soundManager){
    if (powerUp->gameObject.x < paddle->gameObject.x + paddle->gameObject.width &&
        powerUp->gameObject.x + powerUp->gameObject.width > paddle->gameObject.x &&
        powerUp->gameObject.y < paddle->gameObject.y + paddle->gameObject.height &&
        powerUp->gameObject.y + powerUp->gameObject.height > paddle->gameObject.y) {
        // Collision detected, apply the power-up effect to the paddle that collided with the power-up
        powerUp->vptr->applyEffect(powerUp, paddle);
        powerUp->isActive = 1;
        powerUp->onScreen = 0;
        powerUp->effectStartTime = SDL_GetTicks();

        SoundManager_PlayPowerUpSFX(soundManager);
    }
}