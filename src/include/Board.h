#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include "Row.h"
#include "Block.h"

class Board {
    private:
        Row* rowArray;
        int boardWidth;
        int boardHeight;
        int blockSize;

        /* Hide first five rows */
        int hiddenTop = 5;
    public:
        /**
         * Initializes a board with a set width and height.
         * @param width the board width
         * @param height the board height
         * @param blockSize the block size
         */
        Board(int width, int height, int size);

        /**
         * Gets a pointer to the block at position (x, y) [where (0, 0) is the top-left].
         * Returns NULL if no such block exists.
         */
        Block* getBlock(int x, int y);

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
         * Returns the size of a block in pixels.
         */
        int getBlockSize() { return this->blockSize; }

        /**
         * Returns the width of the board.
         */
        int getBoardWidth() { return this->boardWidth; }

        /**
         * Returns the height of the board (including the obscured rows)
         */
        int getBoardHeight() { return this->boardHeight; }

        /**
         * Returns the amount of rows that are hidden at the top.
         */
        int getObscuredTop() { return this->hiddenTop; }

        /**
         * Destroys the board.
         */
        ~Board();
};

#endif
