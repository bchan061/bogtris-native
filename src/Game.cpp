#include "include/Game.h"

Game::Game() {
    this->previousTick = 0;
    this->firstUpdate = true;
    this->currentScreen = NULL;
    this->elapsedDt = 0.0f;
}

void Game::update(uint32_t currentTick) {
    if (this->firstUpdate) {
        this->previousTick = currentTick;
        this->firstUpdate = false;
    } else if(this->currentScreen) {
        uint32_t elapsedTick = currentTick - this->previousTick;
        this->previousTick = currentTick;

        this->elapsedDt += (elapsedTick / 1000.0f);
        while (this->elapsedDt >= Constants::SECONDS_PER_FRAME) {
            this->elapsedDt -= Constants::SECONDS_PER_FRAME;
            this->currentScreen->update(Constants::SECONDS_PER_FRAME);
        }

        float alpha = this->elapsedDt / Constants::SECONDS_PER_FRAME;
        this->currentScreen->draw(alpha);
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

}
