//
// Created by kesler on 4/12/24.
//

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>
#include "../header/Paddle.h"

typedef struct{
    const Uint8* state;
}InputManager;

void InputManager_Init (InputManager *inputManager);
void InputManager_ProcessInput(InputManager* inputManager, Paddle* left_paddle, Paddle* right_paddle);

#endif //INPUTMANAGER_H
