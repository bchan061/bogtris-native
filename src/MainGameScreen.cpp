#include "include/MainGameScreen.h"
#include "include/Game.h"
#include "include/Tetromino.h"
#include "include/Constants.h"

#include <iostream>

MainGameScreen::MainGameScreen(Game* currentGame) : Screen(currentGame) {
    this->board = new Board(10, 25, 24);
    this->board->fillRandom();

    bool** oBox = new bool*[2];
    for (int i = 0; i < 2; i++) {
        oBox[i] = new bool[2];
        oBox[i][0] = true;
        oBox[i][1] = true;
    }
    Tetromino oTetrominoTest = Tetromino(
        "O",
        Constants::Colors::YELLOW,
        oBox,
        2
    );
    delete oBox;
}

void MainGameScreen::update(float dt) {

}

void MainGameScreen::draw(float alpha) {
    this->board->drawBoard(this->game->getRenderer(), 10, 10);
}

MainGameScreen::~MainGameScreen() {
    delete this->board;
}
