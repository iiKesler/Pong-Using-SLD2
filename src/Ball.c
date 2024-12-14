//
// Created by kesler on 4/11/24.
//

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "../header/Ball.h"


// Set the initial position of the ball
void Ball_Init (Ball *ball, float x, float y, float width, float height, float dx, float dy){ // Set the initial position of the ball
    GameObject_Init(&ball -> gameObject, x, y, width, height);
    ball -> dx = dx;
    ball -> dy = dy;
}

void Ball_Speed (Ball *ball, float speed, float time){ // Speed calc of the ball
    ball -> gameObject.x += ball -> dx * speed * time;
    ball -> gameObject.y += ball -> dy * speed * time;
}

int Ball_CheckScore (Ball *ball, int windowWidth, int windowHeight, SoundManager *soundManager){ // Check if the ball has scored
    // and reset the position
    if (ball -> gameObject.x < 0){
        ball -> gameObject.x = windowWidth / 2;
        ball -> gameObject.y = windowHeight / 2;

        // Randomize the direction of the ball
        srand (time(NULL));
        ball -> dx = (rand() % 2 == 0) ? 1 : -1;
        ball -> dy = (rand() % 2 == 0) ? 1 : -1;

		SoundManager_PlayScoreSFX(soundManager);

        return 1;
    } else if (ball->gameObject.x > windowWidth){
        ball -> gameObject.x = windowWidth / 2;
        ball -> gameObject.y = windowHeight / 2;

        // Randomize the direction of the ball
        srand(time(NULL));
        ball -> dx = (rand() % 2 == 0) ? 1 : -1;
        ball -> dy = (rand() % 2 == 0) ? 1 : -1;

		SoundManager_PlayScoreSFX(soundManager);

        return -1;
    }
    return 0;
}

int Ball_CheckWin (int left_player_score, int right_player_score, int score_to_win){ // Check if a player has reached the score to win
    if (left_player_score >= score_to_win){
        return -1;
    } else if (right_player_score >= score_to_win){
        return 1;
    }
    return 0;
}

void Ball_BounceOfWalls (Ball *ball, int window_height, SoundManager *soundManager){ // Check if the ball has hit the upper or lower parts of the screen
    if (ball -> gameObject.y <= 0){
        ball -> dy = -ball -> dy;
        ball -> gameObject.y = 0.02;
    }
    else if (ball -> gameObject.y >= window_height - ball -> gameObject.height){
        ball -> dy = -ball -> dy;
        ball -> gameObject.y = window_height - ball -> gameObject.height - 0.02;
    }

	SoundManager_PlayWallBounceSFX(soundManager);
}

void Ball_PaddleCollision (Ball *ball, Paddle *paddle, SoundManager *soundManager){ // Check if the ball has collided with the paddle
    if (ball -> gameObject.x <= paddle -> gameObject.x + paddle -> gameObject.width &&
        ball -> gameObject.x + ball -> gameObject.width >= paddle -> gameObject.x &&
        ball -> gameObject.y <= paddle -> gameObject.y + paddle -> gameObject.height &&
        ball -> gameObject.y + ball -> gameObject.height >= paddle -> gameObject.y){
        // If the ball's dx and dy are 0 (the ball is stopped), reset them to a random direction
        if (ball -> dx == 0 && ball -> dy == 0) {
            srand(time(NULL));
            ball -> dx = (rand() % 2 == 0) ? 1 : -1;
            ball -> dy = (rand() % 2 == 0) ? 1 : -1;
        } else {
            ball -> dx = -ball -> dx;
        }
        float relative_intersect_y = (paddle -> gameObject.y + (paddle -> gameObject.height / 2)) - (ball -> gameObject.y + (ball -> gameObject.height / 2));
        float normalized_intersect_y = -1 * (relative_intersect_y / (paddle -> gameObject.height / 2));
        ball -> dy = normalized_intersect_y;

		SoundManager_PlayPaddleHitSFX(soundManager);
        SDL_Delay (20);
    }
}

void Ball_BounceOfRectangles (Ball *ball, int window_width, int window_height, SoundManager *soundManager){ // Check if the ball has collided with the walls
    if ((ball -> gameObject.x <= window_width * 0.02 &&
        ((ball -> gameObject.y <= window_height * 0.35) ||
         (ball -> gameObject.y + ball->gameObject.height >= window_height * 0.65))) ||
        (ball -> gameObject.x + ball->gameObject.width >= window_width * 0.98 &&
         ((ball -> gameObject.y <= window_height * 0.35) ||
          (ball -> gameObject.y + ball -> gameObject.height >= window_height * 0.65)))) {
        ball -> dx = -ball -> dx;
        if (ball -> dx > 0){
            ball -> gameObject.x = window_width * 0.02;
        } else {
            ball -> gameObject.x = window_width * 0.98 - ball -> gameObject.width;
        }

		SoundManager_PlayWallBounceSFX(soundManager);
    }
}
