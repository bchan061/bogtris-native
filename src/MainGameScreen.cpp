#include "include/MainGameScreen.h"
#include "include/Game.h"
#include <iostream>

MainGameScreen::MainGameScreen(Game* currentGame) : Screen(currentGame) {
    this->board = new Board(10, 25, 16);
    this->board->fillRandom();
}

void MainGameScreen::update(float dt) {
    
}

void MainGameScreen::draw(float alpha) {
    this->board->drawBoard(this->game->getRenderer(), 10, 10);
}

MainGameScreen::~MainGameScreen() {
    delete this->board;
}
