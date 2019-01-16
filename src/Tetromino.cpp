#include "include/Tetromino.h"

Tetromino::Tetromino(std::string newName, uint32_t newColor, bool** newShape, int newShapeSize) {
    this->name = newName;
    this->color = newColor;
    this->shapeSize = newShapeSize;
    this->currentShapeIndex = 0;

    this->rotationBoxes = new bool**[Tetromino::AMOUNT_OF_ROTATION_BOXES];

    /* Clone newShape to this->originalShape */
    this->originalShape = new bool*[newShapeSize];
    for (int y = 0; y < newShapeSize; y++) {
        this->originalShape[y] = new bool[newShapeSize];
        for (int x = 0; x < newShapeSize; x++) {
            this->originalShape[y][x] = originalShape[y][x];
        }
    }

    this->generateRotationBoxes();
    this->logBox();
}

void Tetromino::generateRotationBoxes() {
    /* First shape: the original shape */
    this->rotationBoxes[0] = this->originalShape;

    /* Second shape: the rotated-right shape */
    bool** newShape = new bool*[this->shapeSize];
    for (int y = 0; y < this->shapeSize; y++) {
        newShape[y] = new bool[this->shapeSize];
        for (int x = 0; x < this->shapeSize; x++) {
            newShape[y][x] = this->originalShape[this->shapeSize - 1 - x][y];
        }
    }

    this->rotationBoxes[1] = newShape;
    
    /* Third shape: the rotated-180 shape */
    bool** newShape2 = new bool*[this->shapeSize];
    for (int y = 0; y < this->shapeSize; y++) {
        newShape2[y] = new bool[this->shapeSize];
        for (int x = 0; x < this->shapeSize; x++) {
            newShape2[y][x] = this->originalShape[this->shapeSize - 1 - y][this->shapeSize - 1 - x];
        }
    }
    this->rotationBoxes[2] = newShape2;

    /* Fourth shape: the rotated-left shape */
    bool** newShape3 = new bool*[this->shapeSize];
    for (int y = 0; y < this->shapeSize; y++) {
        newShape3[y] = new bool[this->shapeSize];
        for (int x = 0; x < this->shapeSize; x++) {
            newShape3[y][x] = this->originalShape[x][this->shapeSize - 1 - y];
        }
    }
    this->rotationBoxes[3] = newShape3;
}

void Tetromino::reset() {
    this->currentShapeIndex = 0;
}

void Tetromino::rotateLeft() {
    this->currentShapeIndex = (
        (this->currentShapeIndex - 1) + Tetromino::AMOUNT_OF_ROTATION_BOXES
    ) % Tetromino::AMOUNT_OF_ROTATION_BOXES;
}

void Tetromino::rotateRight() {
    this->currentShapeIndex = (this->currentShapeIndex + 1) % Tetromino::AMOUNT_OF_ROTATION_BOXES;
}

bool** Tetromino::getRotationBox() {
    return this->rotationBoxes[this->currentShapeIndex];
}

void Tetromino::logBox() {
    bool** currentRotationBox = this->getRotationBox();
    for (int y = 0; y < this->shapeSize; y++) {
        for (int x = 0; x < this->shapeSize; x++) {
            if (currentRotationBox[y][x]) {
                printf("X");
            } else {
                printf("O");
            }
        }
        printf("\n");
    }
}

Tetromino::~Tetromino() {
    /* Remove the generated rotation boxes; but not the original */
    for (int i = 1; i < Tetromino::AMOUNT_OF_ROTATION_BOXES; i++) {
        for (int y = 0; y < this->shapeSize; y++) {
            delete[] this->rotationBoxes[i][y];
        }
        delete[] this->rotationBoxes[i];
    }
    delete[] this->rotationBoxes;
}
