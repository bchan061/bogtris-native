#include "include/MainGameScreen.h"
#include "include/Game.h"
#include "include/Tetrominoes.h"
#include "include/Constants.h"

#include <iostream>

MainGameScreen::MainGameScreen(Game* currentGame) :
    Screen(currentGame), board(10, 25, 24), tetrominoes() {
    this->randomGenerator.initWithTetrominoes(&(this->tetrominoes));
    this->boardOffset = {
        Constants::SCREEN_WIDTH / 2 -
            (this->board.getBoardWidth() * this->board.getBlockSize()) / 2,
        Constants::SCREEN_HEIGHT / 2 -
            ((this->board.getBoardHeight() - this->board.getObscuredTop()) * this->board.getBlockSize()) / 2
    };
    this->heldTetromino = NULL;

    this->getNextTetromino();
}

void MainGameScreen::getNextTetromino() {
    this->board.checkLineClears();
    this->hasHeld = false;
    this->spawnInTetromino(this->randomGenerator.getNextTetromino());
}

void MainGameScreen::spawnInTetromino(Tetromino* tetromino) {
    this->currentTetromino = tetromino;
    this->tetrominoes.setLocationToSpawningLocation(
        &(this->board),
        this->currentTetromino,
        this->currentTetrominoLocation
    );
}

void MainGameScreen::hold() {
    if (!this->hasHeld) {
        if (this->heldTetromino) {
            Tetromino* nextHeldTetromino = this->currentTetromino;
            this->spawnInTetromino(this->heldTetromino);
            this->heldTetromino = nextHeldTetromino;
        } else {
            this->heldTetromino = this->currentTetromino;
            this->spawnInTetromino(this->randomGenerator.getNextTetromino());
        }
    }
    this->hasHeld = true;
}

void MainGameScreen::update(float dt) {

}

void MainGameScreen::draw(float alpha) {
    this->board.drawBoard(this->game->getRenderer(), this->boardOffset);
    this->drawTetromino(this->currentTetromino, this->currentTetrominoLocation);
}

void MainGameScreen::handleKeypress(SDL_Keycode keycode) {
    SDL_Point offset;
    switch(keycode) {
        case SDLK_SPACE:
            this->hold();
            break;
        case SDLK_LEFT:
            offset.x = -1;
            offset.y = 0;
            TetrominoOperations::tryMove(this->board, *(this->currentTetromino), this->currentTetrominoLocation, offset);
            break;
        case SDLK_RIGHT:
            offset.x = 1;
            offset.y = 0;
            TetrominoOperations::tryMove(this->board, *(this->currentTetromino), this->currentTetrominoLocation, offset);
            break;
        case SDLK_z:
            TetrominoOperations::tryRotate(this->board, *(this->currentTetromino), this->currentTetrominoLocation, false);
            break;
        case SDLK_x:
            TetrominoOperations::tryRotate(this->board, *(this->currentTetromino), this->currentTetrominoLocation, true);
            break;
        case SDLK_UP:
            if (TetrominoOperations::hardDrop(this->board, *(this->currentTetromino), this->currentTetrominoLocation)) {
                this->getNextTetromino();
            }
            break;
        case SDLK_DOWN:
            if (TetrominoOperations::softDrop(this->board, *(this->currentTetromino), this->currentTetrominoLocation)) {
                this->getNextTetromino();
            }
            break;
        default:
            break;
    }
}

void MainGameScreen::drawTetromino(Tetromino* tetromino, SDL_Point& position) {
    SDL_Renderer* renderer = this->getGame()->getRenderer();
    SDL_Rect rect;
    rect.w = this->board.getBlockSize();
    rect.h = this->board.getBlockSize();

    uint32_t color = tetromino->getColor();
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = (color) & 0xFF;

    int pixelRelativeX = this->boardOffset.x + position.x * this->board.getBlockSize();
    int pixelRelativeY = this->boardOffset.y + position.y * this->board.getBlockSize();

    std::vector<bool>* rotationBox = tetromino->getRotationBox();
    for (int i = 0; i < tetromino->getShapeSize() * tetromino->getShapeSize(); i++) {
        if (rotationBox->at(i)) {
            int x = i % tetromino->getShapeSize();
            int y = i / tetromino->getShapeSize();
            rect.x = pixelRelativeX + x * this->board.getBlockSize();
            rect.y = pixelRelativeY + (y - this->board.getObscuredTop()) * this->board.getBlockSize();

            SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

MainGameScreen::~MainGameScreen() {

}
