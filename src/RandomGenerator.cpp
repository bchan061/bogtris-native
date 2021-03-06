#include "include/RandomGenerator.h"

#include <algorithm>

RandomGenerator::RandomGenerator() {
    this->nextQueueLength = 7;
}

void RandomGenerator::initWithTetrominoes(Tetrominoes* tetrominoes) {
	this->tetrominoVector = tetrominoes->getAllTetrominoes();

    this->fillQueueWithBag();
}

void RandomGenerator::shuffleTetrominoVector() {
    std::random_shuffle(this->tetrominoVector.begin(), this->tetrominoVector.end());
}

void RandomGenerator::createNewBag() {
    this->shuffleTetrominoVector();
    for (unsigned int i = 0; i < this->tetrominoVector.size(); i++) {
        this->bag.push(this->tetrominoVector.at(i));
    }
}

bool RandomGenerator::isBagEmpty() {
    return this->bag.empty();
}

void RandomGenerator::fillQueueWithBag() {
    while (this->next.size() < this->nextQueueLength) {
        if (this->isBagEmpty()) {
            this->createNewBag();
        }

        Tetromino* bagTetromino = this->bag.front();
        this->bag.pop();
        this->next.push_back(bagTetromino);
    }
}

Tetromino* RandomGenerator::getNextTetromino() {
    if (this->next.size() == 0) {
        return NULL;
    }
    
    Tetromino* nextTetrominoPtr = this->next.front();
    this->next.pop_front();

    this->fillQueueWithBag();

    return nextTetrominoPtr;
}

std::deque<Tetromino*>* RandomGenerator::getNextTetrominoes() {
    return &(this->next);
}
