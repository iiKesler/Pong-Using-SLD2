#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#include "../header/constants.h"
#include "../header/Ball.h"
#include "../header/Paddle.h"
#include "../header/RenderManager.h"
#include "../header/InputManager.h"
#include "../header/PowerUp.h"
#include "../header/PowerUp_SpeedBoost.h"
#include "../header/PowerUp_Size.h"
#include "../header/PowerUp_StopBall.h"
#include "../header/SoundManager.h"

/* The code for this game is going to be Air hockey.
 The game consists of a ball that moves around the screen and bounces off the walls.
 The player can move a paddle to hit the ball and prevent it from going off the screen.
 If the player misses the ball, it is 1 point to the other player.
 The game ends when one of the players reaches 10 points
 One paddle is on the left side, one on the right side.
 The ball always starts in the middle, and it's a 50% chance that it either goes to the left
 or to the right.
 The ball changes a direction when it hits the paddles.
 IJKL keys are used to move the right paddle.
 WASD keys are used to move the left paddle.

 State Machines
 The game is going to be divided into three main states:
 1. The main menu
 2. Game
 3. The game over screen */

typedef enum GameState{
    MENU,
    GAME,
    END
} GameState;

enum GameState current_state = MENU;

int game_is_running = FALSE;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

TTF_Font* font = NULL;

int last_frame_time = 0;

int left_player_score = 0;
int right_player_score = 0;

Uint32 last_collision_time = 0;
Uint32 powerUpSpawnTimer = 0;
PowerUp* activePowerUps[NUM_POWERUPS];

Ball ball;
Paddle left_paddle; // This is a struct variable for the left paddle, it moves with WASD keys
Paddle right_paddle; // This is a struct variable for the right paddle, it moves with IJKL keys
RenderManager renderManager;
PowerUp power_Up;
InputManager inputManager;
SoundManager soundManager;

int initialize_window (void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf (stderr, "Error initializing SDL:\n");
        return FALSE;
    }

    if (TTF_Init() == -1){
        fprintf (stderr, "Error initializing SDL TTF: %s \n", TTF_GetError());
        return FALSE;
    }

    // Create a SDL window
    window = SDL_CreateWindow (NULL,
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH,
                               WINDOW_HEIGHT,
                               SDL_WINDOW_BORDERLESS);
    if (!window) {
        fprintf (stderr, "Error creating SDL window:\n");
    }

    // Create a SDL renderer
    renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf (stderr, "Error creating SDL renderer:\n");
        return FALSE;
    }

    return TRUE;
}

void process_input (void) {
    SDL_Event event;
    const Uint8* state = SDL_GetKeyboardState(NULL);

    // Quitting the game
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                game_is_running = FALSE;
                break;
            case SDL_KEYDOWN:
                if (state[SDL_SCANCODE_ESCAPE]){
                    if(current_state == MENU){ // If we are in the menu, quit the game
                        game_is_running = FALSE;
                    } else { // If we are in the game, go back to the menu
                        current_state = MENU;
                    }
                }
                // Press 1 to start the game
                if (state[SDL_SCANCODE_1] && current_state == MENU){
                    current_state = GAME;
                }
                // Press SPACE to restart the game or quit from the END state
                if (state[SDL_SCANCODE_SPACE] && current_state == END){
                    left_player_score = 0;
                    right_player_score = 0;
                    current_state = GAME;
                }
                break;
        }
    }

    if (current_state != GAME){
        return;
    }

    // Moving the paddles
    InputManager_ProcessInput(&inputManager, &left_paddle, &right_paddle);
}

void setup (void) {
    font = TTF_OpenFont("./Fonts/Lucida Sans Unicode Regular.ttf", FONT_SIZE);
    if (font == NULL){
        fprintf(stderr, "Error loading font: %s\n", TTF_GetError());
        return;
    }

    srand(time(NULL)); // Seed the random number generator

    // Set the initial position of the ball
    Ball_Init (&ball, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 20, 20, rand() % 2 == 0 ? 1 : -1, rand() % 2 == 0 ? 1: -1);

    last_frame_time = SDL_GetTicks();

    // Set the initial position of the left paddle
    Paddle_Init (&left_paddle, WINDOW_WIDTH * 0.1, WINDOW_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT);

    // Set the initial position of the right paddle
    Paddle_Init (&right_paddle, WINDOW_WIDTH * 0.9 - 15, WINDOW_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT);

    // Initialize the render manager
    RenderManager_Init(&renderManager, renderer);

    // Initialize the input manager
    InputManager_Init(&inputManager);

    powerUpSpawnTimer = SDL_GetTicks();

    // Initialize the sound manager
    SoundManager_Init(&soundManager);
    SDL_CreateThread(play_background_music, "MusicThread", (void*)&soundManager);

    game_is_running = TRUE;
}

void update (void) {
    // Waste some time until we reach the target frame time
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    // Only call delay if we are too fast to process this frame
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    // Only update the game objects if we're in the GAME state
    if (current_state != GAME){
        return;
    }

    // Get a delta time factor converted to seconds to be used to update my objects
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    last_frame_time = SDL_GetTicks();

    // Speed of the ball
    Ball_Speed (&ball, BALL_SPEED, delta_time);

    // Bounce the ball at walls of the screen
    Ball_BounceOfWalls(&ball, WINDOW_HEIGHT, &soundManager);

    // Bounce the ball off the rectangles
    Ball_BounceOfRectangles(&ball, WINDOW_WIDTH, WINDOW_HEIGHT, &soundManager);

    // Bounce the ball off the paddles
    Ball_PaddleCollision(&ball, &left_paddle, &soundManager);
    Ball_PaddleCollision(&ball, &right_paddle, &soundManager);

    // Power Up Section

    // Check if it's time to spawn a new power-up based on the onScreen flag
    if (SDL_GetTicks() - powerUpSpawnTimer >= POWERUP_TIMER_TO_SPAWN) {
        // Check if there is already a power-up on the screen
        int isPowerUpOnScreen = 0;
        for (int i = 0; i < NUM_POWERUPS; i++) {
            if (activePowerUps[i] != NULL && activePowerUps[i]->onScreen) {
                isPowerUpOnScreen = 1;
                break;
            }
        }

        // If there is no power-up on the screen, spawn a new one
        if (!isPowerUpOnScreen){
            // Reset the spawn timer
            powerUpSpawnTimer = SDL_GetTicks();

            // Choose a random power-up type
            int powerUpType = rand() % NUM_POWERUPS;

            // Create a new power-up of the chosen type at the chosen position
            if (powerUpType == 0) { // Speed boost power-up
                PowerUp_SpeedBoost* powerUp = malloc(sizeof(PowerUp_SpeedBoost));
                PowerUp_SpeedBoost_Init(powerUp, &left_paddle);
                PowerUp_SpeedBoost_Init(powerUp, &right_paddle);
                powerUp->super.onScreen = 1; // Set onScreen to 1
                powerUp->super.isActive = 0; // Set isActive to 0
                activePowerUps[0] = (PowerUp*)powerUp; // Add powerUp to the list of active power-ups
            } else if (powerUpType == 1) { // Size power-up
                PowerUp_Size* powerUp = malloc(sizeof(PowerUp_Size));
                PowerUp_Size_Init(powerUp, &left_paddle);
                PowerUp_Size_Init(powerUp, &right_paddle);
                powerUp->super.onScreen = 1; // Set onScreen to 1
                powerUp->super.isActive = 0; // Set isActive to 0
                activePowerUps[1] = (PowerUp*)powerUp; // Add powerUp to the list of active power-ups
            } else if (powerUpType == 2) { // Stop ball power-up
                PowerUp_StopBall* powerUp = malloc(sizeof(PowerUp_StopBall));
                PowerUp_StopBall_Init(powerUp, &ball);
                powerUp->super.onScreen = 1; // Set onScreen to 1
                powerUp->super.isActive = 0; // Set isActive to 0
                activePowerUps[2] = (PowerUp*)powerUp; // Add powerUp to the list of active power-ups
            }
        }
    }

    // Check if the power up has collided with any of the paddles
    for (int i = 0; i < NUM_POWERUPS; i++) {
        if (activePowerUps[i] != NULL) {
            PowerUp_CheckCollision(activePowerUps[i], &left_paddle, &soundManager);
            PowerUp_CheckCollision(activePowerUps[i], &right_paddle, &soundManager);
        }
    }

    // Check if 5 seconds have passed since the power-up was picked up
    for (int i = 0; i < NUM_POWERUPS; i++) {
        if (activePowerUps[i] != NULL && activePowerUps[i]->isActive && SDL_GetTicks() - activePowerUps[i]->effectStartTime >= 5000) {
            // 5 seconds have passed, end the effect of the power-up
            activePowerUps[i]->vptr->endEffect(activePowerUps[i], &left_paddle);
            activePowerUps[i]->vptr->endEffect(activePowerUps[i], &right_paddle);
            activePowerUps[i]->isActive = 0;
            activePowerUps[i]->onScreen = 0;

            // Free the memory allocated for the power-up and set its pointer to NULL
            free(activePowerUps[i]);
            activePowerUps[i] = NULL;
        }
    }

    // Score: check if the ball has left either side of the screen and reset if necessary
    int score = Ball_CheckScore(&ball, WINDOW_WIDTH, WINDOW_HEIGHT, &soundManager);
    if (score != 0) {
        if (score == 1) {
            right_player_score++;
            printf("Right player score: %d\n", right_player_score);
        } else {
            left_player_score++;
            printf("Left player score: %d\n", left_player_score);
        }
        // Check if a player has won
        int win = Ball_CheckWin(left_player_score, right_player_score, SCORE_TO_WIN);
        if (win != 0) {
            if (win == 1) {
                printf("Left player wins!\n");
            } else {
                printf("Right player wins!\n");
            }
            current_state = END;
        }
    }

    // Restrict the movement of the left paddle
    Paddle_MovementRestriction(&left_paddle, WINDOW_WIDTH, WINDOW_HEIGHT, 1);

    // Restrict the movement of the right paddle
    Paddle_MovementRestriction(&right_paddle, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
}

void render (void) {
    SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Menu Rendering
    if (current_state == MENU){
        RenderManager_RenderMenu(&renderManager, font);
    }
    // Game Rendering
    else if (current_state == GAME ){
        // Draw the ball
        RenderManager_RenderBall (&renderManager, &ball);

        // Draw the left paddle
        RenderManager_RenderPaddle (&renderManager, &left_paddle);

        // Draw the right paddle
        RenderManager_RenderPaddle (&renderManager, &right_paddle);

        // Render the power-ups
        for (int i = 0; i < NUM_POWERUPS; i++) {
            if (activePowerUps[i] != NULL) {
                RenderManager_RenderPowerUp(&renderManager, activePowerUps[i]);
            }
        }

        // Draw the middle line
        RenderManager_RenderMiddleLine (&renderManager, WINDOW_WIDTH, WINDOW_HEIGHT);

        // Draw the top left goal area
        RenderManager_RenderGoalRect(&renderManager, 0, 0, (int)(WINDOW_WIDTH * 0.02), (int)(WINDOW_HEIGHT * 0.35));

        // Draw the bottom left goal area
        RenderManager_RenderGoalRect(&renderManager, 0, (int)(WINDOW_HEIGHT * 0.65), (int)(WINDOW_WIDTH * 0.02), (int)(WINDOW_HEIGHT * 0.35));

        // Draw the top right goal area
        RenderManager_RenderGoalRect(&renderManager, (int)(WINDOW_WIDTH * 0.98), 0, (int)(WINDOW_WIDTH * 0.02), (int)(WINDOW_HEIGHT * 0.35));

        // Draw the bottom right goal area
        RenderManager_RenderGoalRect(&renderManager, (int)(WINDOW_WIDTH * 0.98), (int)(WINDOW_HEIGHT * 0.65), (int)(WINDOW_WIDTH * 0.02), (int)(WINDOW_HEIGHT * 0.35));

        // Draw the score
        RenderManager_RenderScore(&renderManager, font, left_player_score, right_player_score);
    }
    // End Rendering
    else if (current_state == END){
        // Draw the end screen
        RenderManager_RenderEnd(&renderManager, font, left_player_score, right_player_score);
    }

    SDL_RenderPresent(renderer);
}

// Destroy the window
void destroy_window (void) {
    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    SDL_Quit ();
}

int main(int argc, char *argv[]){
    game_is_running = initialize_window();

    setup();

    while (game_is_running){
        process_input ();
        update ();
        render ();
    }

    destroy_window ();

    return 0;
}
