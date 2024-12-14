//
// Created by kesler on 4/12/24.
//

#include "../header/InputManager.h"
#include "../header/Paddle.h"
#include "../header/constants.h"

void InputManager_Init (InputManager *inputManager){
    inputManager -> state = SDL_GetKeyboardState(NULL);
}

void InputManager_ProcessInput(InputManager* inputManager, Paddle* left_paddle, Paddle* right_paddle){
    // Moving the left paddle
    if (inputManager -> state[SDL_SCANCODE_W])
        Paddle_Move (left_paddle, 0, -left_paddle->speed);
    if (inputManager -> state[SDL_SCANCODE_S])
        Paddle_Move (left_paddle, 0, left_paddle->speed);
    if (inputManager -> state[SDL_SCANCODE_A])
        Paddle_Move (left_paddle, -left_paddle->speed, 0);
    if (inputManager -> state[SDL_SCANCODE_D])
        Paddle_Move (left_paddle, left_paddle->speed, 0);

    // Moving the right paddle
    if (inputManager -> state[SDL_SCANCODE_I])
        Paddle_Move (right_paddle, 0, -right_paddle->speed);
    if (inputManager -> state[SDL_SCANCODE_K])
        Paddle_Move (right_paddle, 0, right_paddle->speed);
    if (inputManager -> state[SDL_SCANCODE_J])
        Paddle_Move (right_paddle, -right_paddle->speed, 0);
    if (inputManager -> state[SDL_SCANCODE_L])
        Paddle_Move (right_paddle, right_paddle->speed, 0);
}

