#include "include/MainGameScreen.h"
#include "include/Game.h"
#include "include/Tetrominoes.h"
#include "include/Constants.h"

#include <iostream>

MainGameScreen::MainGameScreen(Game* currentGame) :
    Screen(currentGame), board(10, 25, 24), tetrominoes() {
    this->board.fillRandom();
    this->randomGenerator.initWithTetrominoes(&(this->tetrominoes));

    this->cur = this->randomGenerator.getNextTetromino();
}

void MainGameScreen::update(float dt) {

}

void MainGameScreen::draw(float alpha) {
    this->board.drawBoard(this->game->getRenderer(), 10, 10);
    this->drawTetromino(this->cur, 500, 50);
}

void MainGameScreen::handleKeypress(SDL_Keycode keycode) {
    switch(keycode) {
        case SDLK_SPACE:
            this->cur = this->randomGenerator.getNextTetromino();
        default:
            break;
    }
}

void MainGameScreen::drawTetromino(Tetromino* tetromino, int offsetX, int offsetY) {
    SDL_Renderer* renderer = this->getGame()->getRenderer();
    SDL_Rect rect;
    rect.w = this->board.getBlockSize();
    rect.h = this->board.getBlockSize();

    uint32_t color = tetromino->getColor();
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = (color) & 0xFF;

    std::vector<bool> rotationBox = tetromino->getRotationBox();
    for (int i = 0; i < tetromino->getShapeSize() * tetromino->getShapeSize(); i++) {
        if (rotationBox.at(i)) {
            int x = i % tetromino->getShapeSize();
            int y = i / tetromino->getShapeSize();
            rect.x = offsetX + x * this->board.getBlockSize();
            rect.y = offsetY + y * this->board.getBlockSize();

            SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

MainGameScreen::~MainGameScreen() {

}
