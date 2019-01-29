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
        Timer dasLeftTimer;
        Timer dasRightTimer;

        Tetromino* currentTetromino;
        Tetromino* heldTetromino;
        bool hasHeld;

        RandomGenerator randomGenerator;
        
        /**
         * Draws a tetromino.
         * For debugging.
         */
        void drawTetromino(Tetromino* tetromino, SDL_Point& position);

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
        void renderGhostPieces(Tetromino* tetromino, SDL_Point& position);

        
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
