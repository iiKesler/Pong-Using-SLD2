//
// Created by kesler on 4/11/24.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

typedef struct {
    float x;
    float y;
    float width;
    float height;
} GameObject;

void GameObject_Init (GameObject *gameObject, float x, float y, float width, float height);

#endif //GAMEOBJECT_H
