#ifndef TETROMINOES_H
#define TETROMINOES_H

#include "Tetromino.h"

#include <vector>

class Tetrominoes {
    private:
        static int const NUMBER_OF_TETROMINOES = 7;
        std::vector<Tetromino> tetrominoArray;

        /**
         * Helper method
         */
        void createTetromino(std::string name, uint32_t color, bool* shape, int shapeSize);
    public:
        /**
         * Initialize tetrominoes.
         */
        Tetrominoes();

        /**
         * Get all the tetrominoes.
         * Organized into a vector.
         */
        std::vector<Tetromino>* getAllTetrominoes() { return &this->tetrominoArray; }

        /**
         * Destroys the tetrominoes.
         */
        ~Tetrominoes();
};

#endif