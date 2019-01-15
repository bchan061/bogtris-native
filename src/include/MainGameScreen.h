#ifndef MAINGAMESCREEN_H
#define MAINGAMESCREEN_H

#include "Screen.h"
#include "Board.h"

class MainGameScreen : public Screen {
    private:
        Board* board;
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
