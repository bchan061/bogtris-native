#ifndef SCREEN_H
#define SCREEN_H

/* Forward declare Game */
class Game;

#include <SDL2/SDL.h>

class Screen {
    protected:
        Game* game;
    public:
        /**
         * Initializes a new screen.
         */
        Screen(Game* currentGame);

        /**
         * Updates the screen.
         * @param dt the elapsed time from the previous frame, in seconds
         */
        virtual void update(float dt) = 0;
        
        /**
         * Draws the screen.
         * @param alpha the interpolaton factor between the two frames
         */
        virtual void draw(float alpha) = 0;

        /**
         * Handles a keypress.
         * @param keycode the SDL_Keycode representing a key
         */
        virtual void handleKeypress(SDL_Keycode keycode) = 0;

        /**
         * Returns the game that was set.
         */
        Game* getGame() { return game; }

        /**
         * Destroys the current screen.
         */
        virtual ~Screen();
};

#endif