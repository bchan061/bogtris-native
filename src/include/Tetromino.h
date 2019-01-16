#ifndef TETROMINO_H
#define TETROMINO_H

#include <string>
#include <vector>

class Tetromino {
    private:
        static int const AMOUNT_OF_ROTATION_BOXES = 4;

        std::string name;
        uint32_t color;
        bool** originalShape;
        int shapeSize;

        int currentShapeIndex;

        /* An array of 2D arrays defining shapes */
        bool*** rotationBoxes;
    public:
        /**
         * Initializes a tetromino.
         * @param newName the name of the tetromino
         * @param newColor the color of the tetromino (0xRRGGBB)
         * @param newShape a 2D array containing the original shape
         * @param newShapeSize the length of the rotation box
         */
        Tetromino(std::string newName, uint32_t newColor, bool** newShape, int newShapeSize);

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
        bool** getRotationBox();

        /**
         * Logs the current rotation box.
         * For debugging purposes.
         */
        void logBox();

        /**
         * Destroys the tetromino.
         */
        virtual ~Tetromino();
};

#endif