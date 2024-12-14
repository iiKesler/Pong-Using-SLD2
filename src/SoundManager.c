//
// Created by kesler on 5/17/24.
//

#include "../header/SoundManager.h"

void SoundManager_Init(SoundManager *soundManager) {
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    Mix_AllocateChannels(16);

	soundManager->paddleHitSFX = Mix_LoadWAV("./Sounds/PaddleBounce_Sound.wav");
    if (soundManager->paddleHitSFX == NULL) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

	soundManager->wallBounceSFX = Mix_LoadWAV("./Sounds/WallBounce_Sound.wav");
    if (soundManager->wallBounceSFX == NULL) {
        printf("Failed to load wall bounce sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    soundManager->powerUpSFX = Mix_LoadWAV("./Sounds/PowerUpPickup_Sound.wav");
	if (soundManager->powerUpSFX == NULL) {
        printf("Failed to load power up sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    // Initialize the semaphore
    soundManager->semaphore = SDL_CreateSemaphore(1);
}

void SoundManager_PlayMusic(SoundManager *soundManager, const char *filename) {
    // Load the music
    soundManager->music = Mix_LoadMUS(filename);
    if (soundManager->music == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    }

    // Play the music
    Mix_PlayMusic(soundManager->music, -1);
}

void SoundManager_PlaySFX(SoundManager *soundManager, const char *filename) {
    // Load the sound effect
    soundManager->sfx = Mix_LoadWAV(filename);
    if (soundManager->sfx == NULL) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    // Play the sound effect
    Mix_PlayChannel(-1, soundManager->sfx, 0);
}

void SoundManager_Cleanup(SoundManager *soundManager) {
    // Free the music and sound effect
    Mix_FreeMusic(soundManager->music);
    Mix_FreeChunk(soundManager->sfx);
	Mix_FreeChunk(soundManager->paddleHitSFX);
	Mix_FreeChunk(soundManager->wallBounceSFX);
	Mix_FreeChunk(soundManager->powerUpSFX);
	Mix_FreeChunk(soundManager->scoreSFX);

    // Close SDL_mixer
    Mix_CloseAudio();

    // Destroy the semaphore
    SDL_DestroySemaphore(soundManager->semaphore);
}

int play_background_music(void *data) {
    SoundManager *soundManager = (SoundManager *)data;
    // Play the background music
    SoundManager_PlayMusic(soundManager, "./Sounds/BackgroundMusic_Sound.wav");

    return 0;
}

void SoundManager_PlayPaddleHitSFX(SoundManager *soundManager) {
    // Wait for the semaphore to become available
	SDL_SemWait(soundManager->semaphore);

    // Play the sound effect
    Mix_PlayChannel(-1, soundManager->paddleHitSFX, 0);

    // Release the semaphore
	SDL_SemPost(soundManager->semaphore);
}

void SoundManager_PlayWallBounceSFX(SoundManager *soundManager){
    // Wait for the semaphore to become available
    SDL_SemWait(soundManager->semaphore);

    // Play the sound effect
    Mix_PlayChannel(-1, soundManager->wallBounceSFX, 0);

    // Release the semaphore
    SDL_SemPost(soundManager->semaphore);
}

void SoundManager_PlayPowerUpSFX(SoundManager *soundManager){
    // Wait for the semaphore to become available
    SDL_SemWait(soundManager->semaphore);

    // Play the sound effect
    Mix_PlayChannel(-1, soundManager->powerUpSFX, 0);

    // Release the semaphore
    SDL_SemPost(soundManager->semaphore);
}

void SoundManager_PlayScoreSFX(SoundManager *soundManager){
    // Wait for the semaphore to become available
    SDL_SemWait(soundManager->semaphore);

    // Play the sound effect
    Mix_PlayChannel(-1, soundManager->scoreSFX, 0);

    // Release the semaphore
    SDL_SemPost(soundManager->semaphore);
}
