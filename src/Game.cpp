#include "include/Game.h"

Game::Game() {
    this->previousTick = 0;
    this->firstUpdate = true;
    this->currentScreen = NULL;
    this->elapsedDt = 0.0f;

    this->limitFramerate = true;
}

void Game::update(uint32_t currentTick) {
    if (this->firstUpdate) {
        this->previousTick = currentTick;
        this->firstUpdate = false;
    } else if(this->currentScreen) {
        uint32_t elapsedTick = currentTick - this->previousTick;
        float elapsedSeconds = elapsedTick / 1000.0f;
        this->previousTick = currentTick;

        if (this->limitFramerate) {
            this->currentScreen->update(Constants::SECONDS_PER_FRAME);
            this->currentScreen->draw(0.0f);

            int timeToWait = (Constants::SECONDS_PER_FRAME * 1000 - elapsedTick);
            if (timeToWait < 0) {
                timeToWait = 0;
            }

            SDL_Delay((uint32_t) timeToWait);
        } else {
            this->elapsedDt += elapsedSeconds;
            while (this->elapsedDt >= Constants::SECONDS_PER_FRAME) {
                this->elapsedDt -= Constants::SECONDS_PER_FRAME;
                this->currentScreen->update(Constants::SECONDS_PER_FRAME);
            }

            float alpha = this->elapsedDt / Constants::SECONDS_PER_FRAME;
            this->currentScreen->draw(alpha);
        }
    }
}

void Game::attachScreen(Screen* newScreen) {
    this->currentScreen = newScreen;
}

void Game::detachScreen() {
    this->currentScreen = NULL;
}

void Game::changeScreen(Screen* newScreen) {
    this->detachScreen();
    this->attachScreen(newScreen);
}

Game::~Game() {
    delete this->currentScreen;
    this->currentScreen = NULL;
}
