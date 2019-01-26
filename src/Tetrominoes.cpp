#include "include/Tetrominoes.h"
#include "include/Constants.h"

#include <math.h>

Tetrominoes::Tetrominoes() {
    this->tetrominoArray.reserve(Tetrominoes::NUMBER_OF_TETROMINOES);

    // TODO: remove to accomodate I-spins
    bool iBox[] = {
        0, 0, 0, 0,
        1, 1, 1, 1,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
    this->createTetromino("I", Constants::Colors::CYAN, iBox, 4);

    // TODO: remove to accomodate T-spins
    bool tBox[] = {
        0, 1, 0,
        1, 1, 1,
        0, 0, 0
    };
    this->createTetromino("T", Constants::Colors::PURPLE, tBox, 3);

    bool jBox[] = {
        1, 0, 0,
        1, 1, 1,
        0, 0, 0
    };
    this->createTetromino("J", Constants::Colors::BLUE, jBox, 3);

    bool lBox[] = {
        0, 0, 1,
        1, 1, 1,
        0, 0, 0
    };
    this->createTetromino("L", Constants::Colors::ORANGE, lBox, 3);

    bool oBox[] = {
        1, 1,
        1, 1
    };
    this->createTetromino("O", Constants::Colors::YELLOW, oBox, 2);

    bool sBox[] = {
        0, 1, 1,
        1, 1, 0,
        0, 0, 0
    };
    this->createTetromino("S", Constants::Colors::GREEN, sBox, 3);

    bool zBox[] = {
        1, 1, 0,
        0, 1, 1,
        0, 0, 0
    };
    this->createTetromino("Z", Constants::Colors::RED, zBox, 3);
}

void Tetrominoes::createTetromino(std::string name, uint32_t color, bool* shape, int shapeSize) {
    this->tetrominoArray.push_back(Tetromino(name, color, shape, shapeSize));
}

void Tetrominoes::setLocationToSpawningLocation(Board* board, Tetromino* tetromino, SDL_Point& point) {
    int middle = (board->getBoardWidth() / 2);
    int start = middle - (int) ceil(tetromino->getShapeSize() / 2.0f);

    point.x = start;
    point.y = board->getObscuredTop() - 1;
}

Tetrominoes::~Tetrominoes() {
    
}
