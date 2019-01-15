#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Screen.h"
#include "Constants.h"

class Game {
    private:
        uint32_t previousTick;
        bool firstUpdate;

        float elapsedDt;

        Screen* currentScreen;
        SDL_Renderer* renderer;
    public:
        /**
         * Initializes an empty game.
         */
        Game();

        /**
         * Updates the current game and screen.
         * @param currentTick the current tick time (in ms)
         */
        void update(uint32_t currentTick);

        /**
         * Attaches a new screen into the game.
         * Does not destroy any previous screens attached.
         * @param newScreen a pointer to a new screen
         */
        void attachScreen(Screen* newScreen);

        /**
         * Detaches the current screen from the game.
         * Also destroys the screen.
         */
        void detachScreen();

        /**
         * Changes the current screen to a new screen.
         * Destroys the old screen.
         * @param newScreen a pointer to a new screen
         */
        void changeScreen(Screen* newScreen);

        /**
         * Attaches a SDL_Renderer to the game.
         * @param newRenderer the new renderer
         */
        void attachRenderer(SDL_Renderer* newRenderer) { this->renderer = newRenderer; }

        /**
         * Returns a SDL_Renderer that (could have been) previously set.
         */
        SDL_Renderer* getRenderer() { return this->renderer; }

        /**
         * Destroys the game.
         */
        ~Game();
};

#endif