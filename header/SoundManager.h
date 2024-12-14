//
// Created by kesler on 5/17/24.
//

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct SoundManager {
    Mix_Music *music;
    Mix_Chunk *sfx;
    SDL_sem *semaphore;
	Mix_Chunk *paddleHitSFX;
	Mix_Chunk *wallBounceSFX;
	Mix_Chunk *powerUpSFX;
	Mix_Chunk *scoreSFX;
} SoundManager;

void SoundManager_Init(SoundManager *soundManager);
void SoundManager_PlayMusic(SoundManager *soundManager, const char *filename);
void SoundManager_PlaySFX(SoundManager *soundManager, const char *filename);
void SoundManager_Cleanup(SoundManager *soundManager);
int play_background_music(void *data);
void SoundManager_PlayPaddleHitSFX(SoundManager *soundManager);
void SoundManager_PlayWallBounceSFX(SoundManager *soundManager);
void SoundManager_PlayPowerUpSFX(SoundManager *soundManager);
void SoundManager_PlayScoreSFX(SoundManager *soundManager);

#endif //SOUNDMANAGER_H
