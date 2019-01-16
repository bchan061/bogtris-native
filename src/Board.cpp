#include "include/Board.h"

Board::Board(int width, int height, int size) {
    this->boardWidth = width;
    this->boardHeight = height;
    this->blockSize = size;
    this->blockArray = new Block*[this->boardHeight];
    for (int y = 0; y < this->boardHeight; y++) {
        this->blockArray[y] = new Block[this->boardWidth];
    }
}

void Board::fillRandom() {
    for (int y = 0; y < this->boardHeight; y++) {
        for (int x = 0; x < this->boardWidth; x++) {
            Block* block = &(this->blockArray[y][x]);
            block->reset();

            /* Set a random color. */
            block->set(rand() % 0xFFFFFF);
        }
    }
}

void Board::drawBoard(SDL_Renderer* renderer, int offsetX, int offsetY) {
    SDL_Rect blockRect;
    blockRect.w = this->blockSize;
    blockRect.h = this->blockSize;
    for (int y = this->hiddenTop; y < this->boardHeight; y++) {
        for (int x = 0; x < this->boardWidth; x++) {
            Block block = this->blockArray[y][x];
            blockRect.x = offsetX + x * this->blockSize;
            blockRect.y = offsetY + (y - this->hiddenTop) * this->blockSize;

            SDL_SetRenderDrawColor(renderer, block.getRed(), block.getGreen(), block.getBlue(), 255);
            SDL_RenderFillRect(renderer, &blockRect);
        }
    }
}

Board::~Board() {
    for (int y = 0; y < this->boardHeight; y++) {
        delete[] this->blockArray[y];
    }

    delete[] this->blockArray;
}
