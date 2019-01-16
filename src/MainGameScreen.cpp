#include "include/MainGameScreen.h"
#include "include/Game.h"
#include "include/Tetrominoes.h"
#include "include/Constants.h"

#include <iostream>

MainGameScreen::MainGameScreen(Game* currentGame) : Screen(currentGame) {
    this->board = new Board(10, 25, 24);
    this->board->fillRandom();

    Tetrominoes tetrominoes = Tetrominoes();
    std::vector<Tetromino*> tetrominoArray = tetrominoes.getAllTetrominoes();
    for (std::vector<Tetromino*>::iterator it = tetrominoArray.begin(); it != tetrominoArray.end(); it++) {
        (*it)->logAllBoxes();
    }
}

void MainGameScreen::update(float dt) {
    
}

void MainGameScreen::draw(float alpha) {
    this->board->drawBoard(this->game->getRenderer(), 10, 10);
}

MainGameScreen::~MainGameScreen() {
    delete this->board;
}
