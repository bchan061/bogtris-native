#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>

class Block {
    private:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        bool active;
    public:
        /* Initializes a black, inactive block. */
        Block();

        /* Resets the block to a black, inactive block. */
        void reset();

        /**
         * Sets the red component of the block's color.
         * @param newRed the red component
         */
        void setRed(uint8_t newRed) { this->r = newRed; }

        /**
         * Sets the green component of the block's color.
         * @param newGreen the green component
         */
        void setGreen(uint8_t newGreen) { this->g = newGreen; }

        /**
         * Sets the blue component of the block's color.
         * @param newBlue the blue component
         */
        void setBlue(uint8_t newBlue) { this->b = newBlue; }

        /**
         * Returns the red component of the color.
         */
        uint8_t getRed() { return this->r; }

        /**
         * Returns the green component of the color.
         */
        uint8_t getGreen() { return this->g; }

        /**
         * Returns the blue component of the color.
         */
        uint8_t getBlue() { return this->b; }

        /**
         * Sets the color of the block, and then activates it.
         * @param color a 24-bit color representing the color (0xRRGGBB)
         */
        void set(uint32_t newColor);

        /**
         * Returns if the block is occupied or not.
         */
        bool isActive() { return this->active; }
};

#endif
