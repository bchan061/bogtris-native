#ifndef MAINGAMESCREEN_H
#define MAINGAMESCREEN_H

#include "Screen.h"
#include "Board.h"
#include "Tetromino.h"
#include "Tetrominoes.h"
#include "RandomGenerator.h"

class MainGameScreen : public Screen {
    private:
        Board board;
        Tetrominoes tetrominoes;

        SDL_Point currentTetrominoLocation;

        Tetromino* cur;

        RandomGenerator randomGenerator;
        
        /**
         * Draws a tetromino.
         * For debugging.
         */
        void drawTetromino(Tetromino* tetromino, int offsetX, int offsetY);
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
