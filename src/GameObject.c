//
// Created by kesler on 4/11/24.
//

#include "../header/GameObject.h"

void GameObject_Init (GameObject *gameObject, float x, float y, float width, float height) {
    gameObject -> x = x;
    gameObject -> y = y;
    gameObject -> width = width;
    gameObject -> height = height;
}