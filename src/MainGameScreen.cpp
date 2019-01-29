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

    this->perpetualDropTimer = Timer(std::bind(&MainGameScreen::perpetualDrop, this), 2.0f);
    this->softDropTimer = Timer(std::bind(&MainGameScreen::softDrop, this), Constants::SECONDS_PER_FRAME * 2);
    this->dasLeftTimer = Timer(std::bind(&MainGameScreen::dasLeft, this), Constants::Timings::ARR);
    this->dasRightTimer = Timer(std::bind(&MainGameScreen::dasRight, this), Constants::Timings::ARR);

    this->getNextTetromino();
}

void MainGameScreen::getNextTetromino() {
    this->board.checkLineClears();
    this->hasHeld = false;
    this->spawnInTetromino(this->randomGenerator.getNextTetromino());

    this->perpetualDropTimer.reset();
}

void MainGameScreen::perpetualDrop() {
    TetrominoOperations::softDrop(this->board, *(this->currentTetromino), this->currentTetrominoLocation);
}

void MainGameScreen::dasLeft() {
    SDL_Point offset = { -1, 0 };
    TetrominoOperations::tryMove(this->board, *(this->currentTetromino), this->currentTetrominoLocation, offset);
}

void MainGameScreen::dasRight() {
    SDL_Point offset = { 1, 0 };
    TetrominoOperations::tryMove(this->board, *(this->currentTetromino), this->currentTetrominoLocation, offset);
}

void MainGameScreen::spawnInTetromino(Tetromino* tetromino) {
    this->currentTetromino = tetromino;
    tetromino->reset();
    this->tetrominoes.setLocationToSpawningLocation(
        &(this->board),
        this->currentTetromino,
        this->currentTetrominoLocation
    );
}

void MainGameScreen::softDrop() {
    TetrominoOperations::softDrop(this->board, *(this->currentTetromino), this->currentTetrominoLocation);
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
    this->handleKeystate();
    this->perpetualDropTimer.update(dt);
    this->softDropTimer.update(dt);
    this->dasLeftTimer.update(dt);
    this->dasRightTimer.update(dt);
}

void MainGameScreen::draw(float alpha) {
    this->board.drawBoard(this->game->getRenderer(), this->boardOffset);
    this->renderGhostPieces(this->currentTetromino, this->currentTetrominoLocation);
    this->drawTetromino(this->currentTetromino, this->currentTetrominoLocation);
}

void MainGameScreen::handleKeystate() {
    const uint8_t* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_LEFT]) {
        this->dasLeftTimer.activate();
    } else {
        this->dasLeftTimer.deactivate();
        this->dasLeftTimer.setCountdown(Constants::Timings::DAS);
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        this->dasRightTimer.activate();
    } else {
        this->dasRightTimer.deactivate();
        this->dasRightTimer.setCountdown(Constants::Timings::DAS);
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        this->softDropTimer.activate();
    } else {
        this->softDropTimer.deactivate();
        this->softDropTimer.reset();
    }
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

void MainGameScreen::renderGhostPieces(Tetromino* tetromino, SDL_Point& position) {
    SDL_Renderer* renderer = this->getGame()->getRenderer();
    SDL_Rect rect;
    rect.w = this->board.getBlockSize();
    rect.h = this->board.getBlockSize();

    uint32_t color = tetromino->getColor();
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = (color) & 0xFF;
    SDL_Point finalPoint = { position.x, position.y };
    int offset = 0;
    while (!this->board.tetrominoCollides(*tetromino, finalPoint)) {
        offset += 1;
        finalPoint.y += 1;
    }

    finalPoint.y -= 1;
    offset -= 1;

    if (offset <= 0) {
        /* Don't draw the ghost pieces if the piece is right above the floor. */
        return;
    }

    int pixelRelativeX = this->boardOffset.x + finalPoint.x * this->board.getBlockSize();
    int pixelRelativeY = this->boardOffset.y + finalPoint.y * this->board.getBlockSize();

    std::vector<bool>* rotationBox = tetromino->getRotationBox();
    for (int i = 0; i < tetromino->getShapeSize() * tetromino->getShapeSize(); i++) {
        if (rotationBox->at(i)) {
            int x = i % tetromino->getShapeSize();
            int y = i / tetromino->getShapeSize();
            rect.x = pixelRelativeX + x * this->board.getBlockSize();
            rect.y = pixelRelativeY + (y - this->board.getObscuredTop()) * this->board.getBlockSize();

            SDL_SetRenderDrawBlendMode(this->game->getRenderer(), SDL_BLENDMODE_BLEND);

            SDL_SetRenderDrawColor(renderer, r, g, b, 0x44);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

MainGameScreen::~MainGameScreen() {

}
