#ifndef ROW_H
#define ROW_H

#include "Block.h"

#include <vector>

class Row {
    private:
        std::vector<Block> blocks;
        int width;
    public:
        /**
         * Initializes an empty row with no blocks.
         */
        Row();

        /**
         * Initializes a row with a set width.
         */
        Row(int width);

        /**
         * Sets the width of the row, and allocates space for the blocks.
         */
        void setWidth(int newWidth);

        /**
         * Returns a pointer to a vector of blocks representing the row.
         */
        std::vector<Block>* getBlocks() { return &(this->blocks); }

        /**
         * Returns the width of the row.
         */
        int getWidth() { return width; }

        /**
         * Gets a pointer to the block at the x-position.
         * Returns NULL if there is no such block.
         */
        Block* getBlock(int x);

        /**
         * Returns if the row is completely occupied.
         */
        bool isFull();

        /**
         * Resets the row to all non-active blocks.
         */
        void reset();

        /**
         * Destroys the row.
         */
        ~Row();
};

#endif