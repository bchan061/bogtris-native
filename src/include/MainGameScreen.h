#ifndef MAINGAMESCREEN_H
#define MAINGAMESCREEN_H

#include "Screen.h"
#include "Board.h"
#include "Tetromino.h"
#include "Tetrominoes.h"
#include "TetrominoOperations.h"
#include "RandomGenerator.h"

#include "Timer.h"

class MainGameScreen : public Screen {
    private:
        Board board;
        Tetrominoes tetrominoes;

        SDL_Point boardOffset;
        SDL_Point currentTetrominoLocation;

        Timer perpetualDropTimer;
        Timer softDropTimer;

        /**
         * Keep track of which DAS charged was most recently charged
         */
        bool dasingRight;
        Timer dasLeftTimer;
        Timer dasRightTimer;

        Tetromino* currentTetromino;
        Tetromino* heldTetromino;
        bool hasHeld;

        RandomGenerator randomGenerator;
        
        /**
         * Draws a tetromino at a block position.
         */
        void drawTetromino(Tetromino* tetromino, SDL_Point& position);

        /**
         * Draws a tetromino at a pixel position.
         * Slightly faded.
         */
        void drawTetrominoAt(Tetromino *tetromino, SDL_Point &position, uint8_t alpha);

        /**
         * Draws the held tetromino, if it exists.
         */
        void drawHeldTetromino();

        /**
         * Gets the next tetromino.
         */
        void getNextTetromino();

        /**
         * Spawns in a tetromino at the top.
         */
        void spawnInTetromino(Tetromino* tetromino);

        /**
         * Perpetually drops the tetromino.
         */
        void perpetualDrop();

        /**
         * DAS movement to the left.
         */
        void dasLeft();

        /**
         * DAS movement to the right.
         */
        void dasRight();

        /**
         * Soft drop the tetromino.
         */
        void softDrop();

        /**
         * Holds the current tetromino.
         */
        void hold();

        /**
         * Handles keyboard state for any held keys.
         */
        void handleKeystate();

        /**
         * Renders the ghost pieces of the tetromino.
         */
        void drawGhostPieces(Tetromino* tetromino, SDL_Point &position);

        /**
         * Draws the next pieces of the queue.
         */
        void drawNextPieces();
    public:
        MainGameScreen(Game* currentGame);
        void update(float dt) override;
        void draw(float alpha) override;
        void handleKeypress(SDL_Keycode keycode) override;

        /**
         * Destroys the MainGameScreen.
         */
        ~MainGameScreen() override;
};

#endif
