#ifndef MAINGAMESCREEN_H
#define MAINGAMESCREEN_H

#include "Screen.h"
#include "Board.h"
#include "Tetromino.h"
#include "Tetrominoes.h"

class MainGameScreen : public Screen {
    private:
        Board* board;
        Tetrominoes* tetrominoes;
        
        /**
         * Draws a tetromino.
         * For debugging.
         */
        void drawTetromino(Tetromino* tetromino, int offsetX, int offsetY);
    public:
        MainGameScreen(Game* currentGame);
        void update(float dt) override;
        void draw(float alpha) override;

        /**
         * Destroys the MainGameScreen.
         */
        ~MainGameScreen() override;
};

#endif
