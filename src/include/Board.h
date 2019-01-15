#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include "Block.h"

class Board {
    private:
        Block** blockArray;
        int boardWidth;
        int boardHeight;
        int blockSize;
    public:
        /**
         * Initializes a board with a set width and height.
         * @param width the board width
         * @param height the board height
         * @param blockSize the block size
         */
        Board(int width, int height, int size);

        /**
         * Fills the board with active blocks with random colors.
         * Used for debugging.
         */
        void fillRandom();

        /**
         * Debug draws the board.
         * @param renderer the SDL_Renderer to use
         * @param offsetX the offset x-coordinate of the board
         * @param offsetY the offset y-coordinate of the board
         */
        void drawBoard(SDL_Renderer* renderer, int offsetX, int offsetY);

        /**
         * Destroys the board.
         */
        ~Board();
};

#endif
