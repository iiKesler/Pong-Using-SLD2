//
// Created by kesler on 4/12/24.
//

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../header/Ball.h"
#include "../header/Paddle.h"
#include "../header/PowerUp.h"

typedef struct {
    SDL_Renderer *renderer;
} RenderManager;

void RenderManager_Init (RenderManager* renderManager, SDL_Renderer* renderer);
void RenderManager_RenderMenu(RenderManager* renderManager, TTF_Font* font);
void RenderManager_RenderBall (RenderManager* renderManager, Ball* ball);
void RenderManager_RenderPaddle (RenderManager* renderManager, Paddle* paddle);
void RenderManager_RenderPowerUp (RenderManager* renderManager, PowerUp* powerUp);
void RenderManager_RenderMiddleLine (RenderManager* renderManager, int window_width, int window_height);
void RenderManager_RenderGoalRect (RenderManager* renderManager, int x, int y, int width, int height);
void RenderManager_RenderScore (RenderManager* renderManager, TTF_Font* font, int left_score, int right_score);
void RenderManager_RenderEnd (RenderManager* renderManager, TTF_Font* font, int left_score, int right_score);

#endif //RENDERMANAGER_H
