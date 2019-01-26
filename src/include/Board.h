#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include "Row.h"
#include "Block.h"
#include "Tetromino.h"

#include <vector>

class Board {
    private:
        std::vector<Row> rowVector;
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
         * @param offset the offset relative to the top-left
         */
        void drawBoard(SDL_Renderer* renderer, SDL_Point offset);

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
         * Determines if a tetromino collides with any block (or wall) in the board.
         */
        bool tetrominoCollides(Tetromino& tetromino, SDL_Point& location);

        /**
         * Renders a tetromino onto the board.
         */
        void renderTetromino(Tetromino& tetromino, SDL_Point& location);

        /**
         * Destroys the board.
         */
        ~Board();
};

#endif
