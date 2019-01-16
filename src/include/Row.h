#ifndef ROW_H
#define ROW_H

#include "Block.h"

class Row {
    private:
        Block* blocks;
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
         * Returns an array of blocks representing the row.
         */
        Block* getBlocks() { return blocks; }

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
         * Destroys the row.
         */
        ~Row();
};

#endif