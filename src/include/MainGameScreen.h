#ifndef MAINGAMESCREEN_H
#define MAINGAMESCREEN_H

#include "Screen.h"
#include "Board.h"
#include "Tetromino.h"
#include "Tetrominoes.h"
#include "TetrominoOperations.h"
#include "RandomGenerator.h"

class MainGameScreen : public Screen {
    private:
        Board board;
        Tetrominoes tetrominoes;

        SDL_Point boardOffset;
        SDL_Point currentTetrominoLocation;

        Tetromino* cur;

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
