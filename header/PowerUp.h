//
// Created by kesler on 4/18/24.
//

#ifndef POWERUP_H
#define POWERUP_H

#include <stdint.h>
#include <SDL2/SDL.h>

#include "../header/GameObject.h"
#include "../header/Paddle.h"
#include "../header/SoundManager.h"

struct PowerUpVtbl;

typedef struct{
    struct PowerUpVtbl const *vptr;
    GameObject gameObject;
    int isActive;
    int onScreen;
    Uint32 effectStartTime;
} PowerUp;

struct PowerUpVtbl{
    void(*applyEffect)(PowerUp const * const me, Paddle* paddle);
    void(*endEffect)(PowerUp const * const me, Paddle* paddle);
};

void PowerUp_Init(PowerUp * const me);
void PowerUp_applyEffect(PowerUp const * const me, Paddle* paddle);
void PowerUp_endEffect(PowerUp const * const me, Paddle* paddle);
void PowerUp_CheckCollision(PowerUp* powerUp, Paddle* paddle, SoundManager *soundManager);

#endif //POWERUP_H
