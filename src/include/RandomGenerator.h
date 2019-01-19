#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include "Tetrominoes.h"

#include <queue>

class RandomGenerator {
    private:
        std::vector<Tetromino*> tetrominoVector;

        unsigned int nextQueueLength;

        std::queue<Tetromino*> next;
        std::queue<Tetromino*> bag;
    public:
        /**
         * Initializes a blank random generator.
         * It will need to be initialized with RandomGenerator::initWithTetrominoes(Tetrominoes*) afterward.
         */
        RandomGenerator();

        /**
         * Initializes a random generator.
         * @param tetrominoes a pointer to a Tetrominoes object
         */
        void initWithTetrominoes(Tetrominoes* tetrominoes);

        /**
         * Shuffles the vector of tetrominoes.
         */
        void shuffleTetrominoVector();

        /**
         * Creates a new bag to pull tetrominoes from.
         */
        void createNewBag();

        /**
         * Returns whether the bag is empty or not.
         */
        bool isBagEmpty();

        /**
         * Fills the next queue with tetrominoes from the bag.
         * If the bag is empty, also creates a new bag.
         */
        void fillQueueWithBag();

        /**
         * Pop the next tetromino from the queue.
         */
        Tetromino* getNextTetromino();
};

#endif