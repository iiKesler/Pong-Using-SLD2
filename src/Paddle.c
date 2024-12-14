//
// Created by kesler on 4/11/24.
//

#include "../header/Paddle.h"
#include"../header/GameObject.h"
#include "../header/constants.h"

void Paddle_Init (Paddle *paddle, float x, float y, float width, float height) {
    GameObject_Init (&paddle -> gameObject, x, y, width, height);
    paddle -> speed = PADDLE_SPEED;
}

void Paddle_Move (Paddle *paddle, float dx, float dy){ // Move the paddle
    paddle -> gameObject.x += dx;
    paddle -> gameObject.y += dy;
}

void Paddle_MovementRestriction(Paddle *paddle, int window_width, int window_height, int is_left_paddle) {
    // Prevent paddle from moving beyond the middle of the screen
    if (is_left_paddle) {
        if (paddle -> gameObject.x < 0) {
            paddle -> gameObject.x = 0;
        }
        if (paddle -> gameObject.x > window_width / 2 - paddle -> gameObject.width) {
            paddle -> gameObject.x = window_width / 2 - paddle -> gameObject.width;
        }
        if (paddle -> gameObject.x < window_width * 0.02) {
            paddle -> gameObject.x = window_width * 0.02;
        }
        if (paddle -> gameObject.y < 0){
            paddle -> gameObject.y = 0;
        }
        if (paddle -> gameObject.y > window_height - paddle -> gameObject.height) {
            paddle -> gameObject.y = window_height - paddle -> gameObject.height;
        }
    } else {
        if (paddle -> gameObject.x < window_width / 2) {
            paddle -> gameObject.x = window_width / 2;
        }
        if (paddle -> gameObject.x > window_width - paddle -> gameObject.width) {
            paddle -> gameObject.x = window_width - paddle -> gameObject.width;
        }
        if (paddle -> gameObject.x > window_width * 0.98 - paddle -> gameObject.width) {
            paddle -> gameObject.x = window_width * 0.98 - paddle -> gameObject.width;
        }
        if (paddle -> gameObject.y < 0){
            paddle -> gameObject.y = 0;
        }
        if (paddle -> gameObject.y > window_height - paddle -> gameObject.height) {
            paddle -> gameObject.y = window_height - paddle -> gameObject.height;
        }
    }
}
