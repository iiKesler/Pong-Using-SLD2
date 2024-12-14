//
// Created by kesler on 4/12/24.
//

#include "../header/RenderManager.h"
#include "../header/constants.h"

void RenderManager_Init(RenderManager* renderManager, SDL_Renderer* renderer) {
    renderManager -> renderer = renderer;
}

void RenderManager_RenderMenu(RenderManager* renderManager, TTF_Font* font) {
    SDL_Color color = {255, 255, 255, 255};

    // Render the title
    SDL_Surface* surface_title = TTF_RenderText_Solid(font, "Air Hockey Game", color);
    SDL_Texture* texture_title = SDL_CreateTextureFromSurface(renderManager->renderer, surface_title);
    SDL_Rect title_rect;
    title_rect.x = WINDOW_WIDTH / 2 - surface_title->w / 2;
    title_rect.y = WINDOW_HEIGHT / 3;
    title_rect.w = surface_title->w;
    title_rect.h = surface_title->h;
    SDL_RenderCopy(renderManager->renderer, texture_title, NULL, &title_rect);
    SDL_FreeSurface(surface_title);
    SDL_DestroyTexture(texture_title);

    // Render the instruction
    SDL_Surface* surface_instruction = TTF_RenderText_Solid(font, "Press 1 to start the game", color);
    SDL_Texture* texture_instruction = SDL_CreateTextureFromSurface(renderManager->renderer, surface_instruction);
    SDL_Rect instruction_rect;
    instruction_rect.x = WINDOW_WIDTH / 2 - surface_instruction->w / 2;
    instruction_rect.y = WINDOW_HEIGHT / 2;
    instruction_rect.w = surface_instruction->w;
    instruction_rect.h = surface_instruction->h;
    SDL_RenderCopy(renderManager->renderer, texture_instruction, NULL, &instruction_rect);
    SDL_FreeSurface(surface_instruction);
    SDL_DestroyTexture(texture_instruction);
}

void RenderManager_RenderBall(RenderManager* renderManager, Ball* ball) { // Drawing the ball
    SDL_Rect ball_rect = {
            (int) ball -> gameObject.x,
            (int) ball -> gameObject.y,
            (int) ball -> gameObject.width,
            (int) ball -> gameObject.height
    };
    SDL_SetRenderDrawColor(renderManager -> renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderManager -> renderer, &ball_rect);
}

void RenderManager_RenderPaddle(RenderManager* renderManager, Paddle* paddle) { // Drawing the paddles
    SDL_Rect paddle_rect = {
            (int) paddle -> gameObject.x,
            (int) paddle -> gameObject.y,
            (int) paddle -> gameObject.width,
            (int) paddle -> gameObject.height
    };
    SDL_SetRenderDrawColor(renderManager -> renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderManager -> renderer, &paddle_rect);
}

void RenderManager_RenderPowerUp(RenderManager* renderManager, PowerUp* powerUp) { // Drawing the powerups
    if (powerUp->onScreen) {
        SDL_Rect powerup_rect = {
                (int) powerUp -> gameObject.x,
                (int) powerUp -> gameObject.y,
                (int) powerUp -> gameObject.width,
                (int) powerUp -> gameObject.height
        };
        SDL_SetRenderDrawColor(renderManager -> renderer, 0, 255, 255, 255);
        SDL_RenderFillRect(renderManager -> renderer, &powerup_rect);
    }
}

void RenderManager_RenderMiddleLine(RenderManager* renderManager, int window_width, int window_height) { // Drawing the middle line
    for (int i = 0; i < window_height; i += 20) {
        SDL_Rect middle_line = {
                window_width / 2 - 2,
                i,
                4,
                10
        };
        SDL_SetRenderDrawColor(renderManager -> renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderManager -> renderer, &middle_line);
    }
}

void RenderManager_RenderGoalRect(RenderManager* renderManager, int x, int y, int width, int height){ // Drawing the goal rectangles
    SDL_Rect goal_rect = {
            x,
            y,
            width,
            height
    };
    SDL_SetRenderDrawColor (renderManager -> renderer, 0, 0, 0, 255);
    SDL_RenderFillRect (renderManager -> renderer, &goal_rect);
    SDL_SetRenderDrawColor (renderManager -> renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect (renderManager -> renderer, &goal_rect);
}

void RenderManager_RenderScore (RenderManager* renderManager, TTF_Font* font, int left_score, int right_score) { // Drawing the score
    char score_text_left[50];
    sprintf(score_text_left, "Left player:  %d", left_score);

    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface_left = TTF_RenderText_Solid(font, score_text_left, color);
    SDL_Texture* texture_left = SDL_CreateTextureFromSurface(renderManager -> renderer, surface_left);

    int score_text_y = 20;
    int score_text_x = 20;

    int text_width_left = surface_left -> w;
    int text_height_left = surface_left -> h;
    SDL_FreeSurface(surface_left);

    SDL_Rect dst_left = {score_text_x, score_text_y, text_width_left, text_height_left};
    SDL_RenderCopy(renderManager -> renderer, texture_left, NULL, &dst_left);

    SDL_DestroyTexture(texture_left);

    char score_text_right[50];
    sprintf(score_text_right, "Right player:  %d", right_score);

    SDL_Surface* surface_right = TTF_RenderText_Solid(font, score_text_right, color);
    SDL_Texture* texture_right = SDL_CreateTextureFromSurface(renderManager -> renderer, surface_right);

    int text_width_right = surface_right -> w;
    int text_height_right = surface_right -> h;
    SDL_FreeSurface(surface_right);

    SDL_Rect dst_right = {WINDOW_WIDTH - text_width_right - score_text_x, score_text_y, text_width_right, text_height_right};
    SDL_RenderCopy(renderManager -> renderer, texture_right, NULL, &dst_right);

    SDL_DestroyTexture(texture_right);
}

void RenderManager_RenderEnd (RenderManager* renderManager, TTF_Font* font, int left_score, int right_score){ // Drawing the end scene
    SDL_Color color = {255, 255, 255, 255};

    // Render the game over text
    char end_text[50];
    if (left_score >= SCORE_TO_WIN){
        sprintf(end_text, "Left player wins!");
    } else {
        sprintf(end_text, "Right player wins!");
    }
    SDL_Surface* surface_end = TTF_RenderText_Solid (font, end_text, color);
    SDL_Texture* texture_end =SDL_CreateTextureFromSurface (renderManager -> renderer, surface_end);
    SDL_Rect end_rect;
    end_rect.x = WINDOW_WIDTH / 2 - surface_end -> w / 2;
    end_rect.y = WINDOW_HEIGHT / 3;
    end_rect.w = surface_end -> w;
    end_rect.h = surface_end -> h;
    SDL_RenderCopy (renderManager -> renderer, texture_end, NULL, &end_rect);
    SDL_FreeSurface (surface_end);
    SDL_DestroyTexture (texture_end);

    // Render the restart instruction

    SDL_Surface* surface_restart = TTF_RenderText_Solid (font, "Press SPACE to restart the game", color);
    SDL_Texture* texture_restart = SDL_CreateTextureFromSurface (renderManager -> renderer, surface_restart);
    SDL_Rect restart_rect;
    restart_rect.x = WINDOW_WIDTH / 2 - surface_restart -> w / 2;
    restart_rect.y = WINDOW_HEIGHT / 2;
    restart_rect.w = surface_restart -> w;
    restart_rect.h = surface_restart -> h;
    SDL_RenderCopy (renderManager -> renderer, texture_restart, NULL, &restart_rect);
    SDL_FreeSurface (surface_restart);
    SDL_DestroyTexture (texture_restart);

    // Render the quit instruction
    SDL_Surface* surface_quit = TTF_RenderText_Solid (font, "Press ESC to quit the game", color);
    SDL_Texture* texture_quit = SDL_CreateTextureFromSurface (renderManager -> renderer, surface_quit);
    SDL_Rect quit_rect;
    quit_rect.x = WINDOW_WIDTH / 2 - surface_quit -> w / 2;
    quit_rect.y = WINDOW_HEIGHT / 2 + 50;
    quit_rect.w = surface_quit -> w;
    quit_rect.h = surface_quit -> h;
    SDL_RenderCopy (renderManager -> renderer, texture_quit, NULL, &quit_rect);
    SDL_FreeSurface (surface_quit);
    SDL_DestroyTexture (texture_quit);
}
