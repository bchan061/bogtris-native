#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include "Tetrominoes.h"

#include <queue>

class RandomGenerator {
    private:
        std::vector<Tetromino*> tetrominoVector;

        int nextQueueLength;

        std::queue<Tetromino*> next;
        std::queue<Tetromino*> bag;
    public:
        /**
         * Initializes a random generator.
         * @param tetrominoes a pointer to a Tetrominoes object
         */
        RandomGenerator(Tetrominoes* tetrominoes);

        /**
         * Shuffles the vector of tetrominoes via Fisher-Yates.
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
};

#endif