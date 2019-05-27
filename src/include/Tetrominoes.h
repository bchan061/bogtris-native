#ifndef TETROMINOES_H
#define TETROMINOES_H

#include "Tetromino.h"
#include "ITetromino.h"
#include "Board.h"
#include <SDL2/SDL.h>
#include <vector>

class Tetrominoes {
    private:
        static int const NUMBER_OF_TETROMINOES = 7;
        std::vector<Tetromino*> tetrominoArray;

        /**
         * Helper method
         */
        void createTetromino(std::string name, uint32_t color, bool* shape, int shapeSize);

		void createITetromino();
    public:
        /**
         * Initialize tetrominoes.
         */
        Tetrominoes();

        /**
         * Get all the tetrominoes.
         * Organized into a vector.
         */
        std::vector<Tetromino*> getAllTetrominoes() { return this->tetrominoArray; }

        /**
         * Sets the point specified to the appropriate spawning location.
         * @param board a pointer to a board
         * @param tetromino a pointer to a tetromino
         * @param point a pointer to a point
         */
        void setLocationToSpawningLocation(Board* board, Tetromino* tetromino, SDL_Point& point);

        /**
         * Destroys the tetrominoes.
         */
        ~Tetrominoes();
};

#endif