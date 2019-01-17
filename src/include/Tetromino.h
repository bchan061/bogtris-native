#ifndef TETROMINO_H
#define TETROMINO_H

#include <string>
#include <vector>

class Tetromino {
    private:
        static int const AMOUNT_OF_ROTATION_BOXES = 4;

        std::string name;
        uint32_t color;
        /* 1D arrays define shapes. Conscious decision to make initializing shape arrays easier */
        bool* originalShape;
        int shapeSize;

        int currentShapeIndex;

        /* An array of 1D arrays defining shapes */
        bool** rotationBoxes;
    public:
        /**
         * Initializes a blank tetromino.
         */
        Tetromino();

        /**
         * Initializes a tetromino.
         * @param newName the name of the tetromino
         * @param newColor the color of the tetromino (0xRRGGBB)
         * @param newShape a psuedo-2D array containing the original shape
         * @param newShapeSize the length of the rotation box
         */
        Tetromino(std::string newName, uint32_t newColor, bool* newShape, int newShapeSize);

        /**
         * Generates rotation boxes for each of the four rotations.
         */
        void generateRotationBoxes();

        /**
         * Resets the tetromino to its default rotation.
         */
        void reset();

        /**
         * Rotates the tetromino left.
         */
        void rotateLeft();

        /**
         * Rotates the tetromino right.
         */
        void rotateRight();

        /**
         * Returns the current rotation box.
         */
        bool* getRotationBox();

        /**
         * Returns the length of the rotation box.
         */
        int getShapeSize() { return this->shapeSize; }

        /**
         * Returns the color of the tetromino.
         * The color is packed as 0x00RRGGBB.
         */
        uint32_t getColor() { return this->color; }

        /**
         * Helper method to get a 1D index from a 2D coordinate.
         */
        static int get1DIndexFrom2DIndex(int x, int y, int width);

        /**
         * Logs the current rotation box.
         * For debugging purposes.
         */
        void logBox();

        /**
         * Logs all rotation boxes.
         * For debugging purposes.
         */
        void logAllBoxes();

        /**
         * Destroys the tetromino.
         */
        virtual ~Tetromino();
};

#endif