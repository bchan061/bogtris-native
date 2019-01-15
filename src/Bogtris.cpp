#include "include/Bogtris.h"

#include <iostream>
#include <string>

int main(int argc, char* args[]) {
    /* Set the seed for random. */
    srand(time(NULL));

    Window *window = new Window("Bogtris", Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);
    
    Game* game = new Game();
    MainGameScreen* mainGameScreen = new MainGameScreen(game);
    game->attachScreen(mainGameScreen);

    window->attachGame(game);
    window->run();

    delete window;

    return 0;
}
