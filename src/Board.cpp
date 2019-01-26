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

void Board::drawBoard(SDL_Renderer* renderer, SDL_Point offset) {
    SDL_Rect boardRect;
    boardRect.x = offset.x;
    boardRect.y = offset.y;
    boardRect.w = this->boardWidth * this->blockSize;
    boardRect.h = (this->boardHeight - this->hiddenTop) * this->blockSize;
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &boardRect);

    SDL_Rect blockRect;
    blockRect.w = this->blockSize;
    blockRect.h = this->blockSize;
    std::vector<Row>* rows = &(this->rowVector);
    for (int y = 0; y < this->boardHeight; y++) {
        Row* row = &(rows->at(y));
        for (int x = 0; x < this->boardWidth; x++) {
            Block* block = row->getBlock(x);

            if (block->isActive()) {
                blockRect.x = offset.x + x * this->blockSize;
                blockRect.y = offset.y + (y - this->hiddenTop) * this->blockSize;

                SDL_SetRenderDrawColor(renderer, block->getRed(), block->getGreen(), block->getBlue(), 255);
                SDL_RenderFillRect(renderer, &blockRect);
            }
        }
    }
}

bool Board::tetrominoCollides(Tetromino& tetromino, SDL_Point& location) {
    std::vector<bool>* tetrominoBoolArray = tetromino.getRotationBox();
    for (unsigned int i = 0; i < tetrominoBoolArray->size(); i++) {
        if (tetrominoBoolArray->at(i)) {
            int x = i % tetromino.getShapeSize();
            int y = i / tetromino.getShapeSize();

            Block* block = this->getBlock(location.x + x, location.y + y);
            if (!block) {
                return true;
            } else if (block->isActive()) {
                return true;
            }
        }
    }
    return false;
}

void Board::renderTetromino(Tetromino& tetromino, SDL_Point& location) {
    std::vector<bool>* tetrominoBoolArray = tetromino.getRotationBox();
    for (unsigned int i = 0; i < tetrominoBoolArray->size(); i++) {
        if (tetrominoBoolArray->at(i)) {
            int x = i % tetromino.getShapeSize();
            int y = i / tetromino.getShapeSize();

            Block* block = this->getBlock(location.x + x, location.y + y);
            if (block) {
                block->set(tetromino.getColor());
            }
        }
    }
}

Board::~Board() {

}
