#include "include/Tetromino.h"

#include <iostream>

Tetromino::Tetromino() {
    this->name = "Blank";
    this->color = 0xFF00FF;
    this->shapeSize = 1;
    this->currentShapeIndex = 0;
    this->rotationBoxes = new bool*[Tetromino::AMOUNT_OF_ROTATION_BOXES];

    this->originalShape = new bool[1];
    this->originalShape[0] = false;

    this->generateRotationBoxes();
}

Tetromino::Tetromino(std::string newName, uint32_t newColor, bool* newShape, int newShapeSize) {
    this->name = newName;
    this->color = newColor;
    this->shapeSize = newShapeSize;
    this->currentShapeIndex = 0;

    this->rotationBoxes = new bool*[Tetromino::AMOUNT_OF_ROTATION_BOXES];

    /* Clone newShape to this->originalShape */
    this->originalShape = new bool[newShapeSize];
    for (int i = 0; i < this->shapeSize * this->shapeSize; i++) {
        this->originalShape[i] = newShape[i];
    }

    this->generateRotationBoxes();
}

int Tetromino::get1DIndexFrom2DIndex(int x, int y, int width) {
    return y * width + x;
}

void Tetromino::generateRotationBoxes() {
    /*
     * The way that these boxes are generated are inefficient;
     * they are borrowed from an existing method that used 2D arrays.
     */

    /* First shape: the original shape */
    this->rotationBoxes[0] = this->originalShape;

    /* Second shape: the rotated-right shape */
    bool* newShape = new bool[this->shapeSize];
    for (int y = 0; y < this->shapeSize; y++) {
        for (int x = 0; x < this->shapeSize; x++) {
            int index = get1DIndexFrom2DIndex(x, y, this->shapeSize);
            int newIndex = get1DIndexFrom2DIndex(y, this->shapeSize - 1 - x, this->shapeSize);
            newShape[index] = this->originalShape[newIndex];
        }
    }

    this->rotationBoxes[1] = newShape;
    
    /* Third shape: the rotated-180 shape */
    bool* newShape2 = new bool[this->shapeSize];
    for (int y = 0; y < this->shapeSize; y++) {
        for (int x = 0; x < this->shapeSize; x++) {
            int index = get1DIndexFrom2DIndex(x, y, this->shapeSize);
            int newIndex = get1DIndexFrom2DIndex(this->shapeSize - 1 - x, this->shapeSize - 1 - y, this->shapeSize);
            newShape2[index] = this->originalShape[newIndex];
        }
    }
    this->rotationBoxes[2] = newShape2;

    /* Fourth shape: the rotated-left shape */
    bool* newShape3 = new bool[this->shapeSize];
    for (int y = 0; y < this->shapeSize; y++) {
        for (int x = 0; x < this->shapeSize; x++) {
            int index = get1DIndexFrom2DIndex(x, y, this->shapeSize);
            int newIndex = get1DIndexFrom2DIndex(this->shapeSize - 1 - y, x, this->shapeSize);
            newShape3[index] = this->originalShape[newIndex];
            
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

bool* Tetromino::getRotationBox() {
    return this->rotationBoxes[this->currentShapeIndex];
}

void Tetromino::logBox() {
    bool* currentRotationBox = this->getRotationBox();
    for (int i = 0; i < this->shapeSize * this->shapeSize; i++) {
        std::cout << currentRotationBox[i];
        if ((i + 1) % this->shapeSize == 0) {
            std::cout << std::endl;
        }
    }
}

void Tetromino::logAllBoxes() {
    for (int i = 0; i < 4; i++) {
        this->currentShapeIndex = i;
        std::cout << "Rotation box " << (i + 1) << " for " << this->name << ": " << std::endl;
        this->logBox();
    }
    this->currentShapeIndex = 0;
}

Tetromino::~Tetromino() {
    /* This also deletes this->originalShape */
    for (int i = 0; i < Tetromino::AMOUNT_OF_ROTATION_BOXES; i++) {
        delete[] this->rotationBoxes[i];
    }
    delete[] this->rotationBoxes;
}
