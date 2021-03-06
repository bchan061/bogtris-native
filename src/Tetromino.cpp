#include "include/Tetromino.h"

#include <iostream>

Tetromino::Tetromino() {
    this->name = "Blank";
    this->color = 0xFF00FF;
    this->shapeSize = 1;
    this->currentShapeIndex = 0;

    /* Create a one tile shape */
    std::vector<bool> original{ true };
    this->rotationBoxes.push_back(original);

    this->generateRotationBoxes();
    this->generateOffsets();
}

Tetromino::Tetromino(std::string newName, uint32_t newColor, bool* newShape, int newShapeSize) {
    this->name = newName;
    this->color = newColor;
    this->shapeSize = newShapeSize;
    this->currentShapeIndex = 0;

    /* Clone newShape to the first rotation box */
    std::vector<bool> original;
    for (int i = 0; i < newShapeSize * newShapeSize; i++) {
        original.push_back(newShape[i]);
    }
    this->rotationBoxes.push_back(original);

    this->generateRotationBoxes();
    this->generateOffsets();
}

int Tetromino::get1DIndexFrom2DIndex(int x, int y, int width) {
    return y * width + x;
}

void Tetromino::generateRotationBoxes() {
    /*
     * The way that these boxes are generated are inefficient;
     * they are borrowed from an existing method that used 2D arrays.
     */
    
    /* First shape: the original shape. Should already be added. */

    /* For convenience */
    std::vector<bool> originalShape = this->rotationBoxes.at(0);

    /* Second shape: the rotated-right shape */
    std::vector<bool> newShape;
    newShape.resize(this->shapeSize * this->shapeSize);
    for (int y = 0; y < this->shapeSize; y++) {
        for (int x = 0; x < this->shapeSize; x++) {
            int index = Tetromino::get1DIndexFrom2DIndex(x, y, this->shapeSize);
            int oldIndex = Tetromino::get1DIndexFrom2DIndex(y, this->shapeSize - 1 - x, this->shapeSize);
            newShape[index] = originalShape.at(oldIndex);
        }
    }

    this->rotationBoxes.push_back(newShape);
    
    /* Third shape: the rotated-180 shape */
    std::vector<bool> newShape2;
    newShape2.resize(this->shapeSize * this->shapeSize);
    for (int y = 0; y < this->shapeSize; y++) {
        for (int x = 0; x < this->shapeSize; x++) {
            int index = Tetromino::get1DIndexFrom2DIndex(x, y, this->shapeSize);
            int oldIndex = Tetromino::get1DIndexFrom2DIndex(this->shapeSize - 1 - x, this->shapeSize - 1 - y, this->shapeSize);
            newShape2[index] = originalShape.at(oldIndex);
        }
    }
    this->rotationBoxes.push_back(newShape2);

    /* Fourth shape: the rotated-left shape */
    std::vector<bool> newShape3;
    newShape3.resize(this->shapeSize * this->shapeSize);
    for (int y = 0; y < this->shapeSize; y++) {
        for (int x = 0; x < this->shapeSize; x++) {
            int index = Tetromino::get1DIndexFrom2DIndex(x, y, this->shapeSize);
            int oldIndex = Tetromino::get1DIndexFrom2DIndex(this->shapeSize - 1 - y, x, this->shapeSize);
            newShape3[index] = originalShape.at(oldIndex);
        }
    }
    this->rotationBoxes.push_back(newShape3);
}

void Tetromino::generateOffsets() {
    /*
     * These offsets are assuming that as y points up.
     * We'll need to flip the y-values later.
     */
    this->offsets = std::vector<std::vector<std::vector<int>>> {
        {
            { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
            { {0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2} },
            { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} },
            { {0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} }
        }
    };
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

std::vector<bool>* Tetromino::getRotationBox() {
    return &(this->rotationBoxes.at(this->currentShapeIndex));
}

std::vector<bool>* Tetromino::getOriginalRotationBox() {
    return &(this->rotationBoxes.at(0));
}

void Tetromino::logBox() {
    std::vector<bool>* currentRotationBox = this->getRotationBox();
    for (int i = 0; i < this->shapeSize * this->shapeSize; i++) {
        std::cout << currentRotationBox->at(i);
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
    
}
