#include "include/Board.h"

Board::Board(int width, int height, int size) {
    this->boardWidth = width;
    this->boardHeight = height;
    this->blockSize = size;

    this->rowVector.reserve(this->boardHeight);
    for (int y = 0; y < this->boardHeight; y++) {
        Row row = Row(this->boardWidth);
        this->rowVector.push_back(row);
    }
}

Block* Board::getBlock(int x, int y) {
    if (y < 0 || y >= this->boardHeight) {
        return NULL;
    }

    return this->rowVector.at(y).getBlock(x);
}

void Board::fillRandom() {
    for (int y = 0; y < this->boardHeight; y++) {
        for (int x = 0; x < this->boardWidth; x++) {
            Block* block = this->getBlock(x, y);
            if (block) {
                block->reset();

                /* Set a random color. */
                block->set(rand() % 0xFFFFFF);
            }
        }
    }
}

void Board::drawBoard(SDL_Renderer* renderer, int offsetX, int offsetY) {
    SDL_Rect blockRect;
    blockRect.w = this->blockSize;
    blockRect.h = this->blockSize;
    for (int y = this->hiddenTop; y < this->boardHeight; y++) {
        for (int x = 0; x < this->boardWidth; x++) {
            Block* block = this->getBlock(x, y);
            blockRect.x = offsetX + x * this->blockSize;
            blockRect.y = offsetY + (y - this->hiddenTop) * this->blockSize;

            SDL_SetRenderDrawColor(renderer, block->getRed(), block->getGreen(), block->getBlue(), 255);
            SDL_RenderFillRect(renderer, &blockRect);
        }
    }
}

Board::~Board() {

}
