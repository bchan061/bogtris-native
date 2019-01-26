#ifndef TETROMINOOPERATIONS_H
#define TETROMINOOPERATIONS_H

#include "Board.h"
#include "Tetromino.h"

class TetrominoOperations {
    public:
        /**
         * Soft drops the tetromino.
         */
        static bool softDrop(Board& board, Tetromino& tetromino, SDL_Point& currentLocation);

        /**
         * Hard drops the tetromino.
         */
        static bool hardDrop(Board& board, Tetromino& tetromino, SDL_Point& currentLocation);

        /**
         * Tries to move the tetromino to an offset.
         */
        static bool tryMove(Board& board, Tetromino& tetromino, SDL_Point& currentLocation, SDL_Point& offset);

        /**
         * Tries to rotate the tetromino within the board.
         * May include any kicks.
         * Returns the offset used, or -1 
         */
        static int tryRotate(Board& board, Tetromino& tetromino, SDL_Point& currentLocation, bool clockwise);
};

#endif